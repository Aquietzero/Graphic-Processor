#include "CentralArea.h"
#include <iostream>

using namespace std;

CentralArea::CentralArea(QWidget* parent) 
	: QWidget(parent) {
	image = new Image();

	imageArea = new	QScrollArea();

	imageArea->setWidgetResizable(true);
	imageArea->setAutoFillBackground(true);
	imageArea->setBackgroundRole(QPalette::Dark);

	imageArea->setAlignment(Qt::AlignCenter);
	imageArea->setWidget(image);

	QHBoxLayout* layout = new QHBoxLayout;

	layout->addWidget(imageArea);

	setLayout(layout);
}

DoubleCentralArea::DoubleCentralArea(QWidget* parent) 
	: QWidget(parent) {
	image = new Image();
	imageArea = new	QScrollArea();

	imageArea->setWidgetResizable(true);
	imageArea->setAutoFillBackground(true);
	imageArea->setBackgroundRole(QPalette::Dark);

	imageArea->setAlignment(Qt::AlignCenter);
	imageArea->setWidget(image);

	QHBoxLayout* layout = new QHBoxLayout;

	layout->addWidget(imageArea);

    // Matched Image
	imageMatched = new Image();
	imageAreaMatched = new	QScrollArea();

	imageAreaMatched->setWidgetResizable(true);
	imageAreaMatched->setAutoFillBackground(true);
	imageAreaMatched->setBackgroundRole(QPalette::Dark);

	imageAreaMatched->setAlignment(Qt::AlignCenter);
	imageAreaMatched->setWidget(imageMatched);

	layout->addWidget(imageAreaMatched);
	setLayout(layout);
}


