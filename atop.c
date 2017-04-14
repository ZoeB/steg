/* ASCII to PETSCII converter, by Zoe Blade */

/* At the moment, this merely swaps uppercase and lowercase letters. */

#include <stdio.h>

void convert(FILE *inputFilePointer, FILE *outputFilePointer) {
	int c;

	while ((c = getc(inputFilePointer)) != EOF) {
		if (c > 0x40 && c < 0x5B) {
			/* Uppercase */
			putc(c + 0x20, outputFilePointer);
		} else if (c > 0x60 && c < 0x7B) {
			/* Lowercase */
			putc(c - 0x20, outputFilePointer);
		} else {
			putc(c, outputFilePointer);
		}

		putc('\n', outputFilePointer);
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
