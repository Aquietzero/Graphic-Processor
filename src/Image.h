#ifndef VIEWIMAGE_H
#define VIEWIMAGE_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <fftw3.h>
#include <algorithm>

#include "Random.h"

#include <QVector>
#include <QStringList>
#include <QString>

#define RANGE 10000
#define N_WH 8
#define N_Partition 10
#define N_Level 8
#define PI 3.1415926

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
    fftw_complex* fftRst;

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

int redFunc(int grey, int r, int g, int b, int range);
int greenFunc(int grey, int r, int g, int b, int range);
int blueFunc(int grey, int r, int g, int b, int range);

class Record{
public:
    Record(){}
    Record(QString);
    Record(QVector<QVector<QVector<double> > >, int, int, QString);

    QVector<QVector<QVector<double> > > histograms;
    int width;
    int height;
    QString fname;
};

class Record2{
public:
    QString fname;
    double similarity;
};

int quantizationH(int level);
int quantizationS(int level);
int quantizationI(int level);
double histogramCompare(QVector<double>, QVector<double>);
double imgMatching(QVector<QVector<QVector<double> > >);
QVector<Record> ImgRecords();
QStringList matchedImgsName(Record, QVector<Record>);
int similarityCmp(Record2, Record2);


#endif
