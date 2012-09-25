#include <QtGui>
#include <QtCore>

#include <iostream>
#include "SimpleDIP.h"

SimpleDIP::SimpleDIP() {
    centralArea = new CentralArea();
    setCentralWidget(centralArea);

    createActions();
    createMenus();
    createStatusBar();
    createToolDockWidget();
    createInfoDockWidget();
    createConnects();

    setMinimumWidth(1200);
    setMinimumHeight(700);

    prevTabIndex = -1;
}

void SimpleDIP::imgMatching() {
    ImageMatching* imgMatching = new ImageMatching(centralArea->image);
    imgMatching->show();
}
