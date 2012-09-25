#include <QtGui>
#include <QtCore>

#include <iostream>
#include "../SimpleDIP.h"

void SimpleDIP::createMenus() {
    QFont menuFont("oldEnglish", 11);
    menuBar()->setFont(menuFont);

    // file menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(quitAction);

    // tool menu
    toolMenu = menuBar()->addMenu(tr("&Tool"));
    toolMenu->addAction(originalImageAction);

    // color menu
    colorMenu = menuBar()->addMenu(tr("&Color"));

    colorMenu->addAction(extractColorAction);

    channelMenu = new QMenu(tr("Channels"));
    channelMenu->addAction(redChannelAction);
    channelMenu->addAction(greenChannelAction);
    channelMenu->addAction(blueChannelAction);
    channelMenu->addAction(greyScaleAction);
    colorMenu->addMenu(channelMenu);

    autoMenu = new QMenu(tr("Auto"));
    autoMenu->addAction(hisEqualizationAction);
    autoMenu->addAction(hisEqualizationAVGAction);
    colorMenu->addMenu(autoMenu);

    halftoningMenu = new QMenu(tr("Halftoning"));
    halftoningMenu->addAction(fixedHalftoningAction);
    halftoningMenu->addAction(expandHalftoningAction);
    colorMenu->addMenu(halftoningMenu);

    // filter menu
    filterMenu = menuBar()->addMenu(tr("Fil&ter"));

    blurMenu = new QMenu(tr("&Blur"));
    blurMenu->addAction(blurAction);
    blurMenu->addAction(weightedBlurAction);
    filterMenu->addMenu(blurMenu);

    enhanceMenu = new QMenu(tr("&Enhance"));
    enhanceMenu->addAction(laplaceEnhanceAction);
    enhanceMenu->addAction(unsharpMaskingAction);
    enhanceMenu->addAction(highBoostAction);
    filterMenu->addMenu(enhanceMenu);

    edgeDetectMenu = new QMenu(tr("Edge &Detect"));
    edgeDetectMenu->addAction(laplaceAction);
    filterMenu->addMenu(edgeDetectMenu);

    noiseMenu = new QMenu(tr("&Noise"));
    noiseMenu->addAction(gaussianNoiseAction);
    noiseMenu->addAction(impulseNoiseAction);
    filterMenu->addMenu(noiseMenu);

    nonlinearFilteringMenu = new QMenu(tr("Non-Linear Filtering"));
    nonlinearFilteringMenu->addAction(medianFilteringAction);
    nonlinearFilteringMenu->addAction(maximumFilteringAction);
    nonlinearFilteringMenu->addAction(minimumFilteringAction);
    filterMenu->addMenu(nonlinearFilteringMenu);

    filterMenu->addAction(spatialFilteringAction);

    // fourier tranform menu
    fftMenu = menuBar()->addMenu(tr("FFT")); 

    fftMenu->addAction(fftAction);
    fftMenu->addAction(ifftAction);
    fftMenu->addAction(LPGFAction);
    fftMenu->addAction(HPGFAction);

    // image matching menu
    imgMatchingMenu = menuBar()->addMenu(tr("Matching"));

    imgMatchingMenu->addAction(imgMatchingAction);
}
