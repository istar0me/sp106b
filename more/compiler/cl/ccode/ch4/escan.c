#include <stdio.h>

char text[] = "Mr. Jamie is a young man.";

char *next(char *text, int *idx, char *token) {	// ���o�U�@�� token
	int i = *idx;				
	if (text[i] == '\0') return NULL; // �w�����
    while (isalpha(text[i])) { 	// �����ť�
		i++;
    }
	if (i == *idx) i++;	// �p�G���O�^��r���A����@�r���C
	int len = i-(*idx);
	strncpy(token, &text[*idx], len);
	token[len] = '\0';
	*idx = i; // �e�i��U�@�Ӧr�}�Y
	return token;
}

int scan(char *text) { // ���y�����D�n�\��
	int ti=0;
	char token[100];
    while (next(text, &ti, token)!=NULL) { // ���_���y
		printf("%s|", token);
    }
}

int main(int argc, char * argv[]) {	// ���y���D�{��
	scan(text);
}
