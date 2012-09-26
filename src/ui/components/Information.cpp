#include "Information.h"

Information::Information(QWidget* parent)
	: QWidget(parent) {

	QVBoxLayout* infoLayout = new QVBoxLayout;

	QLabel* redChannelHistogram = new QLabel("Red Histogram");
	QLabel* greenChannelHistogram = new QLabel("Green Histogram");
	QLabel* blueChannelHistogram = new QLabel("Blue Histogram");
	redChannelHistogram->setFixedHeight(15);
	greenChannelHistogram->setFixedHeight(15);
	blueChannelHistogram->setFixedHeight(15);

	int* arr = new int[256];
	for (int i = 0; i < 256; ++i)
		arr[i] = 0;

	histogramR = new Histogram(arr, 256, QColor(255, 0, 0, 50));	
	histogramG = new Histogram(arr, 256, QColor(0, 255, 0, 50));	
	histogramB = new Histogram(arr, 256, QColor(0, 0, 255, 50));	

	infoLayout->addWidget(redChannelHistogram);
	infoLayout->addWidget(histogramR);
	infoLayout->addWidget(greenChannelHistogram);
	infoLayout->addWidget(histogramG);
	infoLayout->addWidget(blueChannelHistogram);
	infoLayout->addWidget(histogramB);
	infoLayout->addStretch();

	setLayout(infoLayout);

	setFixedWidth(260);
	setMinimumHeight(700);
}
