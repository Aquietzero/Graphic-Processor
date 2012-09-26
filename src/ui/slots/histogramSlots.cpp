#include <QtGui>
#include <QtCore>

#include <iostream>
#include "../SimpleDIP.h"

void SimpleDIP::setHistograms() {
    if (centralArea->image->img != NULL) {
        info->histogramR->setHistogram(
                centralArea->image->imgHistogramR, 256);
        info->histogramG->setHistogram(
                centralArea->image->imgHistogramG, 256);
        info->histogramB->setHistogram(
                centralArea->image->imgHistogramB, 256);
    }
}

void SimpleDIP::histogramEqualization() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();

        centralArea->image->histogramEqualization();

        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}

void SimpleDIP::blockHistogramEqualization() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();

        centralArea->image->blockHistogramEqualization();

        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}

void SimpleDIP::histogramEqualizationAVG() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();

        centralArea->image->getHistogramAVG();
        centralArea->image->histogramEqualizationForRGB();

        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}

