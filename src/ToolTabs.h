#ifndef TOOLTABS_H
#define TOOLTABS_H

#include <QWidget>
#include <QTabWidget>
#include "Image.h"

class QSpinBox;
class QSlider;
class QLabel;
class QPushButton;

class ColorTab : public QWidget {

	Q_OBJECT;
	
public:
	ColorTab(QWidget* parent = NULL);
	void resetColorTab();
	
	QLabel *red;
	QLabel *green;
	QLabel *blue;
	QLabel *brightness;
	QLabel *contrast;

	QSpinBox *greyLevelBox;
	QSlider *greyLevelSlider;
	QSlider *redSlider;
	QSlider *greenSlider;
	QSlider *blueSlider;
	QSlider *brightnessSlider;
	QSlider *contrastSlider;

	QPushButton *okButton;
	QPushButton *cancelButton;
};

class TransformTab : public QWidget {

	Q_OBJECT;
	
public:
	TransformTab(QWidget* parent = NULL);
	void resetTransformTab();
	
	QLabel *resize;
	
	QSpinBox *resizeSpinBox;
	QSlider *resizeSlider;

	QPushButton *okButton;
	QPushButton *cancelButton;
};

class ToolTabs : public QWidget {
	Q_OBJECT;
public:
	ToolTabs(QWidget* parent = NULL);
	void resetToolTabs();

	QTabWidget* toolTabs;
	ColorTab* colorTab;
	TransformTab* transformTab;
};

class ImagesTab : public QWidget {
    Q_OBJECT;
signals:
    void changeMatchedImg(QString imgName);
public slots:
    void showPrevImg();
    void showNextImg();
public:
    ImagesTab(QStringList imgNames, QWidget* parent = NULL);
    void showImages(int begin);

    Image** images;
    QStringList matchingImages;
    int currImage; // From 0 to the length of the images.
    int currPos;   // From 0 to 5.
};

#endif
