#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include "bmpHeader.h"

typedef unsigned char ubyte;

int main(int argc, char**argv)
{
	FILE* fp;
	BITMAPFILEHEADER bmpHeader;
	BITMAPINFOHEADER bmpInfoHeader;
	ubyte *inimg;
	int x, y, imageSize;

	if(argc != 2) {
		fprintf(stderr, "usage : %s input.bmp\n", argv[0]);
		return -1;
	}

	/***** read bmp *****/
	if((fp=fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "Error : Failed to open file...\n");
		return -1;
	}

	/* BITMAPFILEHEADER 구조체의 데이터 */
	fread(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, fp);

	/* BITMAPINFOHEADER 구조체의 데이터 */
	fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

	if(bmpInfoHeader.biBitCount != 24) {
		perror("This image file doesn't supports 24bit color\n");
		fclose(fp);
		return -1;
	}

	int elemSize = bmpInfoHeader.biBitCount/8;
	int size = (bmpInfoHeader.biWidth)*elemSize;
	imageSize = size * bmpInfoHeader.biHeight;

	inimg = (ubyte*)malloc(sizeof(ubyte)*imageSize);
	fread(inimg, sizeof(ubyte), imageSize , fp);
	fclose(fp);
	
	for(y = 0; y < bmpInfoHeader.biHeight; y++) {
		for(x = 0; x < size; x+=elemSize) {
			ubyte b = inimg[x+y*size+0];
            ubyte g = inimg[x+y*size+1];
            ubyte r = inimg[x+y*size+2];
			printf("r : %d, g : %d, b : %d\n", r, g, b);
		}
	}
	//fwrite(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	//fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

	free(inimg);

	return 0;
}

		
