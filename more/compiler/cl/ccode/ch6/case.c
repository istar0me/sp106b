#include "semantics.c"

// ���ܻy�k: Role Action Object by Tools
// ���d��: semantics("�����η}�Y�V�v�l") => people:���� knock:�V object:�v�l hammer:�}�Y
// ���d��: semantics("�ߦY��") => animal:�� �� eat:�Y food:��

char *words[] = {"����", "�V", "�v�l", "�}�Y", "��", "��", "�Y", "��", NULL}; // ����
char *isList[][2]  // ���J�P�аO�����Y��C
= {{"�V", "knock"}, {"����", "people"}, {"�v�l", "object"}, {"�}�Y", "hammer"}, 
   {"��", "animal"}, {"�Y", "eat"}, {"��", "food"}, {"��", "animal"}, {NULL, NULL}}; 
char *cases[][SLOTS] = { // case (���ܻy�k) 
	{ "animal", "eat", "food", NULL }, 
	{ "people", "knock", "object", "hammer"},
	{ NULL, NULL, NULL, NULL }
};

int main() {
	semantics("�����η}�Y�V�v�l"); 	// �y�N�ѪR�d�� 1
	semantics("�ߦY��");			// �y�N�ѪR�d�� 2
}
