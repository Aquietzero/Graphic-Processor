#include "Image.h"
#include <iostream>

using namespace std;

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

	// add some code to detect whether the loading is successful
	// or not.
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

/* Calculate the histogram of the current image.
 */
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
	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j) {
			rgb = img->pixel(i, j);
			imgHistogramR[qRed(rgb)]++;
			imgHistogramG[qGreen(rgb)]++;
			imgHistogramB[qBlue(rgb)]++;
		}
}

/* The following methods are all image processing methods.
 * These methods operates directly on the image. No back-
 * up image is used.
 */

/* redChannel()
 * greenChannel()
 * blueChannel()
 * greyScale()
 * The above four method directly changes the image. Gets the
 * specific channel of the image. These operations are un-
 * invertible.
 */
void Image::redChannel() {
	if (img == NULL)
		return;

	int w = img->width();
	int h = img->height();
	QRgb rgb;

	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j) {
			rgb = img->pixel(i, j);
			int r = qRed(rgb);
			img->setPixel(i, j, qRgb(r, 0, 0));
			tempImg->setPixel(i, j, qRgb(r, 0, 0));
		}
	getHistogram();
	update();
}

void Image::greenChannel() {
	if (img == NULL)
		return;

	int w = img->width();
	int h = img->height();
	QRgb rgb;

	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j) {
			rgb = img->pixel(i, j);
			int g = qGreen(rgb);
			img->setPixel(i, j, qRgb(0, g, 0));
			tempImg->setPixel(i, j, qRgb(0, g, 0));
		}
	getHistogram();
	update();
}

void Image::blueChannel() {
	if (img == NULL)
		return;

	int w = img->width();
	int h = img->height();
	QRgb rgb;

	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j) {
			rgb = img->pixel(i, j);
			int b = qBlue(rgb);
			img->setPixel(i, j, qRgb(0, 0, b));
			tempImg->setPixel(i, j, qRgb(0, 0, b));
		}
	getHistogram();
	update();
}

void Image::greyScale() {
	if (img == NULL)
		return;

	int w = img->width();
	int h = img->height();
	QRgb rgb;

	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j) {
			rgb = img->pixel(i, j);
			int grey = qGray(rgb);
			img->setPixel(i, j, qRgb(grey, grey, grey));
			tempImg->setPixel(i, j, qRgb(grey, grey, grey));
		}
	getHistogram();
	update();
}

/* redChannelChange()
 * greenChannelChange()
 * blueChannelChange()
 * These methods temperarily changes the image. They will not
 * be applied until the ok button is pressed.
 */
void Image::redChannelChange(const int rate) {
	if (img == NULL)
		return;

	int w = tempImg->width();
	int h = tempImg->height();
	QRgb rgb;

	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j) {
			rgb = tempImg->pixel(i, j);
			int r = qRed(rgb);
			int g = qGreen(rgb);
			int b = qBlue(rgb);
			
			r += (int)((255. - r) * rate / 100.);
			if (r <= 255 && r >= 0)
				img->setPixel(i, j, qRgb(r, g, b));
		}
	getHistogram();
	update();
}

void Image::greenChannelChange(const int rate) {
	if (img == NULL)
		return;

	int w = tempImg->width();
	int h = tempImg->height();
	QRgb rgb;

	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j) {
			rgb = tempImg->pixel(i, j);
			int r = qRed(rgb);
			int g = qGreen(rgb);
			int b = qBlue(rgb);

			g += (int)((255. - g) * rate / 100.);
			if (g <= 255 && g >=0)
				img->setPixel(i, j, qRgb(r, g, b));
		}
	getHistogram();
	update();
}

void Image::blueChannelChange(const int rate) {
	if (img == NULL)
		return;

	int w = tempImg->width();
	int h = tempImg->height();
	QRgb rgb;

	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j) {
			rgb = tempImg->pixel(i, j);
			int r = qRed(rgb);
			int g = qGreen(rgb);
			int b = qBlue(rgb);

			b += (int)((255. - b) * rate / 100.);
			if (b <= 255 && b >= 0)
				img->setPixel(i, j, qRgb(r, g, b));
		}
	getHistogram();
	update();
}

/* Increase or decrease the brightness of the image according
 * to the given rate.
 */
