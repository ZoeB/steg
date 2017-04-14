/* Chars to Columns, by Zoe Blade */

#include <stdint.h>
#include <stdio.h>

int c;
int i = 0;

uint8_t data;
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
				data = charset[charOffset + row] & (1 << (7 - col));

				if (data > 0) {
					data = 1;
				}

				byte |= data << row;
			}

			putc(byte, outputFilePointer);
		}
	}
}

int main(int argc, char *argv[]) {
	FILE *filePointer;

	/* Load charset into memory.  TODO: make it possible to specify which charset on the command line. */
	filePointer = fopen("c64lower.bin", "r");

	if (filePointer == NULL) {
		return 1;
	}

	while (((c = getc(filePointer)) != EOF) && (i < 2048)) {
		charset[i] = c;
		i++;
	}

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
