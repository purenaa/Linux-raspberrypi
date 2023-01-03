/* Q. BMP 파일 헤더만 이용해서 BMP 파일을 읽고 픽셀의 값을 출력하는 프로그램을 작성하세요. */
/* 입력 : BMP 파일 이름 */
/* 출력 : (255, 255, 255)  <--- RGB 픽셀의 값 */


#include <stdio.h>									/* 표준입출력에 관한 함수들이 정의되어 있는 헤더파일 */
#include <stdlib.h>									/* malloc-free 할당을 위해 사용 */

#include "bmpHeader.h"									/* BMP 헤더파일 */

typedef unsigned char ubyte;								/* unsigned char를 ubyte로 사용 */ 

int main(int argc, char**argv)								/* argc : 인자의 개수, argv : 인자의 배열 */
{
	FILE* fp;									/* 파일 포인터 */
	BITMAPFILEHEADER bmpHeader;							/* BITMAPFILEHEADER 구조체를 bmpHeader로 사용 */
	BITMAPINFOHEADER bmpInfoHeader;							/* BITMAPINFOHEADER 구조체를 bmpInfoHeader로 사용 */
	ubyte *inimg;									/* 입력 이미지 선언 */
	int x, y, imageSize;								/* x : 열, y : 행, imageSize : 총 이미지의 크기 */

	/* 인자의 개수가 2개가 아닐 경우 예외처리(argv[0] : 실행 파일 이름, argv[1] : 입력 이미지 파일 이름) */
	if(argc != 2) {
		fprintf(stderr, "usage : %s input.bmp\n", argv[0]);
		return -1;
	}

	/***** read bmp *****/										
	if((fp=fopen(argv[1], "rb")) == NULL) {						/* argv[1]이 NULL일 경우 예외처리 */
		fprintf(stderr, "Error : Failed to open file...\n");
		return -1;
	}

	/* BITMAPFILEHEADER 구조체의 데이터 */
	fread(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, fp);

	/* BITMAPINFOHEADER 구조체의 데이터 */
	fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

	/* 입력 이미지의 비트 수가 24비트가 아닐 경우 예외 처리 */
	if(bmpInfoHeader.biBitCount != 24) {
		perror("This image file doesn't supports 24bit color\n");
		fclose(fp);
		return -1;
	}

	int elemSize = bmpInfoHeader.biBitCount/8;					/* 24비트 이미지의 경우 24/8 = 3, 즉 elemSize가 3이 된다.  */
	int size = (bmpInfoHeader.biWidth)*elemSize;					/* size : 이미지 가로 크기 x 한 픽셀당 RGB, 즉 한 픽셀에 RGB를 포함한 총 가로의 크기 */
	imageSize = size * bmpInfoHeader.biHeight;					/* imageSize : 한 픽셀에 RGB를 포함한 총 이미지의 크기 */

	inimg = (ubyte*)malloc(sizeof(ubyte)*imageSize);				/* 총 이미지의 크기만큼 inimg의 메모리를 할당해준다. */
	
	fread(inimg, sizeof(ubyte), imageSize , fp);					/* inimg에 있는 데이터를 1*imageSize만큼 읽는다. */
	fclose(fp);												/* 파일 포인터를 닫음 */
	
	for(y = 0; y < bmpInfoHeader.biHeight; y++) {					/* y : 행, 즉 이미지의 높이만큼 for문을 반복한다. */
		for(x = 0; x < size; x+=elemSize) {					/* x : 열, 즉 이미지의 총 가로의 크기만큼 for문을 반복한다. */
			ubyte b = inimg[x+y*size+0];					/* 한 픽셀의 RGB값 중에서 Blue에 해당하는 값 */
            		ubyte g = inimg[x+y*size+1];					/* 한 픽셀의 RGB값 중에서 Green에 해당하는 값 */
            		ubyte r = inimg[x+y*size+2];					/* 한 픽셀의 RGB값 중에서 Red에 해당하는 값 */
			printf("r : %d, g : %d, b : %d\n", r, g, b);			/* 각각의 한 픽셀의 R, G, B값들을 출력  */
		}
	}

	free(inimg);									/* inimg 메모리 해제 */

	return 0;
}
