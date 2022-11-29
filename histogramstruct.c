#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmpHeader.h"

#define BYTE	unsigned char
#define BASE    16

#define widthbytes(bits)   (((bits)+31)/32*4)

inline unsigned char clip(int value, int min, int max);
unsigned char clip(int value, int min, int max)
{
    return(value > max? max : value < min? min : value);
}

int main(int argc, char** argv)
{
	FILE *fp;
	RGBQUAD palrgb[256];
    
    /* BMP FILE INFO */
	unsigned short int type;  
	unsigned int file_size;   
	unsigned short int reserved1; 
	unsigned short int reserved2; 
	unsigned int offset;   
	
    /* BMP IMAGE INFO */
	unsigned int header_size;  
	int width,height;    
	unsigned short int planes;  
	unsigned short int bits;  
	unsigned int compression;  
	unsigned int imagesize;   
	int hresolution,vresolution; 
	unsigned int ncolors;   
	unsigned int importantcolors; 
	char input[128], output[128];

	float r, g, b, gray;
 
	int i, j, size, index;
	unsigned long histogram[256];
	unsigned char *inimg;
	unsigned char *outimg;
 
	strcpy(input, argv[1]);
	strcpy(output, argv[2]);
 
	if((fp = fopen(input, "rb")) == NULL) {
		fprintf(stderr, "Error : Failed to open file...\n");
		exit(EXIT_FAILURE);
	}
#if 1
    BITMAPFILEHEADER bmpHeader;
    fread(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, fp);
#else
	fread(&type, sizeof(unsigned short int), 1, fp);
	fread(&file_size, sizeof(unsigned int), 1, fp);
	fread(&reserved1, sizeof(unsigned short int), 1, fp);
	fread(&reserved2, sizeof(unsigned short int), 1, fp);
	fread(&offset, sizeof(unsigned int), 1, fp);
#endif

#if 1
    BITMAPINFOHEADER bmpInfoHeader;
    fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
#else	
	fread(&header_size, sizeof(unsigned int), 1, fp);
	fread(&width, sizeof(int), 1, fp);
	fread(&height, sizeof(int), 1, fp);
	fread(&planes, sizeof(unsigned short int), 1, fp);
	fread(&bits, sizeof(unsigned short int), 1, fp);
	fread(&compression, sizeof(unsigned int), 1, fp);
	fread(&imagesize, sizeof(unsigned int), 1, fp);
	fread(&hresolution, sizeof(int), 1, fp);
	fread(&vresolution, sizeof(int), 1, fp);
	fread(&ncolors, sizeof(unsigned int), 1, fp);
	fread(&importantcolors, sizeof(unsigned int), 1, fp);
#endif
	size = widthbytes(bmpInfoHeader.biBitCount * bmpInfoHeader.biWidth);

    imagesize = bmpInfoHeader.SizeImage;
	if(!imagesize) 
	    imagesize = bmpInfoHeader.biHeight * size;

	inimg = (BYTE*)malloc(sizeof(BYTE)*imagesize);
	outimg = (BYTE*)malloc(sizeof(BYTE)*imagesize);
	fread(inimg, sizeof(BYTE), imagesize, fp);
	
	fclose(fp);
 
    printf("Image width : %d, height : %d(%d)\n",
            bmpInfoHeader.biWidth, bmpInfoHeader.biHeight, bmpInfoHeader.biWidth*bmpInfoHeader.biHeight);
	
	for(i = 0; i < 256; i++) histogram[i] = 0;
 
	for(i = 0; i < bmpInfoHeader.biHeight; i++) {
		index = (bmpInfoHeader.biHeight-i-1) * size; 
		for(j = 0 ; j < bmpInfoHeader.biWidth; j++) { 
			r = (float)inimg[index+3*j+2];
			g = (float)inimg[index+3*j+1];
			b = (float)inimg[index+3*j+0];
			gray = (r*0.3F)+(g*0.59F)+(b*0.11F);
			histogram[(unsigned char)(gray)] += 1;
			outimg[index+3*j] = outimg[index+3*j+1] = outimg[index+3*j+2] = gray;
		};
	};

    for(i = 0; i < 256; i++) {
		printf("%-3d  ", i);
		if(!(int)(histogram[i]/bmpInfoHeader.biHeight) && (histogram[i]%bmpInfoHeader.biHeight))
		   printf("*");
		else for(j = 0; j < (int)(histogram[i]/bmpInfoHeader.biHeight); j++)
		   printf("*");
		printf("  %d\n", histogram[i]);
    };
	
	offset += 256*sizeof(RGBQUAD); 

	if((fp = fopen(output, "wb")) == NULL) {
		fprintf(stderr, "Error : Failed to open file...\n");
		exit(EXIT_FAILURE);
	}
 
#if 1
	fwrite(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, fp);
#else
	fwrite(&type, sizeof(unsigned short int), 1, fp);
	fwrite(&file_size, sizeof(unsigned int), 1, fp);
	fwrite(&reserved1, sizeof(unsigned short int), 1, fp);
	fwrite(&reserved2, sizeof(unsigned short int), 1, fp);
	fwrite(&offset, sizeof(unsigned int), 1, fp);
#endif

#if 1
    fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
#else
	fwrite(&header_size, sizeof(unsigned int), 1, fp);
	fwrite(&width, sizeof(int), 1, fp);
	fwrite(&height, sizeof(int), 1, fp);
	fwrite(&planes, sizeof(unsigned short int), 1, fp);
	fwrite(&bits, sizeof(unsigned short int), 1, fp);
	fwrite(&compression, sizeof(unsigned int), 1, fp);
	fwrite(&imagesize, sizeof(unsigned int), 1, fp);
	fwrite(&hresolution, sizeof(int), 1, fp);
	fwrite(&vresolution, sizeof(int), 1, fp);
	fwrite(&ncolors, sizeof(unsigned int), 1, fp);
	fwrite(&importantcolors, sizeof(unsigned int), 1, fp);
	fwrite(palrgb, sizeof(unsigned int), 256, fp);
	fwrite(outimg, sizeof(unsigned char), imagesize, fp);
#endif
    
    fwrite(palrgb, sizeof(unsigned int), 256, fp);

	fwrite(outimg, sizeof(unsigned char), imagesize, fp);
	
	free(inimg);
	free(outimg);

	fclose(fp);

        return 0;
}
