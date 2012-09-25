#include "Image.h"

void Image::gaussianNoise(double mean, double standardDeviation) {
    int w = img->width();
    int h = img->height();
    int r, g, b;
    QRgb rgb;
    double noise;

    srand(unsigned(time(NULL)));
    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j) {
            noise = gaussGenerator(mean, standardDeviation); 

            rgb = tempImg->pixel(i, j);
            r = qRed(rgb); 
            g = qGreen(rgb);
            b = qBlue(rgb);

            r += (int)noise;
            g += (int)noise;
            b += (int)noise;

            r = r > 255 ? 255 : r;
            r = r <   0 ?   0 : r;
            g = g > 255 ? 255 : g;
            g = g <   0 ?   0 : g;
            b = b > 255 ? 255 : b;
            b = b <   0 ?   0 : b;

            img->setPixel(i, j, qRgb(r, g, b));
        }

    getHistogram();
    update();
}

void Image::impulseNoise(double pa, double pb) {
    int w = img->width();
    int h = img->height();
    int r, g, b;
    QRgb rgb;
    double noise;

    srand(unsigned(time(NULL)));
    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j) {
            noise = impulseGenerator(pa, pb);

            rgb = tempImg->pixel(i, j);

            r = qRed(rgb); 
            g = qGreen(rgb);
            b = qBlue(rgb);

            if (noise == -1)
                r = g = b = 0;
            else if (noise == 1)
                r = g = b = 255;

            r = r > 255 ? 255 : r;
            r = r <   0 ?   0 : r;
            g = g > 255 ? 255 : g;
            g = g <   0 ?   0 : g;
            b = b > 255 ? 255 : b;
            b = b <   0 ?   0 : b;

            img->setPixel(i, j, qRgb(r, g, b));
        }
    getHistogram();
    update();
}
