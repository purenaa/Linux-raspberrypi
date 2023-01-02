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
	ubyte *inimg, *outimg;
	int i, imageSize;

	if(argc != 3) {
		fprintf(stderr, "usage : %s input.bmp out.bmp\n", argv[0]);
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
	outimg = (ubyte*)malloc(sizeof(ubyte)*imageSize);
	
	fread(inimg, sizeof(ubyte), imageSize , fp);
	fclose(fp);

	for(i = 0; i < imageSize; i += elemSize) {
		outimg[i+0] = inimg[i+0];
		outimg[i+1] = inimg[i+1];
		outimg[i+2] = inimg[i+2];
	}
	

	/***** write bmp *****/
	if((fp=fopen(argv[2], "wb"))==NULL) {
		fprintf(stderr, "Error : Failed to open file...\n");
		return -1;
	}
	
	/* BITMAPFILEHEADER 구조체의 데이터 */
	fwrite(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, fp);

	/* BITMAPINFOHEADER 구조체의 데이터*/
	fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	
	fwrite(outimg, sizeof(ubyte), imageSize, fp);
	
	fclose(fp);

	free(inimg);
	free(outimg);
	return 0;
}

		
