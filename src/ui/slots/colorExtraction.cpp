#include <QtGui>
#include <QtCore>

#include <iostream>
#include "SimpleDIP.h"

void SimpleDIP::colorExtracting() {
    ColorExtractDialog* settings = new ColorExtractDialog;

    centralArea->image->tempSaveImage();
    connect(settings, SIGNAL(closeAndApplySettings()),
            this, SLOT(tempSave()));
    connect(settings, SIGNAL(applySettings(int, int, int, int)),
            this, SLOT(applyColorExtracting(int, int, int, int)));
    connect(settings, SIGNAL(closeNotApplySettings()),
            this, SLOT(tempRestore()));

}

void SimpleDIP::applyColorExtracting(int r, int g, int b, int range) {
    if (centralArea->image->img != NULL) {
        centralArea->image->greyToPseudoColor(range, r, g, b);
        setHistograms();
        tools->resetToolTabs();
    }
}
