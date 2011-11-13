#ifndef VIEWIMAGE_H
#define VIEWIMAGE_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <fftw3.h>
#include <cmath>

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

	void brightness(const int rate);
	void contrast(const int rate);

	// histogram equalization
	void getHistogram();
	void histogramEqualization();

	// transformation
	void resizeImage(const int rate);

	// halftoning
	void fixedHalftoning(const int r, const int c, int** arr);
	void expandHalftoning(const int r, const int c, int** arr);

	// spatial filtering
	void spatialFiltering(const int l, int** filter);
	void blur();
	void weightedBlur();
	void laplace();

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
};

#endif
