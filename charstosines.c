/* Columns to Sines, by Zoe Blade */

/* Convert columns of a bitmap, 8 pixels high, 1 bit per pixel, into
a series of sine waves.  */

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "wavfile.c"

FILE *wav;

uint8_t charset[768];

int c;
int i = 0;

uint8_t byte;
int charOffset;

float sample;
int freq;
int col;
int row;
int numberOfCopies = 4;
int copy;
float pixel;
float mix;
short out;

void convert(FILE *inputFilePointer) {
	/* Loop through each column of the bitmap */
	while ((col = getc(inputFilePointer)) != EOF) {
		/* Loop through each sample */
		for (sample = 0; sample < 11025; sample++) { /* Hardwire each pixel width as 1/4 of a CD quality second for now */
			mix = 0;

			/* Work out which oscillators are on for this column */
			for (row = 0; row < 8; row++) {
				if (col & (1 << (7 - row))) { /* Lowest frequency oscillator first */
					freq = 16000 + (500 * row); /* Hardwire each pixel height as a single sine wave "beam" 500Hz apart from its neighbours, starting at 16kHz, for now */
					pixel = 0;

					for (copy = 0; copy < numberOfCopies; copy++) {
						/* TODO: Work out why the frequency needs to be multiplied by 4. */
						pixel += sin((freq + (500 / numberOfCopies * copy)) * 4 * (sample / 44100.0) * M_PI_2); /* The number of cycles per second is multiplied by the number of seconds.  Even though the latter's between 0 and 0.25, the frequencies bring it up.  Hardwire CD quality sample rate for now. */
					}

					pixel /= numberOfCopies;

					/* Fuzz off the edges of each pixel to avoid noise bursts */
					if (sample < 2757) {
						pixel = pixel / 2727 * sample;
					} else if (sample > 8268) {
						pixel = pixel / 2727 * (11025 - sample);
					}

					/* Fuzz off the top and bottom rows too */
					if (copy == 0 || copy == numberOfCopies - 1) {
						pixel /= 2;
					}

					mix += (1.0 / 9.0) * pixel; /* Each sine wave should be 1/9th volume, for mixing with headroom */
				}
			}

			out = floor(mix * 32767); /* Convert waveform into signed 16-bit integer */
			wavfile_write(wav, &out, 1);
		}
	}
}

int main(int argc, char *argv[]) {
	FILE *filePointer;

	/* Load charset into memory.  TODO: make it possible to specify which charset on the command line. */
	filePointer = fopen("c64ascii.bin", "r");

	if (filePointer == NULL) {
		return 1;
	}

	while (((c = getc(filePointer)) != EOF) && (i < 768)) {
		charset[i] = c;
		i++;
	}

	fclose(filePointer);

	wav = wavfile_open("out.wav");

	if (!wav) {
		printf("Error: unable to write to out.wav.\n");
	}

	if (argc != 1) {
		printf("Error: please specify exactly one text string.\n");
	}

	while ((c = getc(stdin)) != EOF) {
		/* Only display printable ASCII characters */
		if (c < 32 || c >= 160) {
			continue;
		}

		/* The character set file should only contain printable ASCII characters */
		charOffset = 8 * (c - 32);

		for (col = 0; col < 8; col++) {
			byte = 0;

			for (row = 0; row < 8; row++) {
				if (charset[charOffset + row] & (1 << (7 - col))) {
					byte |= 1 << row;
				}
			}

			convert(byte);
		}
	}

	wavfile_close(wav);
	return 0;
}
