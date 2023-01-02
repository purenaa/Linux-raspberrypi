/* 과제 : BMP 파일 헤더(책 480 페이지)만 이용해서 BMP 파일(lena.bmp)을 읽고 픽셀의 값을 출력하는 프로그램을 작성하세요. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "bmpHeader.h"

#define widthBytes(bits)(((bits)+31)/32*4)

/* 이미지 데이터의 경계 검사를 위한 매크로  */
#define LIMIT_UBYTE(n) ((n)>UCHAR_MAX) ? UCHAR_MAX : ((n)<0) ? 0 : (n)

typedef unsigned char ubyte;

int main(int argc, int **argv)
{
	FILE *fp;
	BITMAPFILEHEADER bmpHeader;			/* BMP FILE INFO */
	BITMAPINFOHEADER bmpInfoHeader;		/* BMP IMAGE INFO */
	RGBQUAD *palrgb;
	ubyte *inimg;
	int x, y, z, imageSize;
	float elemSize;

	if(argc != 2) {
		fprintf(stderr, "usage: %s input.bmp\n", argv[0]);
		return -1;
	}
   
	/* read bmp */
	if((fp=fopen(argv[1], "rb")) == NULL) { 
        fprintf(stderr, "Error : Failed to open file...₩n"); 
        return -1;
    }

	/* BITMAPFILEHEADER 구조체의 데이터 */
	fread(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	/* BITMAPINFOHEADER 구조체의 데이터 */
	fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

	if(bmpInfoHeader.SizeImage != 0)
		bmpInfoHeader.SizeImage = widthBytes(bmpInfoHeader.biBitCount * bmpInfoHeader.biWidth) * bmpInfoHeader.biHeight;

	/* 이미지의 해상도(넓이 x 깊이) */
	printf("Resolution : %d x %d\n", bmpInfoHeader.biWidth, bmpInfoHeader.biHeight);
    printf("Bit Count : %d\n", bmpInfoHeader.biBitCount);		/* 픽셀당 비트 수(색상) */
    printf("Image Size : %d\n", bmpInfoHeader.SizeImage);
    printf("Color : %d\n", bmpInfoHeader.biClrUsed);

	if(bmpInfoHeader.biBitCount == 8 && bmpInfoHeader.biClrUsed == 0)
        bmpInfoHeader.biClrUsed = 256;

	palrgb = (RGBQUAD*)malloc(sizeof(RGBQUAD)*bmpInfoHeader.biClrUsed);
    fread(palrgb, sizeof(RGBQUAD), bmpInfoHeader.biClrUsed, fp);

	int elemSize = bmpInfoHeader.biBitCount / 8;
	int size = bmpInfoHeader.biWidth * elemSize;
	imageSize = size * bmpInfoHeader.biHeight;

	for(int i = 0; i < bmpInfoHeader.biClrUsed; i++) 
        printf("%d : %x %x %x %x\n", i, palrgb[i].rgbRed, palrgb[i].rgbGreen, 
                              palrgb[i].rgbRed, palrgb[i].rgbReserved);

	inimg = (ubyte*)malloc(sizeof(ubyte)*bmpInfoHeader.SizeImage); 

	fread(inimg, sizeof(ubyte), bmpInfoHeader.SizeImage, fp);
	fclose(fp);

	elemSize = bmpInfoHeader.biBitCount / 8.;
    int pos = 0;

	printf("R : %f\n", );
	printf("G : ");

