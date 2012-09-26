#include "Image.h"

void Image::getHistogram() {
	if (img == NULL)
		return;

	int w = img->width();
	int h = img->height();
	QRgb rgb;

	imgHistogramR = new int[256];
	imgHistogramG = new int[256];
	imgHistogramB = new int[256];
	for (int i = 0; i < 256; ++i) {
		imgHistogramR[i] = 0;
		imgHistogramG[i] = 0;
		imgHistogramB[i] = 0;
	}
	for (int i = 0; i < w; ++i) {
		for (int j = 0; j < h; ++j) {
			rgb = img->pixel(i, j);
			imgHistogramR[qRed(rgb)]++;
			imgHistogramG[qGreen(rgb)]++;
			imgHistogramB[qBlue(rgb)]++;
		}
    }
}

void Image::getHistogramAVG() {
	if (img == NULL)
		return;

	imgHistogramAVG = new int[256];
    for (int i = 0; i < 256; ++i)
        imgHistogramAVG[i] = (imgHistogramR[i] +
                              imgHistogramG[i] +
                              imgHistogramB[i]) / 3.;
}

void Image::histogramEqualization() {
	if (img == NULL)
		return;

	int w = img->width();
	int h = img->height();
	QRgb rgb;

	for (int i = 1; i < 256; ++i) {
		imgHistogramR[i] += imgHistogramR[i - 1];
		imgHistogramG[i] += imgHistogramG[i - 1];
		imgHistogramB[i] += imgHistogramB[i - 1];
	}

	for (int i = 0; i < w; ++i) {
		for (int j = 0; j < h; ++j) {
			rgb = img->pixel(i, j);

			int r = 255. * (double)imgHistogramR[qRed(rgb)] / (w * h);
			int g = 255. * (double)imgHistogramG[qGreen(rgb)] / (w * h);
			int b = 255. * (double)imgHistogramB[qBlue(rgb)] / (w * h);

			img->setPixel(i, j, qRgb(r, g, b));
			tempImg->setPixel(i, j, qRgb(r, g, b));
		}
    }
    // Update the histogram of the equalized image.
	getHistogram();
	update();
}

void Image::histogramEqualizationForRGB() {
	if (img == NULL)
		return;

	int w = img->width();
	int h = img->height();
	QRgb rgb;

	for (int i = 1; i < 256; ++i) 
		imgHistogramAVG[i] += imgHistogramAVG[i - 1];

	for (int i = 0; i < w; ++i) {
		for (int j = 0; j < h; ++j) {
			rgb = img->pixel(i, j);

			int r = 255. * (double)imgHistogramAVG[qRed(rgb)] / (w * h);
			int g = 255. * (double)imgHistogramAVG[qGreen(rgb)] / (w * h);
			int b = 255. * (double)imgHistogramAVG[qBlue(rgb)] / (w * h);

			img->setPixel(i, j, qRgb(r, g, b));
			tempImg->setPixel(i, j, qRgb(r, g, b));
		}
    }
    // Update the histogram of the equalized image.
	getHistogram();
	update();
}
