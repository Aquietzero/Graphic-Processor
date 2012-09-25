#include <QtGui>
#include <QtCore>

#include <iostream>
#include "../SimpleDIP.h"

void SimpleDIP::gaussianNoise() {
    GaussianNoiseDialog* settings = new GaussianNoiseDialog;

    centralArea->image->tempSaveImage();
    connect(settings, SIGNAL(closeAndApplySettings()),
            this, SLOT(tempSave()));
    connect(settings, SIGNAL(applySettings(int, int)),
            this, SLOT(addGaussianNoise(int, int)));
    connect(settings, SIGNAL(closeNotApplySettings()),
            this, SLOT(tempRestore()));
}

void SimpleDIP::addGaussianNoise(int mean, int sd) {
    if (centralArea->image->img != NULL) {
        centralArea->image->gaussianNoise(mean, sd);
        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}

void SimpleDIP::impulseNoise() {
    ImpulseNoiseDialog* settings = new ImpulseNoiseDialog;

    centralArea->image->tempSaveImage();
    connect(settings, SIGNAL(closeAndApplySettings()),
            this, SLOT(tempSave()));
    connect(settings, SIGNAL(applySettings(double, double)),
            this, SLOT(addImpulseNoise(double, double)));
    connect(settings, SIGNAL(closeNotApplySettings()),
            this, SLOT(tempRestore()));
}

void SimpleDIP::addImpulseNoise(double pa, double pb) {
    if (centralArea->image->img != NULL) {
        centralArea->image->impulseNoise(pa, pb);
        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}
