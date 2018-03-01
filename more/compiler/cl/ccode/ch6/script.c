#include "semantics.c"

// �@�����G�ϥή��ܻy�k
char *sentences[] = 
{"�����P�����O�j�Ǫ��P�Z�P��", "�b�j�T�ɬ����R�W�F����", "���~��L�̴N���B�F", 
"�åB�ͤF�@�Ӥp�k�ĳ��J", "�������~��i�J�@�a�j���q�u�@", "�ѩ��{�}�n�A�ҥH�Q���¬��g�z", 
"�g�i�O�L������", "�ѩ�u�@�W�¤i�۳B�A�H�P�����P�g�i��[�ͱ�", "�����o�{�����P�g�i���~�J�ƥ��", 
"�o�M�w���B", "�åB���o�F���J�����@�v�C", "�Ө�H���B���ᤣ�[", "�����P�g�i�N���B�F�C"};

char *words[] = {"��[�ͱ�", "����", "����", "�g�i", "���J", "���B", "�L��", "�L��", "�~�J", "���B", "�R", "��", NULL}; // ����

char *isList[][2]  // ���J�P�аO�����Y��C
= {{"��[�ͱ�", "love"},  {"����", "man"}, {"����", "woman"}, {"�g�i", "woman"}, {"���J", "man"}, 
   {"���J", "baby"}, {"�L��", "man"}, {"�L��", "woman"}, {"�~�J", "extramarital"}, 
   {"���B", "marry"}, {"���B", "divorce"}, {"�R", "love"}, {"��", "born"}, 
   {"�L", "man"}, {"�o", "woman"}, {NULL, NULL}}; 
char *cases[][SLOTS] = { // case (���ܻy�k) 
	{ "man", "love", "woman", NULL },	// �k�H �R �k�H
	{ "man", "date", "woman", NULL}, 	// �k�H �k�H �橹
	{ "man", "marry", "woman", NULL},	// �k�H �k�H ���B
	{ "man", "sex", "woman", NULL},		// �k�H �k�H ��t
	{ "woman", "born", "baby", NULL},	// �k�H �� �p��
	{ "baby", "growup", NULL, NULL},	// �p�� ���j
	{ "man", "woman", "extramarital", NULL}, // �~�J[�k�H (��t|�R) �t�@�Ӥk�H]
	{ "man", "divorce", "woman",  NULL}, // �k�H �k�H ���B
	{ NULL, NULL, NULL, NULL }
};

int main() {
	int i;
	for (i=0; sentences[i] != NULL; i++)
		semantics(sentences[i]);
}