void Image::brightness(const int rate) {
	if (img == NULL)
		return;

	int w = tempImg->width();
	int h = tempImg->height();
	QRgb rgb;

	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j) {
			rgb = tempImg->pixel(i, j);
			int r = qRed(rgb);
			int g = qGreen(rgb);
			int b = qBlue(rgb);
			
			r += (int)((255. - r) * rate / 100.);
			g += (int)((255. - g) * rate / 100.);
			b += (int)((255. - b) * rate / 100.);

			if (r <= 255 && r >= 0 &&
				g <= 255 && g >= 0 &&
				b <= 255 && b >= 0)
				img->setPixel(i, j, qRgb(r, g, b));
		}
	getHistogram();
	update();
}

/* Increase or decrease the contrast of the image according to 
 * the given rate.
 */
void Image::contrast(const int rate) {
	if (img == NULL)
		return;

	int w = tempImg->width();
	int h = tempImg->height();
	QRgb rgb;

	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j) {
			rgb = tempImg->pixel(i, j);
			int r = qRed(rgb);
			int g = qGreen(rgb);
			int b = qBlue(rgb);

			if (rate > 0) {
				r = r > 127 ? r + (int)((255. - r) * rate / 100.) :
							  r - (int)(r * rate / 100.);
				g = g > 127 ? g + (int)((255. - g) * rate / 100.) :
							  g - (int)(g * rate / 100.);
				b = b > 127 ? b + (int)((255. - b) * rate / 100.) :
							  b - (int)(b * rate / 100.);
			}
			else {
				r = r > 127 ? r - (int)((r - 127.) * rate / 100.) :
							  r + (int)((127. - r) * rate / 100.);
				g = g > 127 ? g + (int)((g - 127.) * rate / 100.) :
							  g - (int)((127. - g) * rate / 100.);
				b = b > 127 ? b + (int)((b - 127.) * rate / 100.) :
							  b - (int)((127. - g) * rate / 100.);
			}
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

	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j) {
			rgb = img->pixel(i, j);

			int r = 255. * (double)imgHistogramR[qRed(rgb)] / (w * h);
			int g = 255. * (double)imgHistogramG[qGreen(rgb)] / (w * h);
			int b = 255. * (double)imgHistogramB[qBlue(rgb)] / (w * h);

			img->setPixel(i, j, qRgb(r, g, b));
			tempImg->setPixel(i, j, qRgb(r, g, b));
		}
	getHistogram();
	update();
}

