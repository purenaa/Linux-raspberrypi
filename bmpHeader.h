#ifndef __BMP_FILE_H__
#define __BMP_FILE_H__

typedef struct __attribute__((__packed__)) {
    unsigned short bfType;
    unsigned int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
    unsigned int biSize;
    unsigned int biWidth;
    unsigned int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int SizeImage;
    unsigned int bixPelsPerMeter;
    unsigned int biYpelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
} BITMAPINFOHEADER;

typedef struct {
    unsigned char rgbBule;
    unsigned char rgbGreen;
    unsigned char rgbRed;
    unsigned char rgbResserved;
} RGBQUAD;

#endif /* __BMP_FILE_H__ */
