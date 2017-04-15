/* Columns to Sines, by Zoe Blade */

/* Convert columns of a bitmap, 8 pixels high, 1 bit per pixel, into
a series of sine waves.  */

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "wavfile.c"

FILE *wav;

float i;
int freq;
int col;
int row;
float pixel;
float mix;
short out;

uint8_t charset[2048];

void convert(FILE *inputFilePointer) {
	/* Loop through each column of the bitmap */
	while ((col = getc(inputFilePointer)) != EOF) {
		/* Loop through each sample */
		for (i = 0; i < 11025; i++) { /* Hardwire each pixel width as 1/4 of a CD quality second for now */
			mix = 0;

			/* Work out which oscillators are on for this column */
			for (row = 0; row < 8; row++) {
				if (col & (1 << (7 - row))) { /* Lowest frequency oscillator first */
					freq = 16000 + (500 * row); /* Hardwire each pixel height as a single sine wave "beam" 500Hz apart from its neighbours, starting at 16kHz, for now */
					freq *= 4; /* I don't know why this is needed.  TODO: Figure this out! */
					pixel = sin(freq * (i / 44100.0) * M_PI_2); /* The number of cycles per second is multiplied by the number of seconds.  Even though the latter's between 0 and 0.25, the frequencies bring it up.  Hardwire CD quality sample rate for now. */

					/* Fuzz off the edges of each pixel to avoid noise bursts */
					if (i < 2757) {
						pixel = pixel / 2727 * i;
					} else if (i > 8268) {
						pixel = pixel / 2727 * (11025 - i);
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

	wav = wavfile_open("out.wav");

	if (!wav) {
		printf("Error: unable to write to out.wav.\n");
	}

	if (argc == 1) {
		convert(stdin);
	} else {
		while (--argc > 0) {
			filePointer = fopen(*++argv, "r");

			if (filePointer == NULL) {
				continue;
			}

			convert(filePointer);
			fclose(filePointer);
		}
	}

	wavfile_close(wav);
	return 0;
}
