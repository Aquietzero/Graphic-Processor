#ifndef IMAGEMATCHING_H
#define IMAGEMATCHING_H

#include <QMainWindow>

#include "CentralArea.h"
#include "ToolTabs.h"
#include "Information.h"
#include "Dialogs.h"

class QAction;

class ImageMatching : public QMainWindow {
    Q_OBJECT;

public slots:
    void changeMatchedImg(QString imgName);
public:
    ImageMatching(Image* image);
    void createImagesDockWidget();

private:
    QDockWidget* imagesDockWidget;
    ImagesTab* imagesTab;

    DoubleCentralArea* doubleCentralArea;

    QStringList matchingImgNames;
};

#endif