void Image::colorsChange(const int rateR, const int rateG, 
		const int rateB, const int rateBright) {
	if (img == NULL)
		return;

	int w = tempImg->width();
	int h = tempImg->height();
	QRgb rgb;

	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j) {
			rgb = tempImg->pixel(i, j);
			int r = qRed(rgb);
			int g = qGreen(rgb);
			int b = qBlue(rgb);

			// channels
			r += (int)((255. - r) * rateR / 100.);
			g += (int)((255. - g) * rateG / 100.);
			b += (int)((255. - b) * rateB / 100.);

			r = r > 255 ? 255 : r;
			r = r <   0 ?   0 : r;
			g = g > 255 ? 255 : g;
			g = g <   0 ?   0 : g;
			b = b > 255 ? 255 : b;
			b = b <   0 ?   0 : b;
			img->setPixel(i, j, qRgb(r, g, b));
			
			// brightness
			r += (int)((255. - r) * rateBright / 100.);
			g += (int)((255. - g) * rateBright / 100.);
			b += (int)((255. - b) * rateBright / 100.);

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

void Image::resizeImage(const int rate) {
	float r = rate / 100.;
	float w = tempImg->width() * r;
	float h = tempImg->height() * r;
	float x, y;
	float ax, ay, bx, by, cx, cy, dx, dy;
	float ar, ag, ab, br, bg, bb, cr, cg, cb, dr, dg, db;
	float er, eg, eb, fr, fg, fb;
	QRgb rgb;

	QImage* newImage = new QImage(w, h, tempImg->format());
	for (int i = 0; i < (int)w; ++i)
		for (int j = 0; j < (int)h; ++j) {
			x = (float)i / r;
			y = (float)j / r;

			// to avoid that x and y excceed the range of the 
			// two-dimension vector.
			if ((float)tempImg->width() - x < 2)
				x = tempImg->width() - 2;
			if ((float)tempImg->height() - y < 2)
				y = tempImg->height() - 2;

			ax = x, ay = y;
			bx = x + 1; by = y;
			cx = x, cy = y + 1;
			dx = x + 1, dy = y + 1;
			
			rgb = tempImg->pixel(ax, ay);
			ar = qRed(rgb);	
			ag = qGreen(rgb);	
			ab = qBlue(rgb);	
	
			rgb = tempImg->pixel(bx, by);
			br = qRed(rgb);	  	
			bg = qGreen(rgb);	 	
			bb = qBlue(rgb);	 	

			rgb = tempImg->pixel(cx, cy);
			cr = qRed(rgb);	  	
			cg = qGreen(rgb);	 	
			cb = qBlue(rgb);	 	
	
			rgb = tempImg->pixel(dx, dy);
			dr = qRed(rgb);	  	
			dg = qGreen(rgb);	 	
			db = qBlue(rgb);	 	

			er = ar + (br - ar) * (x - ax);
			fr = cr + (dr - cr) * (x - cx);
			int R = (int)(er + (fr - er) * (y - ay));

			eg = ag + (bg - ag) * (x - ax);
			fg = cg + (dg - cg) * (x - cx);
			int G = (int)(eg + (fg - eg) * (y - ay));

			eb = ab + (bb - ab) * (x - ax);
			fb = cb + (db - cb) * (x - cx);
			int B = (int)(eb + (fb - eb) * (y - ay));

			newImage->setPixel(i, j, qRgb(R, G, B));
		}
	img = newImage;
	getHistogram();
	update();
}

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

/* The spatial filtering supposes that the size of the given filter 
 * is odd rather than even for advantages
 */
void Image::spatialFiltering(const int l, int** filter) {
	if (img == NULL)
		return;

	int w = tempImg->width();
	int h = tempImg->height();
	QImage* auxImage = new QImage(w + l - 1, h + l - 1, tempImg->format());

	QRgb rgb;
	int r, g, b;
	int weight = 0;

	// get the sum of the filter
	for (int i = 0; i < l; ++i)
		for (int j = 0; j < l; j++)
			weight += filter[i][j];

	// create an auxiliary image
	int begin = (l - 1) / 2;
	for (int i = begin; i < w + begin; ++i)
		for (int j = begin; j < h + begin; ++j)
			auxImage->setPixel(i, j, tempImg->pixel(i - begin, j - begin));

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
	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j) {
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

			r = r > 255 ? 255 : r;
			r = r <   0 ?   0 : r;
			g = g > 255 ? 255 : g;
			g = g <   0 ?   0 : g;
			b = b > 255 ? 255 : b;
			b = b <   0 ?   0 : b;
	
			img->setPixel(i, j, qRgb(r, g, b));
			tempImg->setPixel(i, j, qRgb(r, g, b));
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
	spatialFiltering(3, filter);
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
	spatialFiltering(3, filter);
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
	spatialFiltering(3, filter);
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

/* The following function calculates the fourier tranformation
 * of the given image.
 */
void Image::fft() {
    int w = img->width();
    int h = img->height();
    int size = w * h * 4;

    fftw_complex *in, *out;
    fftw_plan p;

    in  = (fftw_complex*) fftw_malloc (sizeof(fftw_complex) * size);
    out = (fftw_complex*) fftw_malloc (sizeof(fftw_complex) * size);
    fftRst = (fftw_complex*) fftw_malloc (sizeof(fftw_complex) * size);

    // padding with 0; translate the center of the transformation
    // and make preparation of the fourier transformation.
    for (int j = 0; j < h; ++j) {
        for (int i = 0; i < w; ++i) {
            in[j * w * 2 + i][0] = qRed(img->pixel(i, j));    
            in[j * w * 2 + i][1] = 0;
            if ((i + j) % 2 == 1)
                in[j * w * 2 + i][0] *= -1;
        }
        for (int i = w; i < 2 * w; ++i) {
            in[j * w * 2 + i][0] = 0;
            in[j * w * 2 + i][1] = 0;
        }
    }
    for (int j = h; j < 2 * h; ++j) 
        for (int i = 0; i < 2 * w; ++i) {
            in[j * w * 2 + i][0] = 0;
            in[j * w * 2 + i][1] = 0;
        }
    
    // fourier transformation
    p = fftw_plan_dft_2d(2 * w, 2 * h, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);

    // create an image to show the result of the fourier transformation
    fftImg = new QImage(2 * w, 2 * h, tempImg->format());
    double grey, spectrum; 
    double max = sqrt(out[0][0] * out[0][0] + out[0][1] * out[0][1]);
    for (int i = 1; i < size; ++i) {
        spectrum = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
        if (spectrum > max)
            max = spectrum;
    }

    for (int i = 0; i < 2 * w; ++i)
        for (int j = 0; j < 2 * h; ++j) {
            grey = sqrt((out[j * w * 2 + i][0] * out[j * w * 2 + i][0] + 
                   out[j * w * 2 + i][1] * out[j * w * 2 + i][1])) * 255 / max;
            grey = 100 * log(grey + 1);

            if (grey > 255)
                fftImg->setPixel(i, j, qRgb(255, 255, 255));
            else if (grey < 0)
                fftImg->setPixel(i, j, qRgb(0, 0, 0));
            else
                fftImg->setPixel(i, j, qRgb(grey, grey, grey));
        }

    // store the result of the fourier transformation
    for (int i = 0; i < size; ++i) {
        fftRst[i][0] = out[i][0];
        fftRst[i][1] = out[i][1];
    }

    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);
}

void Image::ifft() {
    int w = img->width();
    int h = img->height();
    int size = w * h * 4;

    fftw_complex *out;
    fftw_plan p;

    out = (fftw_complex*) fftw_malloc (sizeof(fftw_complex) * size);

    // fourier transformation
    p = fftw_plan_dft_2d(2 * w, 2 * h, fftRst, out, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(p);

    int grey;
    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j) {
            grey = out[j * w * 2 + i][0] / size;
            if ((i + j) % 2 == 1)
                grey *= -1;

            if (grey > 255)
                grey = 255;
            else if (grey < 0)
                grey = 0;
            img->setPixel(i, j, qRgb(grey, grey, grey));
        }

    fftw_destroy_plan(p);
    fftw_free(out);
}
    
void Image::spectrum() {
    int w = img->width();
    int h = img->height();

    fft();

    img = new QImage(2 * w, 2 * h, tempImg->format());
    for (int i = 0; i < 2 * w; ++i)
        for (int j = 0; j < 2 * h; ++j) 
            img->setPixel(i, j, fftImg->pixel(i, j));

    update();
}

void Image::inverseSpectrum() {
    int w = img->width() / 2;
    int h = img->height() / 2;

    img = new QImage(w, h, tempImg->format());
    ifft();
    update();
}

void Image::lowpassGaussian(double freq) {
    int w = img->width();
    int h = img->height();
    double e = 2.71828;

    // execute the fourier transformation
    fft();
     
    // filtering
    double exponent;
    double distance;
    for (int i = 0; i < 2 * w; ++i) 
        for (int j = 0; j < 2 * h; ++j){
            distance = (w - i) * (w - i) +
                       (h - j) * (h - j);
            exponent = -distance / (2 * freq * freq);
            fftRst[j * w * 2 + i][0] *= (pow(e, exponent));
            fftRst[j * w * 2 + i][1] *= (pow(e, exponent));
    }

    // execute the inverse fourier transformation
    ifft();
    update();
}
 
void Image::highpassGaussian(double freq) {
    int w = img->width();
    int h = img->height();
    double e = 2.71828;

    // execute the fourier transformation
    fft();
    
    // filtering
    double exponent;
    double distance;
    for (int i = 0; i < 2 * w; ++i) 
        for (int j = 0; j < 2 * h; ++j){
            distance = (w - i) * (w - i) +
                       (h - j) * (h - j);
            exponent = -distance / (2 * freq * freq);
            fftRst[j * w * 2 + i][0] *= (1 - (pow(e, exponent)));
            fftRst[j * w * 2 + i][1] *= (1 - (pow(e, exponent)));
    }

    // execute the inverse fourier transformation
    ifft();
    update();
}
