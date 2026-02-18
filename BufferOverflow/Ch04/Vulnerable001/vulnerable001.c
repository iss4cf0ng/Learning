//filename: vulnerable001.c

#include <stdlib.h>
#include <stdio.h>

void do_something(FILE *pfile) {
	char buf[128];
	fscanf(pfile, "%s", buf);
	
	//do file reading and parsing below
	//...
}

int main(int argc, char* argv[]) {
	char dummp[1024];
	FILE *pfile;
	
	printf("Vulnerable001 starts...");
	
	if (argc>=2) pfile = fopen(argv[1], "r");
	if (pfile) do_something(pfile);
	
	printf("Vulnerable001 ends...\n");
	
	return 0;
}
