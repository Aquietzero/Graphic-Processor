#include "Image.h"

void Image::getHistogram() {
	if (img == NULL) return;

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
	if (img == NULL) return;

	imgHistogramAVG = new int[256];
    for (int i = 0; i < 256; ++i)
        imgHistogramAVG[i] = (imgHistogramR[i] +
                              imgHistogramG[i] +
                              imgHistogramB[i]) / 3.;
}

void Image::histogramEqualization() {
	if (img == NULL) return;

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
	if (img == NULL) return;

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

void Image::blockHistogramEqualization() {
	if (img == NULL) return;

    // TODO make it variable.
    int JUMP = 128;
    int blockPixels = JUMP * JUMP;

	int w = img->width();
	int h = img->height();
    int r, g, b, intensity;
	QRgb rgb;

    int* histogramR = new int[256];
    int* histogramG = new int[256];
    int* histogramB = new int[256];
    int* histogramAVG = new int[256];
    // For each block, execute block histogram equalization.
    for (int i = 0; i < w; i += JUMP) {
        for (int j = 0; j < h; j += JUMP) {
            // Reset histogram.
            for (int n = 0; n < 256; ++n) {
                histogramR[n] = 0;
                histogramG[n] = 0;
                histogramB[n] = 0;
            }
            // Calculate the histogram.
            for (int x = 0; x < JUMP; ++x) {
                for (int y = 0; y < JUMP; ++y) {
                    rgb = img->pixel(i + x, j + y);
                    histogramR[qRed(rgb)]++;
                    histogramG[qGreen(rgb)]++;
                    histogramB[qBlue(rgb)]++;
                }
            }
            // Calculate the average histogram.
            for (int n = 0; n < 256; ++n) {
                histogramAVG[n] = (histogramR[n] + histogramG[n] + histogramB[n]) / 3;
            }
            // Calculate the cumulative histogram.
            for (int n = 1; n < 256; ++n) {
                histogramAVG[n] += histogramAVG[n - 1];
            }
            // Update the image.
            for (int x = 0; x < JUMP; ++x) {
                for (int y = 0; y < JUMP; ++y) {
                    rgb = img->pixel(i + x, j + y);

                    r = 255 * histogramAVG[qRed(rgb)] / blockPixels;
                    g = 255 * histogramAVG[qGreen(rgb)] / blockPixels;
                    b = 255 * histogramAVG[qBlue(rgb)] / blockPixels;

                    img->setPixel(i + x, j + y, qRgb(r, g, b));
                    tempImg->setPixel(i + x, j + y, qRgb(r, g, b));
                }
            }
        }
    }
    // Update the histogram of the equalized image.
	getHistogram();
	update();
}
