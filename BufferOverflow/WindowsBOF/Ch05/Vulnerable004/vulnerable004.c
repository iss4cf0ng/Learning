//vulnerable004.c
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	FILE *pFile;
	char *long_buffer;
	char short_buf[64];
	printf("Vulnerable004 starts...\n");
	
	if (argc >= 2) pFile = fopen(argv[1], "r");
	if (pFile) {
		long_buffer = malloc(2048);
		fscanf(pFile, "%s", long_buffer);
		
		//do something
		
		free(long_buffer);
		
		fscanf(pFile, "%s", short_buf);
	}
	
	printf("Vulnerable004 ends...\n");
}
