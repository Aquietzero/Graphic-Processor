#include <QtGui>
#include <QtCore>

#include <iostream>
#include "../SimpleDIP.h"

void SimpleDIP::hisEqualization() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();

        centralArea->image->histogramEqualization();

        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}

void SimpleDIP::hisEqualizationAVG() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();

        centralArea->image->getHistogramAVG();
        centralArea->image->histogramEqualizationForRGB();

        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}

