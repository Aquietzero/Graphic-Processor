#include <QtGui>
#include <QtCore>

#include <iostream>
#include "../SimpleDIP.h"

void SimpleDIP::laplaceTransform() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();
        centralArea->image->laplace();
        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}


void SimpleDIP::laplaceEnhance() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();
        centralArea->image->laplaceEnhance();
        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}

void SimpleDIP::unsharpMaskEnhance() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();
        centralArea->image->unsharpMasking();
        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}

void SimpleDIP::highBoostEnhance() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();
        centralArea->image->highBoost();
        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}
