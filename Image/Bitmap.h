#include <stdio.h>
#include <math.h>
#include <bitset>

#ifndef BITMAP_H
#define BITMAP_H
typedef uint8_t BYTE;

class Bitmap {
    typedef struct {
        unsigned short bfType;
        unsigned int bfSize;
        unsigned short bfReserved1;
        unsigned short bfReserved2;
        unsigned int bfOffBits;
    } bmpFHEAD;

    typedef struct bmpIHEAD {
        unsigned int biSize;
        int biWidth;
        int biHeight;
        unsigned short biPlanes;
        unsigned short biBitCount;
        unsigned int biCompression;
        unsigned int biSizeImage;
        int biXPelsPerMeter;
        int biYPelsPerMeter;
        unsigned int biClrUsed;
        unsigned int biClrImportant;
    } bmpIHEAD;

    typedef struct bmpPAL {
        unsigned char r;
        unsigned char g;
        unsigned char b;
    } PAL;

    int width, height;

public:
    unsigned char *data;

    Bitmap(void);

    bool create(int x, int y);

    bool load(const char *filename);

    bool save(const char *filename);

    int getwidth(void) {
        if (data) return width; else return -1;
    };

    int getheight(void) {
        if (data) return height; else return -1;
    };

    void getcolor(int x, int y, BYTE &r, BYTE &g, BYTE &b);

    void setcolor(int x, int y, BYTE r, BYTE g, BYTE b);

    ~Bitmap(void);
};

#endif