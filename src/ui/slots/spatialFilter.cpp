#include <QtGui>
#include <QtCore>

#include <iostream>
#include "SimpleDIP.h"

void SimpleDIP::spatialFiltering() {
    SpatialFilteringDialog* settings = new SpatialFilteringDialog;

    centralArea->image->tempSaveImage();
    connect(settings, SIGNAL(closeAndApplySettings()),
            this, SLOT(tempSave()));
    connect(settings, SIGNAL(applySettings(int**)),
            this, SLOT(applySpatialFiltering(int**)));
    connect(settings, SIGNAL(closeNotApplySettings()),
            this, SLOT(tempRestore()));
}

void SimpleDIP::applySpatialFiltering(int** filter) {
    if (centralArea->image->img != NULL) {
        centralArea->image->spatialFiltering(3, filter, NULL, true);
        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}

