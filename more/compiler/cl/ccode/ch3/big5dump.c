#include <stdio.h>

#define BYTE unsigned char

int main() {
	BYTE h, t;
	for (h=0xA1; h<=0xF9; h++) { // Big5 ���X�d��
		printf("\n");
		for (t=0x00; t<0xFF; t++) { // Big5 ���X�d��
			printf("%c%c %2x%2x", h, t, h, t);
			if (t % 8 == 0) printf("\n");
		}
	}
}
