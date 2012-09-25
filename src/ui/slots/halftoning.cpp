#include <QtGui>
#include <QtCore>

#include <iostream>
#include "SimpleDIP.h"

void SimpleDIP::fixedHalftoning() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();

        int** arr = new int*[3];
        for (int i = 0; i < 3; ++i)
            arr[i] = new int[3];
        arr[0][0] = 7;
        arr[0][1] = 9;
        arr[0][2] = 5;
        arr[1][0] = 2;
        arr[1][1] = 1;
        arr[1][2] = 4;
        arr[2][0] = 6;
        arr[2][1] = 3;
        arr[2][2] = 8;

        centralArea->image->fixedHalftoning(3, 3, arr);
        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}

void SimpleDIP::expandHalftoning() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();

        int** arr = new int*[3];
        for (int i = 0; i < 3; ++i)
            arr[i] = new int[3];
        arr[0][0] = 7;
        arr[0][1] = 9;
        arr[0][2] = 5;
        arr[1][0] = 2;
        arr[1][1] = 1;
        arr[1][2] = 4;
        arr[2][0] = 6;
        arr[2][1] = 3;
        arr[2][2] = 8;

        centralArea->image->expandHalftoning(3, 3, arr);
        setHistograms();
        tools->resetToolTabs();
        emit imageModified();
    }
}
