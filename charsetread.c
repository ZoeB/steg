/* Raw 1-bit 8x8 charset reader, by Zoe Blade */

/* Read 1-bit-per-pixel, 8-pixels-wide bitmap artwork and display it
as ASCII art*/

#include <stdio.h>

void readFont(FILE *inputFilePointer, FILE *outputFilePointer) {
	int character;
	int i;

	while ((character = getc(inputFilePointer)) != EOF) {
		for (i = 0; i < 8; i++) {
			if (character & (1 << (7 - i))) {
				putc('#', outputFilePointer);
			} else {
				putc(' ', outputFilePointer);
			}
		}

		putc('\n', outputFilePointer);
	}
}

int main(int argc, char *argv[]) {
	FILE *filePointer;

	if (argc == 1) {
		readFont(stdin, stdout);
	} else {
		while (--argc > 0) {
			filePointer = fopen(*++argv, "r");

			if (filePointer == NULL) {
				continue;
			}

			readFont(filePointer, stdout);
			fclose(filePointer);
		}
	}

	return 0;
}
