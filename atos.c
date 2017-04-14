#include <stdint.h>

int main(int argc, char *argv[]) {
	uint8_t font[128][5];

	font['A'][0] = 0b00000010;
	font['A'][1] = 0b00000101;
	font['A'][2] = 0b00000111;
	font['A'][3] = 0b00000101;
	font['A'][4] = 0b00000101;

	return 0;
}
