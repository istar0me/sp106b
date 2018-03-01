#include <stdio.h>
#include <assert.h>

#define NIL -1				// �䤣��ɶǦ^ NIL
#define SLOTS 4				// �@�� case ���̦h slot �ƶq
#define FILLS 4				// �C�� SLOT �̦h��J���J��
#define TOKENS 1000			// �@�ӥy�l���̦h���J�W��
#define SMAX 100000			// �r���e�q

char *empty="";				// �Ŧr��
char *slots[SLOTS][FILLS]; 	// �C����쪺��R�� (�i��h�ӡA�̦h FILLS ��)
int  fills[SLOTS]; 			// �C����쪺��R�Ӽ�
char *tokens[TOKENS];		// ���J��C
char strTable[SMAX]; 		// �r���
int  strTop = 0;	 		// �r���j�p
extern char *words[];		// ���J��C
extern char *isList[][2];	// (���J, �аO) �t���C
extern char *cases[][SLOTS];// ���ܻy�k��C

// �N�y�y�_�������J��C
int tokenize(char *str, char *tokens[]) {
	int i, ti=0;
	for (i=0; i<strlen(str); ) {
		int wi = wordFind(&str[i]);
		char *ch;
		if (wi == NIL) {
			ch = &strTable[strTop];
			sprintf(ch, "%c%c", str[i], str[i+1]);
			strTop += 3;
		}
		assert(ti < TOKENS);
		tokens[ti] = (wi==NIL)?ch:words[wi];
		i+= strlen(tokens[ti]);
		ti++;
	}
	tokens[ti] = NULL;
}

// �M����夤�O�_���o�ӵ��J
int wordFind(char *str) {
	int i;
	for (i=0; words[i]!=NULL; i++) {
		if (strncmp(str, words[i], strlen(words[i]))==0) {
			return i;
		}
	}
	return NIL;
}

// �L�X���J�}�C
int wordsPrint(char *words[]) {
	int i;
	for (i=0; words[i] != NULL; i++) {
		printf("%s ", words[i]);
	}
	printf("\n");
}

// ����R���D�n�t��k
double caseFill(char *tokens[], char *fields[SLOTS], char *slots[SLOTS][FILLS]) {
	int ti, si, fi, score=0;
	for (si=0; si<SLOTS; si++)
		fills[si] = 0;
	for (ti=0; tokens[ti]!=NULL; ti++) {
		for (si=0; si<SLOTS; si++) {
			if (pairFind(tokens[ti], fields[si], isList)!=NIL) {
				assert(fills[si] < FILLS);
				slots[si][fills[si]++] = tokens[ti];
			}
		}
	}
	for (si=0; si<SLOTS; si++)
		score += fills[si];
	return score;
}

// �M��X�̦n����R�W�h
int caseBest() {
	int ci, best=0;
	double  bestScore=0.0;
	for (ci=0; cases[ci][0] != NULL; ci++) {
		double score = caseFill(tokens, cases[ci], slots);
		if (score > bestScore) {
			best = ci;
			bestScore = score;
		}
	}
	return best;
}

// �L�X��R�����p
int casePrint(char *fields[SLOTS], char *slots[SLOTS][FILLS]) {
	int si, fi;
	for (si=0; si<SLOTS; si++) {
		if (fields[si] != NULL) {
			printf("%s:", fields[si]);
			for (fi=0; fi<fills[si]; fi++)
				printf("%s ", slots[si][fi]);
		}
	}
	printf("\n");
}

// �M�� (child, parent) �t��O�_�s�b pairList ���C
int pairFind(char *child, char *parent, char *pairList[][2]) {
	if (child == NULL || parent == NULL) return NIL;
	int pi=0; 
	for (pi=0; pairList[pi][0] != NULL; pi++) {
		if (strcmp(child, pairList[pi][0])==0 && strcmp(parent, pairList[pi][1])==0)
			return pi;
	}
	return NIL;
}

// �y�N�ѪR�G�H����R��k��X�̨ζ�R�� case�A�M��L�X��R���p�C
int semantics(char *str) {
	tokenize(str, tokens); 	// �_��
	wordsPrint(tokens); 	// �L�X�_��
	int best = caseBest(); 	// ��X�̨ζ�R
	double score = caseFill(tokens, cases[best], slots); // ����@���̨ζ�R
	casePrint(cases[best], slots); // �L�X�̨ζ�R
	printf("\n");
}
