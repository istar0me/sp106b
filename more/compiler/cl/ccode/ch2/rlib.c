#include <stdio.h>

// int randInt(int n):�H���Ǧ^�@�Ӥp�� n ����� (0,1,2..., n-1)
// �Ϊk:randInt(5) �|�Ǧ^ 0, 1, 2, 3, 4 �䤤���@
int randInt(int n) { // �H���Ǧ^�@�Ӥp�� n ����� (0,1,2..., n-1)
  return rand() % n;
}

// int randChar(char *set):�H���Ǧ^ set �����@�Ӧr��
// �Ϊk:randChar("0123456789") �|�Ǧ^�@���H�����Ʀr
char randChar(char *set) { // �H���Ǧ^ set �����@�Ӧr��
  int len = strlen(set);
  int i = rand()%len;
  return set[i];
}

// int randStr(char *set, int size):�H���Ǧ^ set �����@�Ӧr��
// �Ϊk: char *n[] = {"dog", "cat"}; randStr(n, 2) 
//       �|�Ǧ^ "dog", "cat" �䤤���@�C
char *randStr(char *set[], int size) { // �H���Ǧ^ set �����@�Ӧr��
  int i = rand()%size;
  return set[i];
}
