#include <QtGui>
#include <QtCore>

#include <iostream>
#include "../SimpleDIP.h"

void SimpleDIP::fft() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();
        centralArea->image->spectrum();
        tools->resetToolTabs();
        emit imageModified();
    }
}

void SimpleDIP::ifft() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();
        centralArea->image->inverseSpectrum();
        tools->resetToolTabs();
        emit imageModified();
    }
}


void SimpleDIP::LPGF() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();
        centralArea->image->lowpassGaussian(30);
        tools->resetToolTabs();
        emit imageModified();
    }
}

void SimpleDIP::HPGF() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();
        centralArea->image->highpassGaussian(160);
        tools->resetToolTabs();
        emit imageModified();
    }
}
