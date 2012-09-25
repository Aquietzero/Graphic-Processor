#include "Image.h"

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

void Image::changeTone(int r_0, int g_0, int b_0) {
	if (img == NULL)
		return;

	int w = tempImg->width();
	int h = tempImg->height();
    int r, g, b;
	QRgb rgb;

	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j) {
			rgb = tempImg->pixel(i, j);

			r = qRed(rgb);
			g = qGreen(rgb);
			b = qBlue(rgb);

            r = (float)(r) * r_0 / (r_0 + g_0 + b_0);
            g = (float)(g) * g_0 / (r_0 + g_0 + b_0);
            b = (float)(b) * b_0 / (r_0 + g_0 + b_0);

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
