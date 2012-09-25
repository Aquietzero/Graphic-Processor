#include "Image.h"

void Image::fixedHalftoning(const int r, const int c, int** arr) {
    if (img == NULL)
        return;

    float level = 256 / (r * c + 1);

    int w = tempImg->width();
    int h = tempImg->height();
    int R, G, B;
    int newR, newG, newB;
    QRgb rgb;

    QImage* newImage = new QImage(w, h, tempImg->format());
    for (int i = 0; i < w; i += r)
        for (int j = 0; j < h; j += c) {
            R = G = B = 0;
            for (int m = 0; m < c && i + m < w; ++m)
                for (int n = 0; n < r && j + n < h; ++n) {
                    rgb = tempImg->pixel(i + m, j + n);
                    R += qRed(rgb);
                    G += qGreen(rgb);
                    B += qBlue(rgb);
                }
            R /= level * r * c;
            G /= level * r * c;
            B /= level * r * c;

            for (int m = 0; m < c && i + m < w; ++m)
                for (int n = 0; n < r && j + n < h; ++n) {
                    newR = R < arr[m][n] ? 0 : 255;
                    newG = G < arr[m][n] ? 0 : 255;
                    newB = B < arr[m][n] ? 0 : 255;

                    newImage->setPixel(i + m, j + n, 
                            qRgb(newR, newG, newB));
                }
        }
    img = newImage;
    getHistogram();
    tempSaveImage();
    update();
}

/* The image will expand according to the size of the given halftoning
 * pattern so that each of the pixel in the original image matches a
 * complete pattern.
 */
void Image::expandHalftoning(const int r, const int c, int** arr) {
    if (img == NULL)
        return;

    int w = tempImg->width() * r;
    int h = tempImg->height() * c;
    float level = 256 / (r * c + 1);

    int R, G, B;
    int newR, newG, newB;
    QRgb rgb;

    QImage* newImage = new QImage(w, h, tempImg->format());
    for (int i = 0; i < w; i += r)
        for (int j = 0; j < h; j += c) {
            rgb = tempImg->pixel(i / c, j / r);

            R = qRed(rgb) / level;
            G = qGreen(rgb) / level;
            B = qBlue(rgb) / level;

            for (int m = 0; m < c; ++m)
                for (int n = 0; n < r; ++n) {
                    newR = R < arr[m][n] ? 0 : 255;	
                    newG = G < arr[m][n] ? 0 : 255;	
                    newB = B < arr[m][n] ? 0 : 255;	

                    newImage->setPixel(i + m, j + n, 
                            qRgb(newR, newG, newB));
                }
        }
    img = newImage;
    getHistogram();
    tempSaveImage();
    update();
}
