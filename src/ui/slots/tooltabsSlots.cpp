#include <QtGui>
#include <QtCore>

#include <iostream>
#include "../SimpleDIP.h"

void SimpleDIP::redChange(int rate) {
    if (centralArea->image->img != NULL) {
        centralArea->image->redChannelChange(rate);
        setHistograms();
        emit imageModified();
    }
}

void SimpleDIP::greenChange(int rate) {
    if (centralArea->image->img != NULL) {
        centralArea->image->greenChannelChange(rate);
        setHistograms();
        emit imageModified();
    }
}

void SimpleDIP::blueChange(int rate) {
    if (centralArea->image->img != NULL) {
        centralArea->image->blueChannelChange(rate);
        setHistograms();
        emit imageModified();
    }
}

void SimpleDIP::colorsChange() {
    if (centralArea->image->img != NULL) {
        if (!checkTabSwitch())
            centralArea->image->tempSaveImage();
        int rateR = tools->colorTab->redSlider->value();
        int rateG = tools->colorTab->greenSlider->value();
        int rateB = tools->colorTab->blueSlider->value();
        int rateBright = tools->colorTab->brightnessSlider->value();

        centralArea->image->colorsChange(
                rateR, rateG, rateB, rateBright);
        setHistograms();
        emit imageModified();
    }
}

void SimpleDIP::brightnessChange(int rate) {
    if (centralArea->image->img != NULL) {
        centralArea->image->brightness(rate);
        setHistograms();
        emit imageModified();
    }
}

void SimpleDIP::contrastChange(int rate) {
    if (centralArea->image->img != NULL) {
        centralArea->image->contrast(rate);
        setHistograms();
        emit imageModified();
    }
}

void SimpleDIP::resizeImg() {
    if (centralArea->image->img != NULL) {
        if (!checkTabSwitch())
            centralArea->image->tempSaveImage();
        int rate = tools->transformTab->resizeSlider->value();
        centralArea->image->resizeImage(rate);
        emit imageModified();
    }
}

