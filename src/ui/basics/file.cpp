#include <QtGui>
#include <QtCore>

#include <iostream>
#include "../SimpleDIP.h"

void SimpleDIP::closeEvent(QCloseEvent* event) {
    if (okToContinue()) {
        writeSettings();
        event->accept();
    }
    else {
        event->ignore();
    }
}

void SimpleDIP::writeSettings() {
}

bool SimpleDIP::okToContinue() {
    if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("Simple DIP"),
                tr("The picture has been modified.\n"
                    "Do you want to save your changes?"),
                QMessageBox::Yes | QMessageBox::No
                | QMessageBox::Cancel);
        if (r == QMessageBox::Yes) {
            return save();
        }
        else if (r == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

void SimpleDIP::open() {
    if (okToContinue()) {
        QString filename = QFileDialog::getOpenFileName(this, 
                tr("Open Images"), ".",
                tr("Image files (*)"));
        if (!filename.isEmpty()) { 
            centralArea->image->setImage(filename);
            setHistograms();

            QString shownName = QFileInfo(
                    centralArea->image->imgName).fileName();
            setWindowTitle(tr("%1[*] - %2").arg(shownName)
                    .arg(tr("Simple DIP")));

            moveImage();
            setWindowModified(false);
        }
    }
}

void SimpleDIP::moveImage() {
    int w = centralArea->image->img->width();
    int h = centralArea->image->img->height();

    if (w < 600) w = (600 - w) / 2;
    else w = 0;

    if (h < 600) h = (600 - h) / 2;
    else h = 0;

    centralArea->image->move(w, h);
}

bool SimpleDIP::save() {
    if (centralArea->image->img != NULL)
        return saveAs();
    return false;
}

bool SimpleDIP::saveAs() {
    if (centralArea->image->img != NULL) {
        QString filename = QFileDialog::getSaveFileName(this,
                tr("Save Image"), ".",
                tr("Image Files (*.bmp)"));
        if (filename.isEmpty())
            return false;

        return saveImage(filename);
    }
    return false;
}

void SimpleDIP::tempSave() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();
        tools->colorTab->resetColorTab();
    }
}

bool SimpleDIP::saveImage(const QString &filename) {
    return centralArea->image->writeImage(filename);
}

void SimpleDIP::tempRestore() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempRestoreImage();
        setHistograms();
        tools->colorTab->resetColorTab();
    }
}

void SimpleDIP::setImageModified() {
    setWindowModified(true);
}

void SimpleDIP::setHistograms() {
    if (centralArea->image->img != NULL) {
        info->histogramR->setHistogram(
                centralArea->image->imgHistogramR, 256);
        info->histogramG->setHistogram(
                centralArea->image->imgHistogramG, 256);
        info->histogramB->setHistogram(
                centralArea->image->imgHistogramB, 256);
    }
}

bool SimpleDIP::checkTabSwitch() {
    int currTabIndex = tools->toolTabs->currentIndex();
    if (currTabIndex == prevTabIndex) {
        prevTabIndex = currTabIndex;
        return true;
    }
    else {
        prevTabIndex = currTabIndex;
        return false;
    }
}

void SimpleDIP::originalImage() {
    if (centralArea->image->img != NULL) {
        centralArea->image->originalImage();
        centralArea->image->getHistogram();
        setHistograms();

        centralArea->image->update();
        setWindowModified(false);
        tools->resetToolTabs();
        emit imageModified();
    }
}

