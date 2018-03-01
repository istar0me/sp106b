#include "unicode.c"

#define LEN 512

int main(int argc, char *argv[]) {
	uinit(); // ��l��
	cedict();		// �]�w²�c�ഫ��
}

// ���J CC-CEDICT
int cedict() {
    FILE* inFile=uopen("cedict_ts.u16le", "rb");	// �}�� CC-CEDICT
    FILE* outFile=uopen("cedict_log.u16le", "wb");
    while(!feof(inFile)) {				 	// �@��Ū���ɮ׵���
		wchar_t line[LEN], head[LEN], tail[LEN], tc[LEN], sc[LEN], pr[LEN], en[LEN];
        if (fgetws(line, LEN, inFile)== NULL) 	// Ū�J (�c, ²)
			break;
		if (line[0] == '#') continue;
		fwprintf(outFile, L"line=%ls", line);
		swscanf(line, L"%s %s [%[^]]] /%[^/]", tc, sc, pr, en);
		fwprintf(outFile, L"tc=%ls sc=%ls pr=%ls en=%ls\n\n", tc, sc, pr, en);
    }
	fclose(inFile);	// ������J�� CC-CEDICT
	fclose(outFile); // ���� log ��X��
}
