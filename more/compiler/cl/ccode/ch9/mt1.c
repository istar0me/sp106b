#include <stdio.h>
#include <string.h>
#define NIL -1
char *ewords[] = {"a",  "the", "cat", "dog", "lady", "chase", "bite", "park", "in", NULL};
char *cwords[] = {"�@", "�o",  "��",  "��",  "�k�H", "�l",    "�r",   "����", "�b", NULL};

// �M����夤�O�_���o�ӵ��J
int wordFind(char *words[], char *word) {
    int i;
    for (i=0; words[i]!=NULL; i++) {
        if (strncmp(word, words[i], strlen(words[i]))==0)
            return i;
    }
    return NIL;
}

void mt(char *s, char *swords[], char *twords[]) {
	char *spliter=",;. ";
	char *sword = strtok(s, spliter);
	while (sword != NULL) {
		int si = wordFind(swords, sword);
		if (si!=NIL) {
			printf("%s(%s) ", swords[si], twords[si]);
		}
		sword = strtok(NULL, spliter);
	}
}

int main(int argc, char * argv[]) {
	char english[] = "a dog chase a lady in the park";
	mt(english, ewords, cwords);
}