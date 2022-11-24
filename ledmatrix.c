#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

#define FBDEVICE        "/dev/fb1"

extern inline unsigned short makepixel(unsigned char r, unsigned char g, unsigned char b)
{
    return (unsigned short)(((r>>3) << 11) | ((g>>2) << 5) | (b>>3));
}

int main(void)
{
    struct fb_fix_screeninfo finfo;
    struct fb_var_screeninfo vinfo;
    unsigned short *pfb;
    int fbfd, size;

    fbfd = open(FBDEVICE, O_RDWR);
    if(fbfd < 0) {
        perror("Error: cannot open framebuffer device");
        return EXIT_FAILURE;
    }

    ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo);
    if(strcmp(finfo.id, "RPi-Sense FB") != 0) {
        printf("%s\n", "Error: Rpi-Sense FB not found");
        close(fbfd);
        return EXIT_FAILURE;
    }

    if(ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) < 0) {
        perror("Error reading fixed information");
        return EXIT_FAILURE;
    }

    size = vinfo.xres * vinfo.yres * sizeof(short);

    pfb = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if(pfb == MAP_FAILED) {
        close(fbfd);
        perror("Error mmapping the file");
        return EXIT_FAILURE;
    }

    memset(pfb, 0, size);
    *(pfb+3+3*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+2+2*vinfo.xres) = makepixel(255, 0, 127); 
    *(pfb+2+3*vinfo.xres) = makepixel(255, 0, 127); 
    *(pfb+1+3*vinfo.xres) = makepixel(255, 0, 127); 
    *(pfb+1+2*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+0+3*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+1+4*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+2+4*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+3+4*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+4+4*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+5+4*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+3+5*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+4+5*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+2+5*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+3+6*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+4+6*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+5+5*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+5+3*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+6+3*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+6+4*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+7+3*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+6+2*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+5+2*vinfo.xres) = makepixel(255, 0, 127);
    *(pfb+4+3*vinfo.xres) = makepixel(255, 0, 127);
   // *(pfb+1+4*vinfo.xres) = makepixel(255, 0, 127);
  // *(pfb+2+2*vinfo.xres) = makepixel(0, 255, 0);
   // *(pfb+4+4*vinfo.xres) = makepixel(0, 0, 255);
   // *(pfb+6+6*vinfo.xres) = makepixel(255, 0, 255);

    if(munmap(pfb, size) == -1) {
        perror("Error un-mmapping the file");
    }
    close(fbfd);

    return EXIT_SUCCESS;
}

