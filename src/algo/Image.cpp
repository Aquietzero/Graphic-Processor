#include "Image.h"
#include <iostream>
#include <cmath>
#include <QFile>
#include <QTextStream>

Image::Image(QWidget* parent)
    : QWidget(parent) {
        img     = NULL;	
        tempImg = NULL;	
        oldImg  = NULL;	
        imgHistogramR = NULL;
        imgHistogramG = NULL;
        imgHistogramB = NULL;

        setMinimumWidth(512);
        setMinimumHeight(512);
        update();
    }

Image::Image(QString filename, QWidget* parent)
    : QWidget(parent) {
        img     = new QImage(filename);
        tempImg = new QImage(filename);
        oldImg  = new QImage(filename);
        imgName = filename;

        if (img->colorCount() != 0) {
            convert(&img);
            convert(&tempImg);
            convert(&oldImg);
        }

        int w = img->width();
        int h = img->height();
        setMinimumWidth(w);
        setMinimumHeight(h);

        getHistogram();
        update();

        /* TODO
         * add some code to detect whether the loading is successful
         * or not.
         */
    }

Image& Image::operator=(const Image &otherImage) {
    img     = new QImage(*(otherImage.img));
    tempImg = new QImage(*(otherImage.img));
    oldImg  = new QImage(*(otherImage.img));
    imgName = otherImage.imgName;
    return *this;
}

void Image::convert(QImage** otherImg) {
    QImage* newImg = new QImage((*otherImg)->size(), QImage::Format_RGB32);
    int w = (*otherImg)->width();
    int h = (*otherImg)->height();

    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j) {
            int grey = (*otherImg)->pixel(i, j);
            newImg->setPixel(i, j, qRgb(grey, grey, grey));
        }
    *otherImg = newImg;
}

void Image::setImage(const QString &filename) {
    img     = new QImage(filename);
    tempImg = new QImage(filename);
    oldImg  = new QImage(filename);
    imgName = filename;

    if (img->colorCount() != 0) {
        convert(&img);
        convert(&tempImg);
        convert(&oldImg);
    }

    getHistogram();
    update();
}

bool Image::writeImage(const QString &filename) {
    tempImg = new QImage(*img);
    oldImg  = new QImage(*img);

    getHistogram();
    return img->save(filename);
}

void Image::tempSaveImage() {
    QImage* newImg = new QImage(img->size(), img->format());
    int w = img->width();
    int h = img->height();

    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j)
            newImg->setPixel(i, j, img->pixel(i, j));

    tempImg = newImg;
    getHistogram();
    update();
}

void Image::tempRestoreImage() {
    QImage* newImg = new QImage(tempImg->size(), tempImg->format());
    int w = tempImg->width();
    int h = tempImg->height();

    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j)
            newImg->setPixel(i, j, tempImg->pixel(i, j));

    img = newImg;
    getHistogram();
    update();
}

void Image::originalImage() {
    QImage* newImg = new QImage(oldImg->size(), oldImg->format());
    QImage* newImg2 = new QImage(oldImg->size(), oldImg->format());
    int w = oldImg->width();
    int h = oldImg->height();

    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j) {
            newImg->setPixel(i, j, oldImg->pixel(i, j));
            newImg2->setPixel(i, j, oldImg->pixel(i, j));
        }

    img = newImg;
    tempImg = newImg2;
    getHistogram();
    update();
}

void Image::paintEvent(QPaintEvent* event) {
    if (img != NULL) {
        QPainter painter(this);
        painter.drawImage(0, 0, *img);
        setFixedSize(img->size());
    }
}
