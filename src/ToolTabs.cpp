#include <QtGui>
#include <QtCore>

#include "ToolTabs.h"
#include <iostream>

using namespace std;

ToolTabs::ToolTabs(QWidget* parent)
	: QWidget(parent) {

	QHBoxLayout* layout = new QHBoxLayout;

	toolTabs = new QTabWidget();	

	colorTab = new ColorTab();
	transformTab = new TransformTab();

	toolTabs->addTab(colorTab, tr("Color Tools"));
	toolTabs->addTab(transformTab, tr("Transformation"));

	layout->addWidget(toolTabs);

	setLayout(layout);
	setMinimumWidth(250);
}

void ToolTabs::resetToolTabs() {
	colorTab->resetColorTab();
	transformTab->resetTransformTab();
}

ColorTab::ColorTab(QWidget* parent)
	: QWidget(parent) {

	QHBoxLayout* greyLayout = new QHBoxLayout;

	QVBoxLayout* mainLayout = new QVBoxLayout;

	QGridLayout* channelsLayout = new QGridLayout;
	QGridLayout* brightAndContrastLayout = new QGridLayout;
	
	QGroupBox* colorAndTones = new QGroupBox(tr("Color and Tones"));
	QGroupBox* brightAndContrast = new QGroupBox(tr("Brightness and Contrast"));

	
	// grey level adjustment
	greyLevelBox = new QSpinBox();
	greyLevelBox->setRange(1, 128);	

	greyLevelSlider = new QSlider(Qt::Horizontal);
	greyLevelSlider->setRange(1, 128);
	
	connect(greyLevelSlider, SIGNAL(valueChanged(int)),
			greyLevelBox, SLOT(setValue(int)));
	connect(greyLevelBox, SIGNAL(valueChanged(int)),
			greyLevelSlider, SLOT(setValue(int)));

	greyLayout->addWidget(greyLevelSlider);
	greyLayout->addWidget(greyLevelBox);
	
	// color and tones adjustment
	QHBoxLayout* okCancelLayout = new QHBoxLayout;

	red = new QLabel("red channel");
	green = new QLabel("green channel");
	blue = new QLabel("blue channel");

	redSlider = new QSlider(Qt::Horizontal);
	redSlider->setRange(-100, 100);
	redSlider->setValue(0);
	greenSlider = new QSlider(Qt::Horizontal);
	greenSlider->setRange(-100, 100);
	greenSlider->setValue(0);
	blueSlider = new QSlider(Qt::Horizontal);
	blueSlider->setRange(-100, 100);
	blueSlider->setValue(0);

	channelsLayout->addWidget(red, 0, 0);
	channelsLayout->addWidget(redSlider, 0, 1);
	channelsLayout->addWidget(green, 1, 0);
	channelsLayout->addWidget(greenSlider, 1, 1);
	channelsLayout->addWidget(blue, 2, 0);
	channelsLayout->addWidget(blueSlider, 2, 1);

	colorAndTones->setFlat(false);
	colorAndTones->setLayout(channelsLayout);
	colorAndTones->setMaximumHeight(120);

	// brightness and contrast
	brightness = new QLabel("brightness");
	contrast = new QLabel("contrast");

	brightnessSlider = new QSlider(Qt::Horizontal);
	brightnessSlider->setRange(-100, 100);
	brightnessSlider->setValue(0);
	contrastSlider = new QSlider(Qt::Horizontal);
	contrastSlider->setRange(-100, 100);
	contrastSlider->setValue(0);

	brightAndContrastLayout->addWidget(brightness, 0, 0);
	brightAndContrastLayout->addWidget(brightnessSlider, 0, 1);
	brightAndContrastLayout->addWidget(contrast, 1, 0);
	brightAndContrastLayout->addWidget(contrastSlider, 1, 1);

	brightAndContrast->setFlat(true);
	brightAndContrast->setLayout(brightAndContrastLayout);
	brightAndContrast->setMaximumHeight(100);
	
	// ok button
	okButton = new QPushButton("OK");
	okButton->setFixedWidth(70);
	// cancel button
	cancelButton = new QPushButton("Cancel");
	cancelButton->setFixedWidth(70);

	okCancelLayout->addWidget(okButton);
	okCancelLayout->addWidget(cancelButton);

	// main layout
	mainLayout->addLayout(greyLayout);
	mainLayout->addWidget(colorAndTones);
	mainLayout->addWidget(brightAndContrast);
	mainLayout->addLayout(okCancelLayout);

	mainLayout->addStretch();
	setLayout(mainLayout);
}

void ColorTab::resetColorTab() {
	redSlider->setValue(0);
	greenSlider->setValue(0);
	blueSlider->setValue(0);
	brightnessSlider->setValue(0);
}

TransformTab::TransformTab(QWidget* parent) 
	: QWidget(parent) {
	QVBoxLayout* transLayout = new QVBoxLayout;
	QHBoxLayout* resizeLayout = new QHBoxLayout;
	QHBoxLayout* okCancelLayout = new QHBoxLayout;

	resize = new QLabel("Resize");

	resizeSpinBox = new QSpinBox();
	resizeSpinBox->setRange(1, 500);
	resizeSpinBox->setValue(100);

	resizeSlider = new QSlider(Qt::Horizontal);
	resizeSlider->setRange(1, 500);
	resizeSlider->setValue(100);

	connect(resizeSpinBox, SIGNAL(valueChanged(int)),
			resizeSlider, SLOT(setValue(int)));
	connect(resizeSlider, SIGNAL(valueChanged(int)),
			resizeSpinBox, SLOT(setValue(int)));

	resizeLayout->addWidget(resizeSlider);
	resizeLayout->addWidget(resizeSpinBox);

	okButton = new QPushButton("OK");
	okButton->setFixedWidth(70);
	cancelButton = new QPushButton("Cancel");
	cancelButton->setFixedWidth(70);

	transLayout->addWidget(resize);
	transLayout->addLayout(resizeLayout);
	transLayout->addLayout(okCancelLayout);
	transLayout->addStretch();

	setLayout(transLayout);
}

void TransformTab::resetTransformTab() {
	resizeSpinBox->setValue(100);
	resizeSlider->setValue(100);
}
