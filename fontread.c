/* Raw 1-bit 8x8 font reader, by Zoe Blade */

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
		return 0; /* Only work with named files, not stdin */
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