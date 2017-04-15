/* Columns to Sines, by Zoe Blade */

/* Convert columns of a bitmap, 8 pixels high, 1 bit per pixel, into
a series of sine waves.  */

#include <math.h>
#include <stdint.h>
#include <stdio.h>

int i;
int freq;
int col;
int row;
float mix;
uint8_t out;

uint8_t charset[2048];

void convert(FILE *inputFilePointer, FILE *outputFilePointer) {
	/* Loop through each column of the bitmap */
	while ((col = getc(inputFilePointer)) != EOF) {
		mix = 0;

		for (i = 0; i < 11025; i++) { /* Hardwire each pixel width as 1/4 of a CD quality second for now */
			/* Work out which oscillators are on for this column */
			for (row = 0; row < 8; row++) {
				if (col & (1 << (7 - row))) { /* Lowest frequency oscillator first */
					freq = 16000 + (500 * row); /* Hardwire each pixel height as a single sine wave "beam" 500Hz apart from its neighbours, starting at 16kHz, for now */
					/* Each sine wave should be 1/9th volume, for mixing with headroom */
					mix += (1 / 9) * sin(freq * (i / 44100) * M_PI_2); /* Hardwire CD quality sample rate for now */
				}
			}
		}

		out = mix * 255; /* Hardwire 8-bit quality for now */
		putc(out, outputFilePointer);
	}
}

int main(int argc, char *argv[]) {
	FILE *filePointer;

	if (argc == 1) {
		convert(stdin, stdout);
	} else {
		while (--argc > 0) {
			filePointer = fopen(*++argv, "r");

			if (filePointer == NULL) {
				continue;
			}

			convert(filePointer, stdout);
			fclose(filePointer);
		}
	}

	return 0;
}
