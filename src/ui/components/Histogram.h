#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QWidget>
#include <QPainter>

class Histogram : public QWidget {

	Q_OBJECT;
	
public:
	Histogram(QWidget* parent = NULL);
	Histogram(int* arr, int n, QColor c, QWidget* parent = NULL);
	void setHistogram(int* arr, int n);
	void maximum();

	int* data;
	int size;
	int max;
    QColor color;

protected:
	void paintEvent(QPaintEvent* event);
};

#endif
