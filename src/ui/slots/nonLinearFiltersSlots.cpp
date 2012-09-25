#include <QtGui>
#include <QtCore>

#include <iostream>
#include "../SimpleDIP.h"

void SimpleDIP::medianFiltering() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();
        centralArea->image->medianFiltering();
        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}

void SimpleDIP::maximumFiltering() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();
        centralArea->image->maximumFiltering();
        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}

void SimpleDIP::minimumFiltering() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();
        centralArea->image->minimumFiltering();
        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}
