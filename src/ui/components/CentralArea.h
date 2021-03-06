#ifndef CENTRALAREA_H
#define CENTRALAREA_H

#include <QWidget>
#include <QScrollArea>
#include <QHBoxLayout>
#include "Image.h"

class CentralArea : public QWidget {
	Q_OBJECT;
public:
	CentralArea(QWidget* parent = NULL);

	Image* image;
	QScrollArea* imageArea;
};

class DoubleCentralArea : public QWidget {
	Q_OBJECT;
public:
	DoubleCentralArea(QWidget* parent = NULL);

	Image* image;
	Image* imageMatched;
	QScrollArea* imageArea;
	QScrollArea* imageAreaMatched;
};

#endif
