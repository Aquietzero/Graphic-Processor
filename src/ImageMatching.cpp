#include <QtGui>
#include <QtCore>

#include <iostream>
#include "ImageMatching.h"

using namespace std;

ImageMatching::ImageMatching(Image* image) {
    doubleCentralArea = new DoubleCentralArea();
    setCentralWidget(doubleCentralArea);


    // Get file names of the images which matches the given image.
    matchingImgNames = image->match();
    createImagesDockWidget();

    // Show the given image.
    doubleCentralArea->image->setImage(image->imgName);
    int width  = doubleCentralArea->image->img->width();
    int height = doubleCentralArea->image->img->height();
    int size = width > height ? width : height;
    if (size > 400)
        doubleCentralArea->image->resizeImage(400. * 100 / size);

    // Show the current selected image.
    Image* currImage = imagesTab->images[imagesTab->currImage];
    doubleCentralArea->imageMatched->setImage(currImage->imgName);

    setMinimumWidth(1100);
    setMinimumHeight(600);
    doubleCentralArea->update();

    connect(imagesTab, SIGNAL(changeMatchedImg(QString)),
            this, SLOT(changeMatchedImg(QString)));
}

void ImageMatching::createImagesDockWidget() {
    imagesDockWidget = new QDockWidget(tr("Matching Images"));
    imagesDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
    
    imagesTab = new ImagesTab(matchingImgNames);
    imagesDockWidget->setWidget(imagesTab);
    addDockWidget(Qt::BottomDockWidgetArea, imagesDockWidget);
}

void ImageMatching::changeMatchedImg(QString imgName) {
    doubleCentralArea->imageMatched->setImage(imgName);
    int width  = doubleCentralArea->image->img->width();
    int height = doubleCentralArea->image->img->height();
    int size = width > height ? width : height;
    if (size > 400)
        doubleCentralArea->image->resizeImage(400. * 100 / size);
}
