/* Columns to Sines, by Zoe Blade */

/* Convert columns of a bitmap, 8 pixels high, 1 bit per pixel, into
a series of sine waves.  */

#include <stdint.h>
#include <stdio.h>

uint8_t byte;
int col;
int row;

uint8_t charset[2048];

void convert(FILE *inputFilePointer, FILE *outputFilePointer) {
	/* Loop through each column of the bitmap */
	while ((col = getc(inputFilePointer)) != EOF) {
		/* Work out which oscillators are on for this column */
		for (row = 0; row < 8; row++) {
			if (col & (1 << (7 - col))) {
				byte |= 1 << row;
			}
		}
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
