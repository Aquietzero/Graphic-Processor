#include <QtGui>
#include <QtCore>

#include <iostream>
#include "../SimpleDIP.h"

void SimpleDIP::createConnects() {
    connect(this, SIGNAL(imageModified()), 
            this, SLOT(setImageModified()));

    // color tab sliders
    connect(tools->colorTab->redSlider, SIGNAL(valueChanged(int)),
            this, SLOT(colorsChange()));
    connect(tools->colorTab->greenSlider, SIGNAL(valueChanged(int)),
            this, SLOT(colorsChange()));
    connect(tools->colorTab->blueSlider, SIGNAL(valueChanged(int)),
            this, SLOT(colorsChange()));
    connect(tools->colorTab->brightnessSlider, SIGNAL(valueChanged(int)),
            this, SLOT(colorsChange()));
    connect(tools->colorTab->contrastSlider, SIGNAL(valueChanged(int)),
            this, SLOT(contrastChange(int)));

    // transformation tab sliders
    connect(tools->transformTab->resizeSlider, SIGNAL(valueChanged(int)),
            this, SLOT(resizeImg()));

    // when ok button is pressed, the current changes will be
    // applied to the image
    connect(tools->colorTab->okButton, SIGNAL(clicked()),
            this, SLOT(tempSave()));
    connect(tools->colorTab->cancelButton, SIGNAL(clicked()),
            this, SLOT(tempRestore()));

    connect(tools->transformTab->okButton, SIGNAL(clicked()),
            this, SLOT(tempSave()));
    connect(tools->transformTab->cancelButton, SIGNAL(clicked()),
            this, SLOT(tempRestore()));
}
