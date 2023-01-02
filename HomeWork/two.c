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
	RGBQUAD *palrgb;
	ubyte *inimg, *outimg;
	int x, y, imageSize;

	if(argc != 3) {
        fprintf(stderr, "usage : %s input.bmp output.bmp\n", argv[0]);
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
	
	for(y = 0; y < bmpInfoHeader.biHeight; y++) {
		for(x = 0; x < size; x+=elemSize) {
			outimg[x+y*size+0] = inimg[x+y*size+0];
            outimg[x+y*size+1] = inimg[x+y*size+1];
            outimg[x+y*size+2] = inimg[x+y*size+2];
		}
	}

	palrgb = (RGBQUAD*)malloc(sizeof(RGBQUAD)*256);
    for(x = 0; x < 256; x++) {
        palrgb[x].rgbBlue = palrgb[x].rgbGreen = palrgb[x].rgbRed = x;
        palrgb[x].rgbReserved = 0;
    }	
	
	if((fp=fopen(argv[2], "wb"))==NULL) {
		fprintf(stderr, "Error : Failed to open file...\n");
		return -1;
	}

	bmpHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*256;
    bmpHeader.bfSize = bmpHeader.bfOffBits + bmpInfoHeader.SizeImage;
	
	/* BITMAPFILEHEADER 구조체의 데이터 */
	fwrite(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, fp);

	/* BITMAPINFOHEADER 구조체의 데이터*/
	fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

	fwrite(palrgb, sizeof(RGBQUAD), 256, fp);
	fwrite(outimg, sizeof(ubyte), imageSize, fp);

	fclose(fp);

	free(inimg);
	free(palrgb);
	free(outimg);
	
	return 0;
}
	
