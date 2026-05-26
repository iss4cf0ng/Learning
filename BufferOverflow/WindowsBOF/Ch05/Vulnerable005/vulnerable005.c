//vulnerable005.c
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

char rock[0xE000] = "...some data";
char Rahab[0x2000] = "\x90\x58\x58\xc3"; //NOP/POP/POP/RET

void foo(void *src_buf, size_t const len) {
	size_t const BUF_LEN = 128;
	char bad_buf[BUF_LEN];
	
	memcpy(bad_buf, src_buf, len * 2); //bad usage!
}

int main(int argc, char *argv[]) {
	size_t const STR_LEN = 4096;
	wchar_t *unicode_buf = malloc(STR_LEN);
	char ascii_buf[STR_LEN];
	FILE *pfile;
	int rt;
	
	printf("Vulnerable005 starts...\n");
	
	if (argc >= 2) {
		pfile = fopen(argv[1], "r");
		fscanf(pfile, "%s", ascii_buf);
		rt = MultiByteToWideChar(CP_UTF7, 0, ascii_buf, -1, unicode_buf, STR_LEN);
		if (rt == 0) {
			return -1;
		}
		
		foo(unicode_buf, rt * 2);
	}
	
	printf("Vulnerable005 ends...\n");
	free(unicode_buf);
}
