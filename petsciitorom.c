/* PETSCII to ROM, by Zoe Blade */

#include <stdio.h>

void convert(FILE *inputFilePointer, FILE *outputFilePointer) {
	int c;

	while ((c = getc(inputFilePointer)) != EOF) {
		switch (c & 0b01110000) {
		case 0b01000000: /* @ to o */
		case 0b01010000: /* p to <- */
			c -= 64; /* Shift lowercase letters */
			break;

		case 0b01100000: /* _ to O */
		case 0b01110000: /* P to thing */
			c -= 32; /* Shift uppercase letters */
		}

		putc(c, outputFilePointer);
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
