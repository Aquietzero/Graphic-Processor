#ifndef IMAGE_H
#define IMAGE_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <algorithm>
// #include <fftw3.h>

#include "random.h"

using namespace std;

class Image : public QWidget {

    Q_OBJECT;

    public:
    Image(QWidget* parent = NULL);
    Image(QString filename, QWidget* parent = NULL);
    Image& operator=(const Image &otherImage);

    // file
    void convert(QImage** otherImg);
    void setImage(const QString &filename);
    bool writeImage(const QString &filename);
    void tempSaveImage();
    void tempRestoreImage();
    void originalImage();

    // color
    void redChannel();
    void greenChannel();
    void blueChannel();
    void greyScale();

    void redChannelChange(const int rate);
    void greenChannelChange(const int rate);
    void blueChannelChange(const int rate);
    void colorsChange(const int rateR, const int rateG, 
            const int rateB, const int rateBright);

    void changeTone(int r, int g, int b);

    void brightness(const int rate);
    void contrast(const int rate);

    // histogram equalization
    void getHistogram();
    void getHistogramAVG();
    void histogramEqualization();
    void blockHistogramEqualization();
    void histogramEqualizationForRGB();

    // transformation
    void resizeImage(const int rate);

    // halftoning
    void fixedHalftoning(const int r, const int c, int** arr);
    void expandHalftoning(const int r, const int c, int** arr);

    // spatial filtering
    void spatialFiltering(
            const int l, int** filter, 
            int(*filterFunc)(int, int*), bool linear);
    void blur();
    void weightedBlur();
    void laplace();
    void medianFiltering();
    void maximumFiltering();
    void minimumFiltering();

    // enhance
    void laplaceEnhance();
    void unsharpMasking();
    void highBoost();

    // arithmetic
    void add(QImage otherImg);
    void sub(QImage otherImg);
    void scale(const int factor);

    // fourier transformation
    void fft();
    void ifft();
    void spectrum();
    void inverseSpectrum();
    void lowpassGaussian(double freq);
    void highpassGaussian(double freq);

    // noise generation
    void gaussianNoise(double mean, double standardDeviation);
    void impulseNoise(double pa, double pb);

    // pseudo-color process
    void greyToPseudoColor(int range, int r, int g, int b);
    void greyToRGB(int(*rFunc)(int, int, int, int, int),
            int(*gFunc)(int, int, int, int, int),
            int(*bFunc)(int, int, int, int, int),
            int r, int g, int b, int range);

    // image matching               
    void saveCharacteristic();
    QStringList match();

    // Highlight
    void addBorder();

    protected:
    void paintEvent(QPaintEvent* event);

    public:
    QImage* img;
    QImage* tempImg;
    QImage* oldImg;    
    QImage* fftImg;
    // fftw_complex* fftRst;

    QString imgName;
    int* imgHistogramR;
    int* imgHistogramG;
    int* imgHistogramB;
    int* imgHistogramAVG;

    // image matching.
    QImage* toHSI(QImage*);
    QVector<QImage> partition(QImage*);
    QVector<QVector<double> > histogram(QImage);//double[3][8]
    QVector<QVector<QVector<double> > > histograms(QVector<QImage>);//double[9][3][8]
};

int median(int l, int* window);
int maximum(int l, int* window);
int minimum(int l, int* window);

#endif
