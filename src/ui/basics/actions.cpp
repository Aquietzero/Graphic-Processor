#include <QtGui>
#include <QtCore>

#include <iostream>
#include "../SimpleDIP.h"

void SimpleDIP::createActions() {
    createFileMenuActions();
    createToolMenuActions();
    createColorMenuActions();
    createFilterMenuActions();
    createFFTMenuActions();
    createImgMatchingMenuActions();
}

void SimpleDIP::createFileMenuActions() {
    // open option in menubar
    openAction = new QAction(tr("&Open..."), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an .bmp image file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    // save option in menubar
    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the current image"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    // save as option in menubar
    saveAsAction = new QAction(tr("Save As..."), this);
    saveAsAction->setStatusTip(tr("Save the current image under a "
                "new file name"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    // quit option in menubar
    quitAction = new QAction(tr("&Quit..."), this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    quitAction->setStatusTip(tr("Exit the application"));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));	
}

void SimpleDIP::createToolMenuActions() {
    originalImageAction = new QAction(tr("Original Image"), this);
    originalImageAction->setStatusTip(
            tr("Redo down to the original image"));
    connect(originalImageAction, SIGNAL(triggered()),
            this, SLOT(originalImage()));
}

void SimpleDIP::createColorMenuActions() {
    redChannelAction = new QAction(tr("Red Channel"), this);
    redChannelAction->setStatusTip(
            tr("Get the red channel of the picture"));
    connect(redChannelAction, SIGNAL(triggered()), 
            this, SLOT(getRedChannel()));

    greenChannelAction = new QAction(tr("Green Channel"), this);
    greenChannelAction->setStatusTip(
            tr("Get the green channel of the picture"));
    connect(greenChannelAction, SIGNAL(triggered()), 
            this, SLOT(getGreenChannel()));

    blueChannelAction = new QAction(tr("Blue Channel"), this);
    blueChannelAction->setStatusTip(
            tr("Get the blue channel of the picture"));
    connect(blueChannelAction, SIGNAL(triggered()), 
            this, SLOT(getBlueChannel()));

    greyScaleAction = new QAction(tr("Grey Scale"), this);
    greyScaleAction->setStatusTip(
            tr("Get the grey scale of the picture"));
    connect(greyScaleAction, SIGNAL(triggered()), 
            this, SLOT(getGreyScale()));

    hisEqualizationAction = new QAction(tr("Histogram Equalization"), this);
    hisEqualizationAction->setStatusTip(
            tr("Histogram Equalization"));
    connect(hisEqualizationAction, SIGNAL(triggered()),
            this, SLOT(hisEqualization()));

    hisEqualizationAVGAction = new QAction(tr(
                "Average Histogram Equalization"), this);
    hisEqualizationAVGAction->setStatusTip(
            tr("Average Histogram Equalization"));
    connect(hisEqualizationAVGAction, SIGNAL(triggered()),
            this, SLOT(hisEqualizationAVG()));

    expandHalftoningAction = new QAction(tr("Expand Halftoning"), this);
    expandHalftoningAction->setStatusTip(
            tr("Expand Halftoning"));
    connect(expandHalftoningAction, SIGNAL(triggered()),
            this, SLOT(expandHalftoning()));

    fixedHalftoningAction = new QAction(tr("Fixed Halftoning"), this);
    fixedHalftoningAction->setStatusTip(
            tr("Fixed Halftoning"));
    connect(fixedHalftoningAction, SIGNAL(triggered()),
            this, SLOT(fixedHalftoning()));

    extractColorAction = new QAction(tr("Color Extraction"), this);
    extractColorAction->setStatusTip(
            tr("Color Extraction"));
    connect(extractColorAction, SIGNAL(triggered()),
            this, SLOT(colorExtracting()));

}

void SimpleDIP::createFilterMenuActions() {
    // filter menu action
    laplaceAction = new QAction(tr("&Laplace"), this);
    laplaceAction->setStatusTip(
            tr("Laplace Filtering for edge detection of the image"));
    connect(laplaceAction, SIGNAL(triggered()),
            this, SLOT(laplaceTransform()));

    blurAction = new QAction(tr("&Blur"), this);
    blurAction->setStatusTip(
            tr("Slightly blur the image"));
    connect(blurAction, SIGNAL(triggered()),
            this, SLOT(blur()));

    weightedBlurAction = new QAction(tr("&Weighted Blur"), this);
    weightedBlurAction->setStatusTip(
            tr("Using the weighted smooth filter to blur the image"));
    connect(weightedBlurAction, SIGNAL(triggered()),
            this, SLOT(weightedBlur()));

    laplaceEnhanceAction = new QAction(tr("&Laplace Enhance"), this);
    laplaceEnhanceAction->setStatusTip(
            tr("Using Laplace Factor to enhance the image"));
    connect(laplaceEnhanceAction, SIGNAL(triggered()),
            this, SLOT(laplaceEnhance()));

    unsharpMaskingAction = new QAction(tr("&Unsharp Masking"), this);
    unsharpMaskingAction->setStatusTip(
            tr("Using the original image to subtract its blured "
                "version and then adds it by itself to get a unsharp "
                "masking enhancement"));
    connect(unsharpMaskingAction, SIGNAL(triggered()),
            this, SLOT(unsharpMaskEnhance()));

    highBoostAction = new QAction(tr("&High Boost"), this);
    highBoostAction->setStatusTip(
            tr("Using the original image to subtract its blured "
                "version, scales it for a specific factor and then "
                " adds it by itself to get a high boost enhancement"));
    connect(highBoostAction, SIGNAL(triggered()),
            this, SLOT(highBoostEnhance()));

    gaussianNoiseAction = new QAction(tr("&Gaussian Noise"), this);
    gaussianNoiseAction->setStatusTip(
            tr("Add Gaussian Noise to the image."));
    connect(gaussianNoiseAction, SIGNAL(triggered()),
            this, SLOT(gaussianNoise()));

    impulseNoiseAction = new QAction(tr("&Impulse Noise"), this);
    impulseNoiseAction->setStatusTip(
            tr("Add impulse noise to the image."));
    connect(impulseNoiseAction, SIGNAL(triggered()),
            this, SLOT(impulseNoise()));

    medianFilteringAction = new QAction(tr("Median Filtering"), this);
    medianFilteringAction->setStatusTip(
            tr("Using median filter to filter the image."));
    connect(medianFilteringAction, SIGNAL(triggered()),
            this, SLOT(medianFiltering()));

    maximumFilteringAction = new QAction(tr("Maximum Filtering"), this);
    maximumFilteringAction->setStatusTip(
            tr("Using maximum filter to filter the image."));
    connect(maximumFilteringAction, SIGNAL(triggered()),
            this, SLOT(maximumFiltering()));

    minimumFilteringAction = new QAction(tr("Minimum Filtering"), this);
    minimumFilteringAction->setStatusTip(
            tr("Using minimum filter to filter the image."));
    connect(minimumFilteringAction, SIGNAL(triggered()),
            this, SLOT(minimumFiltering()));

    spatialFilteringAction = new QAction(tr("Spatial Filtering"), this);
    spatialFilteringAction->setStatusTip(
            tr("General Spatial Filtering according to the given filter"));
    connect(spatialFilteringAction, SIGNAL(triggered()),
            this, SLOT(spatialFiltering()));
}

void SimpleDIP::createFFTMenuActions() {
    fftAction = new QAction(tr("FFT"), this);
    fftAction->setStatusTip(
            tr("Calculate the fourier transformation of the current "
                "image."));
    connect(fftAction, SIGNAL(triggered()),
            this, SLOT(fft()));

    ifftAction = new QAction(tr("IFFT"), this);
    ifftAction->setStatusTip(
            tr("Calculate the fourier transformation of the current "
                "image."));
    connect(ifftAction, SIGNAL(triggered()),
            this, SLOT(ifft()));

    LPGFAction = new QAction(tr("LP Gaussian Filter"), this);
    LPGFAction->setStatusTip(
            tr("Using Gaussian lowpass filter to blur the image"));
    connect(LPGFAction, SIGNAL(triggered()),
            this, SLOT(LPGF()));

    HPGFAction = new QAction(tr("HP Gaussian Filter"), this);
    HPGFAction->setStatusTip(
            tr("Using Gaussian lowpass filter to blur the image"));
    connect(HPGFAction, SIGNAL(triggered()),
            this, SLOT(HPGF()));
}

void SimpleDIP::createImgMatchingMenuActions() {
    imgMatchingAction = new QAction(tr("Matching"), this);
    imgMatchingAction->setStatusTip(tr("Image Matching."));
    connect(imgMatchingAction, SIGNAL(triggered()),
            this, SLOT(imgMatching()));
}
