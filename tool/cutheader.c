#include <stdio.h>
#include <stdlib.h>
#include <sys/dos.h>
#include <sys/param.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	int siz;
	char *adr;

	if (argc != 3) {
		printf("cutheader.x INfile OUTfile\n");
		return 0;
	}

	fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		perror(argv[1]);
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	siz = ftell(fp);
	siz = siz - 0x1c;
	adr = malloc(siz);
	if (adr == NULL) {
		perror("malloc");
		exit(1);
	}
	fseek(fp, 0x1c, SEEK_SET);
	fread(adr, 1, siz, fp);
	fclose(fp);

	fp = fopen(argv[2], "wb");
	if (NULL == fp) {
		perror(argv[2]);
		exit(1);
	}
	fwrite(adr, 1, siz, fp);
	fclose(fp);

	free(adr);

	return 0;
}
