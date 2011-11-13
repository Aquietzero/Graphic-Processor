#include "Information.h"

Information::Information(QWidget* parent)
	: QWidget(parent) {

	QVBoxLayout* infoLayout = new QVBoxLayout;

	QLabel* redChannelHistogram = new QLabel("<b>Red Channel Histogram</b>");
	QLabel* greenChannelHistogram = new QLabel("<b>Green Channel Histogram</b>");
	QLabel* blueChannelHistogram = new QLabel("<b>Blue Channel Histogram</b>");
	redChannelHistogram->setFixedHeight(15);
	greenChannelHistogram->setFixedHeight(15);
	blueChannelHistogram->setFixedHeight(15);

	int* arr = new int[256];
	for (int i = 0; i < 256; ++i)
		arr[i] = 0;
	histogramR = new Histogram(arr, 256);	
	histogramG = new Histogram(arr, 256);	
	histogramB = new Histogram(arr, 256);	

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
