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

	//imageArea->setFixedWidth(600);
	//imageArea->setFixedHeight(600);

	imageArea->setAlignment(Qt::AlignCenter);
	imageArea->setWidget(image);

	QHBoxLayout* layout = new QHBoxLayout;

	layout->addWidget(imageArea);
	setLayout(layout);
}
