#include "Image.h"

/* The spatial filtering supposes that the size of the given filter 
 * is odd rather than even for advantages
 */
void Image::spatialFiltering(
        const int l, int** filter, int(*filterFunc)(int, int*), bool linear) {

    if (img == NULL)
        return;

    int w = tempImg->width();
    int h = tempImg->height();
    QImage* auxImage = new QImage(w + l - 1, h + l - 1, tempImg->format());

    QRgb rgb;
    int r, g, b;
    int weight = 0;

    // get the sum of the filter
    if (linear) {
        for (int i = 0; i < l; ++i)
            for (int j = 0; j < l; j++)
                weight += filter[i][j];
    }

    // create an auxiliary image
    int begin = (l - 1) / 2;
    for (int i = begin; i < w + begin; ++i)
        for (int j = begin; j < h + begin; ++j)
            auxImage->setPixel(i, j, tempImg->pixel(i - begin, j - begin));

    // padding
    for (int i = begin - 1; i >= 0; --i)
        for (int j = 0; j < w; ++j)
            auxImage->setPixel(j, i, auxImage->pixel(j, i + 1));
    for (int i = h + 1; i <= h + begin; ++i)
        for (int j = 0; j < w; ++j)
            auxImage->setPixel(j, i, auxImage->pixel(j, i - 1));
    for (int i = begin - 1; i >= 0; --i)
        for (int j = 0; j < h; ++j)
            auxImage->setPixel(i, j, auxImage->pixel(i + 1, j));
    for (int i = w + 1; i <= w + begin; ++i)
        for (int j = 0; j < h; ++j)
            auxImage->setPixel(i, j, auxImage->pixel(i - 1, j));

    // filtering
    int* rArr = new int[l * l];
    int* gArr = new int[l * l];
    int* bArr = new int[l * l];
    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j) {
            // linear filtering
            if (linear) {
                r = g = b = 0;
                for (int m = 0; m < l; ++m)
                    for (int n = 0; n < l; ++n) {
                        rgb = auxImage->pixel(i + m, j + n);

                        r += qRed(rgb) * filter[m][n];	
                        g += qGreen(rgb) * filter[m][n];	
                        b += qBlue(rgb) * filter[m][n];	
                    }	
                if (weight != 0) {
                    r /= weight;
                    g /= weight;
                    b /= weight;
                }
            }

            // nonlinear filtering
            else {
                for (int m = 0; m < l; ++m)
                    for (int n = 0; n < l; ++n) {
                        rgb = auxImage->pixel(i + m, j + n);

                        rArr[m * l + n] = qRed(rgb);
                        gArr[m * l + n] = qGreen(rgb);
                        bArr[m * l + n] = qBlue(rgb);
                    }
                r = filterFunc(l, rArr);
                g = filterFunc(l, gArr);
                b = filterFunc(l, bArr);
            }

            r = r > 255 ? 255 : r;
            r = r <   0 ?   0 : r;
            g = g > 255 ? 255 : g;
            g = g <   0 ?   0 : g;
            b = b > 255 ? 255 : b;
            b = b <   0 ?   0 : b;

            img->setPixel(i, j, qRgb(r, g, b));
            //tempImg->setPixel(i, j, qRgb(r, g, b));
        }
    getHistogram();
    update();
}

void Image::laplace() {
    // create a laplace filter
    int** filter = new int*[3];
    for (int i = 0; i < 3; ++i)
        filter[i] = new int[3];

    filter[0][0] = 0;
    filter[0][1] = 1;
    filter[0][2] = 0;
    filter[1][0] = 1;
    filter[1][1] = -4;
    filter[1][2] = 1;
    filter[2][0] = 0;
    filter[2][1] = 1;
    filter[2][2] = 0;
    spatialFiltering(3, filter, NULL, true);
}

void Image::blur() {
    int** filter = new int*[3];
    for (int i = 0; i < 3; ++i)
        filter[i] = new int[3];

    filter[0][0] = 1;
    filter[0][1] = 1;
    filter[0][2] = 1;
    filter[1][0] = 1;
    filter[1][1] = 1;
    filter[1][2] = 1;
    filter[2][0] = 1;
    filter[2][1] = 1;
    filter[2][2] = 1;
    spatialFiltering(3, filter, NULL, true);
}

void Image::weightedBlur() {
    int** filter = new int*[3];
    for (int i = 0; i < 3; ++i)
        filter[i] = new int[3];

    filter[0][0] = 1;
    filter[0][1] = 2;
    filter[0][2] = 1;
    filter[1][0] = 2;
    filter[1][1] = 4;
    filter[1][2] = 2;
    filter[2][0] = 1;
    filter[2][1] = 2;
    filter[2][2] = 1;
    spatialFiltering(3, filter, NULL, true);
}

