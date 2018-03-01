#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// int randInt(int n):�H���Ǧ^�@�Ӥp�� n ����� (0,1,2..., n-1)
// �Ϊk:randInt(5) �|�Ǧ^ 0, 1, 2, 3, 4 �䤤���@
int randInt(int n) { // �H���Ǧ^�@�Ӥp�� n ����� (0,1,2..., n-1)
  return rand() % n;
}

// int randChar(char *set):�H���Ǧ^ set �����@�Ӧr��
// �Ϊk:randChar("0123456789") �|�Ǧ^�@���H�����Ʀr
int randChar(char *set) { // �H���Ǧ^ set �����@�Ӧr��
  int len = strlen(set);
  int i = rand()%len;
  return set[i];
}

int timeSeed() {
  long ltime = time(NULL);
  printf("ltime=%ld\n", ltime);
  int stime = (unsigned) ltime/2;
  srand(stime);
}
