/* Columns to Sines, by Zoe Blade */

/* Convert columns of a bitmap, 8 pixels high, 1 bit per pixel, into
a series of sine waves.  */

#include <stdint.h>
#include <stdio.h>

int c;

uint8_t byte;
int charOffset;
int col;
int row;

uint8_t charset[2048];

void convert(FILE *inputFilePointer, FILE *outputFilePointer) {
	while ((c = getc(inputFilePointer)) != EOF) {
		charOffset = 8 * c;

		for (col = 0; col < 8; col++) {
			byte = 0;

			for (row = 0; row < 8; row++) {
				if (charset[charOffset + row] & (1 << (7 - col))) {
					byte |= 1 << row;
				}
			}

			putc(byte, outputFilePointer);
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