void Image::laplaceEnhance() {
    if (img == NULL)
        return;

    int w = tempImg->width();
    int h = tempImg->height();

    QImage* newImage = new QImage(w, h, tempImg->format());
    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j)
            newImage->setPixel(i, j, tempImg->pixel(i, j));

    laplace();

    tempImg = newImage;
    sub(*img);
    getHistogram();
    update();
}

void Image::unsharpMasking() {
    if (img == NULL)
        return;

    int w = tempImg->width();
    int h = tempImg->height();

    QImage* oriImage1 = new QImage(w, h, tempImg->format());
    QImage* oriImage2 = new QImage(w, h, tempImg->format());
    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j) {
            oriImage1->setPixel(i, j, tempImg->pixel(i, j));
            oriImage2->setPixel(i, j, tempImg->pixel(i, j));
        }

    blur();
    tempImg = oriImage1;
    sub(*img);
    tempImg = oriImage2;
    add(*img);

    getHistogram();
    update();
}

void Image::highBoost() {
    if (img == NULL)
        return;

    int w = tempImg->width();
    int h = tempImg->height();

    QImage* oriImage1 = new QImage(w, h, tempImg->format());
    QImage* oriImage2 = new QImage(w, h, tempImg->format());
    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j) {
            oriImage1->setPixel(i, j, tempImg->pixel(i, j));
            oriImage2->setPixel(i, j, tempImg->pixel(i, j));
        }

    blur();
    tempImg = oriImage1;
    sub(*img);
    scale(2);
    tempImg = oriImage2;
    add(*img);

    getHistogram();
    update();
}

void Image::add(QImage otherImg) {
    int w = tempImg->width();
    int h = tempImg->height();
    QRgb rgb1, rgb2;
    int r, g, b;

    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j) {
            rgb1 = tempImg->pixel(i, j);
            rgb2 = otherImg.pixel(i, j);

            r = qRed(rgb1) + qRed(rgb2);
            g = qGreen(rgb1) + qGreen(rgb2);
            b = qBlue(rgb1) + qBlue(rgb2);

            r = r > 255 ? 255 : r;
            r = r <   0 ?   0 : r;
            g = g > 255 ? 255 : g;
            g = g <   0 ?   0 : g;
            b = b > 255 ? 255 : b;
            b = b <   0 ?   0 : b;

            img->setPixel(i, j, qRgb(r, g, b));
            tempImg->setPixel(i, j, qRgb(r, g, b));
        }
}

void Image::sub(QImage otherImg) {
    int w = tempImg->width();
    int h = tempImg->height();
    QRgb rgb1, rgb2;
    int r, g, b;

    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j) {
            rgb1 = tempImg->pixel(i, j);
            rgb2 = otherImg.pixel(i, j);

            r = qRed(rgb1) - qRed(rgb2);
            g = qGreen(rgb1) - qGreen(rgb2);
            b = qBlue(rgb1) - qBlue(rgb2);

            r = r > 255 ? 255 : r;
            r = r <   0 ?   0 : r;
            g = g > 255 ? 255 : g;
            g = g <   0 ?   0 : g;
            b = b > 255 ? 255 : b;
            b = b <   0 ?   0 : b;

            img->setPixel(i, j, qRgb(r, g, b));
            tempImg->setPixel(i, j, qRgb(r, g, b));
        }
}

void Image::scale(const int factor) {
    int w = tempImg->width();
    int h = tempImg->height();
    QRgb rgb;
    int r, g, b;

    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j) {
            rgb = tempImg->pixel(i, j);

            r = factor * qRed(rgb); 
            g = factor * qGreen(rgb);
            b = factor * qBlue(rgb);

            r = r > 255 ? 255 : r;
            r = r <   0 ?   0 : r;
            g = g > 255 ? 255 : g;
            g = g <   0 ?   0 : g;
            b = b > 255 ? 255 : b;
            b = b <   0 ?   0 : b;

            img->setPixel(i, j, qRgb(r, g, b));
            tempImg->setPixel(i, j, qRgb(r, g, b));
        }
}

void Image::medianFiltering() {
    int (*filterFunc)(int, int*) = median;
    spatialFiltering(3, NULL, filterFunc, false);
}


void Image::maximumFiltering() {
    int (*filterFunc)(int, int*) = maximum;
    spatialFiltering(3, NULL, filterFunc, false);
}

void Image::minimumFiltering() {
    int (*filterFunc)(int, int*) = minimum;
    spatialFiltering(3, NULL, filterFunc, false);
}

int median(int l, int* window) {
    sort(window, window + l * l);
    return window[(l * l + 1) / 2];
}

int maximum(int l, int* window) {
    sort(window, window + l * l);
    return window[l * l - 1];
}

int minimum(int l, int* window) {
    sort(window, window + l * l);
    return window[0];
}
