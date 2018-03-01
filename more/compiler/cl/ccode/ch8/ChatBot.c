// �`�N�A���{���� big5 �s�X�A�|���u�\�\�\�v���ĽX���D�A�ФŨϥΡu�\�\�\�v���r�C
#include <stdio.h>
#include <time.h>
#define LEN 512
#define QMAX 10
#define AMAX 20
char *empty="";

typedef struct {
	char *q[QMAX];
	char *a[AMAX];
} QA;

QA qa[]={
{ .q={"����", NULL}, .a={"���Ȯ�!", NULL} }, 
{ .q={"�藍�_", "��p", "���n�N��", NULL}, .a={"�O����p !", "�O�Ȯ�A���޻� !", NULL} }, 
{ .q={"�i�_", "�i���i�H", NULL}, .a={"�A�T�w�Q%s", NULL} }, 
{ .q={"�ڪ�", NULL}, .a={"�A��%s?", NULL} }, 
{ .q={"��", NULL}, .a={"�A����%s", NULL} }, 
{ .q={"�A�O", NULL}, .a={"�A�{���ڬO%s", NULL} }, 
{ .q={"�{��", "�H��", NULL}, .a={"����%s?", NULL} }, 
{ .q={"�Pı", NULL}, .a={"�`���o�طPı��?", NULL} }, 
{ .q={"����", NULL}, .a={"�A�Ʊ��%s", NULL} }, 
{ .q={"�O�_", NULL}, .a={"����Q���D�O�_%s", NULL} }, 
{ .q={"����", NULL}, .a={"���󤣯�%s?", "�A�չL�F��?", NULL} }, 
{ .q={"�ڬO", NULL}, .a={"�A�n�A�[���[��!", NULL} }, 
{ .q={"�ƻ�","����","���","��","����","�p��","����","�]��", NULL}, 
  .a={"����o�˰�?","����A��o���D������?","�A�{�����׬O�ƻ�O?", NULL} }, 
{ .q={"��]", NULL}, .a={"�o�O�u������]��?", "�o�O�u������]��?", NULL} }, 
{ .q={"�z��", NULL}, .a={"�o�����F�ƻ�O?", "�٦���L�z�Ѷ�?", NULL} }, 
{ .q={"�A�n","��","�z�n", NULL}, .a={"�A�n�A���ƻ���D��?", NULL} }, 
{ .q={"�Ϊ�", NULL}, .a={"�A�n�����ӽT�w?", NULL} }, 
{ .q={"�A�O", NULL}, .a={"�A�{���ڬO%s", NULL} }, 
{ .q={"����o","�����D", NULL}, .a={"���󤣪��D?","�b�Q�Q�ݡA���S���ƻ�i���?", NULL} }, 
{ .q={"���Q","���Ʊ�", NULL}, .a={"���S���ƻ��k�O?","���󤣷Q%s?","���A�Ʊ��˩O?", NULL} }, 
{ .q={"�Q","�Ʊ�", NULL}, .a={"����Q%s?","�u���Q%s?","���N�h����?","���󤣩O?", NULL} }, 
{ .q={"��", NULL}, .a={"����%s?", NULL} }, 
{ .q={"��", NULL}, .a={"�ڸӦp��%s","�A�Q�n��%s", NULL} }, 
{ .q={"�A", NULL}, .a={"�A�u���O�b���ڶ�?","�O���ڤF�A�ͽͧA�a!","����o�����ߧ�%s","�A�ۤv%s", NULL} }, 
{ .q={"�`�O","�`�`", NULL}, .a={"�ण����黡���O?","���?", NULL} }, 
{ .q={"��", NULL}, .a={"���h��?","���̹�?", NULL} }, 
{ .q={"��", NULL}, .a={"�A�T�w��?","�ڤF��!", NULL} }, 
{ .q={"�B��", NULL}, .a={"�h�i�D�ڤ@�Ǧ����L���Ƨa!","�A�{�ѥL�h�[�F�O?", NULL} }, 
{ .q={"�q��", NULL}, .a={"�A�����q���O���ڶ�?", NULL} }, 
{ .q={"���L", NULL}, .a={"�O�Q���F","�O���L","�O�Q����h�F","�Ʊ��`�O�|�ѨM�� ", NULL} }, 
{ .q={"����", NULL}, .a={"������","�ӴΤF","�o�˫ܦn��", NULL} }, 
{ .q={"�O��", "�O��", NULL}, .a={"�ƻ�ƩO?","�ڥi�H���U�A��?","�ڧƱ�گ����o�W��!", NULL} }, 
{ .q={"�q��", NULL}, .a={"�A�����q���O���ڶ�?", NULL} }, 
{ .q={NULL}, .a={"�ڤF��","�گ�z��","�٦����D�� ?","���~�򻡤U�h","�i�H������ԲӤ@�I��?",
"�o�˳�! �ڪ��D!","�M��O? �o�ͬƻ��?","�A�өO? �i�H�h���@�Ƕ�","���U�өO? ","�i�H�h�i�D�ڣ��Ƕ�?",
"�h�ͽͦ����A���ơA�n��?","���֧A","�Q�h�᣸���", NULL} }
};

void replace(char *source, char *target, char *from, char *to) {
	char *match = strstr(source, from);
	if (!match)
		strcpy(target, source);
	else {
		int len = match-source;
		strncpy(target, source, len);
		target[len] = '\0';
		sprintf(target+len, "%s%s", to, match+strlen(from));
	}
}
  
void delay(unsigned int secs) {
    time_t retTime = time(0) + secs;    // Get finishing time.
    while (time(0) < retTime);    		// Loop until it arrives.
}

void answer(char *question) {
	int i, qi, ai, acount;
	char *tail=empty;
    for (i=0; qa[i].q[0]!=NULL; i++) {
		for (qi=0; qa[i].q[qi]!=NULL; qi++) {
			char *q = qa[i].q[qi];
			char *match = strstr(question, q);
            if (match != NULL) {
                tail = match+strlen(q);
//				printf("match Q:%s tail:%s\n", q, tail);
				goto Found;
			}
		}
    }
Found:
	for (acount = 0; qa[i].a[acount] != NULL; acount++);
	ai = rand()%acount;
	delay(5+rand()%10);
	char youTail[LEN];
	replace(tail, youTail, "��", "�A");
	printf(qa[i].a[ai], youTail);
	printf("\n");
}

int main() {
	char question[LEN];
	printf("�z�n�A�ڪ��B��! ���ߨƶ� ?\n");
    do {
        printf(">> ");
        gets(question);
        answer(question);
    } while (!strcmp(question, "�A��")==0);
}
