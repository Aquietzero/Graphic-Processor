#include <QtGui>
#include <QtCore>

#include <iostream>
#include "../SimpleDIP.h"

void SimpleDIP::blur() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();
        centralArea->image->blur();
        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}

void SimpleDIP::weightedBlur() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();
        centralArea->image->weightedBlur();
        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}
