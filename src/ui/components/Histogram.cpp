#include "Histogram.h"

Histogram::Histogram(QWidget* parent) 
	: QWidget(parent) {
	size = 255;
	max = 0;
	data = new int[255];
	for (int i = 0; i < size; ++i)
		data[i] = 0;

	setMinimumWidth(255);
	setMinimumHeight(160);
}

Histogram::Histogram(int* arr, int n, QColor c, QWidget* parent)
	: QWidget(parent) {
	
	size = n;
    color = c;
	data = new int[n];
	for (int i = 0; i < size; ++i)
		data[i] = arr[i];

	maximum();

	setFixedWidth(255);
	setFixedHeight(160);
}

void Histogram::setHistogram(int* arr, int n) {
	if (n == size) {
		for (int i = 0; i < n; ++i)
			data[i] = arr[i];
	} else {
		data = new int[n];
		for (int i = 0; i < size; ++i)
			data[i] = arr[i];
	}
	maximum();

	update();
}

void Histogram::maximum() {
	max = 0;
	for (int i = 0; i < size; ++i) {
		if (data[i] > max)
			max = data[i];
	}
}

void Histogram::paintEvent(QPaintEvent* event) {
	int bgW = width();
	int bgH = height();
	int bgh = bgH / 4;
	int grey = 150;
	int x = 0;
	int y = 0;

	QPainter painter(this);

	painter.setRenderHint(QPainter::Antialiasing, true);

	// background
	for (int i = 0; i < 4; ++i) {
		painter.setPen(QPen(QColor(grey, grey, grey)));
		painter.setBrush(QBrush(QColor(grey, grey, grey)));
		painter.drawRect(x, y, bgW, bgh);
		y += bgh;
		grey -= 10;
	}

    // data
    painter.setPen(QPen(color));
    painter.setBrush(QBrush(color));
    int dataW = (float)(bgW - 40) / size;
    dataW = dataW == 0 ? 1 : dataW;
    int dataH;
    for (int i = 0; i < size; ++i) {
        x = dataW * i;
        dataH = (int)((float)data[i] * bgH / max);
        y = bgH - dataH;
        if (y >= 0 && dataH >= 0)
            painter.drawRect(x, y, dataW, dataH);
    }
}
