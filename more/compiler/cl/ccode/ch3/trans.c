#include "unicode.c"

#define UMAX 65536 // UTF16 ���r�̦h 65536 �ӡC
wchar_t zmap[UMAX] /*�c��²���*/, smap[UMAX]/*²���c���*/;

int main(int argc, char *argv[]) {
	uinit(); // ��l��
	tsmap();		// �]�w²�c�ഫ��
	if (argc != 4) help(); // �ˬd�Ѽ�
	if (strcmp(argv[1], "t2s")==0)// �p�G�O t2s�A�c��²
		translate(zmap, argv[2], argv[3]);
	else if (strcmp(argv[1], "s2t")==0)// �p�G�O s2t�A²���c
		translate(smap, argv[2], argv[3]);
	else // �_�h��� help()
		help(); 
}

int help() { // ��ܨϥΤ�k
	printf("trans <mode> <fromFile> <toFile>\n"
		   "<mode>={z2s or s2z}\n");	
}

// �ھ� map �i���ഫ�C zmap: �c��² , smap: ²���c�C
int translate(wchar_t *map, char *inFileName, char *outFileName) {
    FILE* inFile=uopen(inFileName, "rb"); 	// �}�ҿ�J�� (UTF-16 �榡)
    FILE* outFile=uopen(outFileName, "wb");	// �إ߿�X�� (UTF-16 �榡)
    while(1) { // �@��Ū
		wchar_t c = fgetwc(inFile); // Ū�@�Ӧr��
		if (feof(inFile)) // �p�G�w�g���ɧ��A���}�õ���
			break;
		if (map[c] == 0)  // �p�G�r�����ഫ���s�b
			fputwc(c, outFile); // �����N�r����X
		else
			fputwc(map[c], outFile); // �_�h�N�ഫ�᪺�r����X
    }
	fclose(inFile);		// ������J��
	fclose(outFile);	// ������X��
}

// ���J²�c�ഫ��
int tsmap() {
	memset(zmap, 0, sizeof(wchar_t)*UMAX); 	// �M���c��²���
	memset(smap, 0, sizeof(wchar_t)*UMAX); 	// �M��²���c���
    FILE* inFile=uopen("t2s.txt", "rb");	// �}���c²��Ӫ� (UTF-16 �榡)
    while(!feof(inFile)) {				 	// �@��Ū���ɮ׵���
		wchar_t zs[10];					 
        if (fgetws(zs, 10, inFile)== NULL) 	// Ū�J (�c, ²)
			break;
		wchar_t z = zs[0], s=zs[1]; 		// �]�w (z=�c, s=²)
		if (z!=s) {
			zmap[z] = s;					// zmap[�c]=²
			smap[s] = z;					// smap[²]=�c
		}
    }
	fclose(inFile);							// �����c²��Ӫ�
}
