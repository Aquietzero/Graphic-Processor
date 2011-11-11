#ifndef INFORMATION_H
#define INFORMATION_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "Histogram.h"

class Information : public QWidget {
	
	Q_OBJECT;
	
public:
	Information(QWidget* parent = NULL);

	Histogram* histogramR;
	Histogram* histogramG;
	Histogram* histogramB;
};

#endif
