/*
 * rawrite for Human68k
 * -- Write a binary image to 1200K diskette.
 *    by Masaru Oki
 *
 * Usage:
 *	Human prompt> RAWRITE
 *
 *	And follow the prompts.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/dos.h>
#include <sys/param.h>
#include <ctype.h>

#define BYTEPERTRACK	(1024)
#define SECTORPERTRACK	(16)
#define SECTORPERSIDE	(8)

int
main()
{
	char fname[MAXPATHLEN];
	FILE *fp;
	int siz;
	char *adr;
	char drive;
	int	nTrack, nSector, nSide;
	int	nStartSector;
	
	printf("RaWrite 1.2 - Write disk file to raw floppy diskette\n");
	printf("Enter source file name: ");
	scanf("%s", fname);
	fp = fopen(fname, "rb");
	if (fp == NULL) {
		perror(fname);
		exit(1);
	}

	printf("Enter side(0 or 1): ");
	scanf("%d", &nSide);
	printf("Enter track number(0-167): ");
	scanf("%d", &nTrack);
	printf("Enter sector number(1-8): ");
	scanf("%d", &nSector);

	nStartSector = nTrack * SECTORPERTRACK + (nSector-1);
	if (nSide == 1) nStartSector += SECTORPERSIDE;
	printf("start sector:%d\n", nStartSector);

	printf("Enter destination drive: ");
	scanf("%s", fname);
	drive = fname[0];
	drive = (islower(drive) ? toupper(drive) : drive) - 'A';

	fseek(fp, 0, SEEK_END);
	siz = ftell(fp);
	printf("file size(byte): %d\n", siz);
	// ファイルサイズが1024で割り切れない場合、1024バイトで整える
	if (siz % BYTEPERTRACK != 0) siz = (siz / BYTEPERTRACK) * BYTEPERTRACK + BYTEPERTRACK;
	printf("write size(byte): %d, write sector num: %d\n", siz, siz/BYTEPERTRACK);

	fseek(fp, 0, SEEK_SET);
	adr = malloc(siz);
	if (adr == NULL) {
		perror("malloc");
		exit(1);
	}
	printf("Reading image\n");
	fread(adr, 1, siz, fp);
	fclose(fp);

	printf("Please insert a formatted diskette into ");
	printf("drive %c: and press -ENTER- :", drive + 'A');
	fflush(stdin);
	getchar();

	printf("\nWriting image to drive %c:", drive+'A');
	// 第三引数はSector番号
	// 第四引数はセクタ数
	_dos_diskwrt2(adr, drive + 1, nStartSector, siz / BYTEPERTRACK);

	printf("\nDone.\n");
	fflush(stdin);

	return 0;
}
