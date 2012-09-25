#include "Image.h"

/* The following function calculates the fourier tranformation
 * of the given image.
 */
void Image::fft() {
    /*
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
    */
}

void Image::ifft() {
    /*
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
    */
}

void Image::spectrum() {
    /*
       int w = img->width();
       int h = img->height();

       fft();

       img = new QImage(2 * w, 2 * h, tempImg->format());
       for (int i = 0; i < 2 * w; ++i)
       for (int j = 0; j < 2 * h; ++j) 
       img->setPixel(i, j, fftImg->pixel(i, j));

       update();
       */
}

void Image::inverseSpectrum() {
    /*
       int w = img->width() / 2;
       int h = img->height() / 2;

       img = new QImage(w, h, tempImg->format());
       ifft();
       update();
       */
}

void Image::lowpassGaussian(double freq) {
    /*
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
    */
}

void Image::highpassGaussian(double freq) {
    /*
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
    */
}
