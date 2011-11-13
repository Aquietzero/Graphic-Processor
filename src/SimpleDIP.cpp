#include <QtGui>
#include <QtCore>

#include <iostream>
#include "SimpleDIP.h"

using namespace std;

SimpleDIP::SimpleDIP() {
	centralArea = new CentralArea();
	setCentralWidget(centralArea);

	createActions();
	createMenus();
	createStatusBar();
	createToolDockWidget();
	createInfoDockWidget();
	createConnects();

	setMinimumWidth(1200);
	setMinimumHeight(700);

	prevTabIndex = -1;
}

void SimpleDIP::closeEvent(QCloseEvent* event) {
	if (okToContinue()) {
		writeSettings();
		event->accept();
	}
	else {
		event->ignore();
	}
}

void SimpleDIP::writeSettings() {
}

bool SimpleDIP::okToContinue() {
	if (isWindowModified()) {
		int r = QMessageBox::warning(this, tr("Simple DIP"),
						tr("The picture has been modified.\n"
						   "Do you want to save your changes?"),
						QMessageBox::Yes | QMessageBox::No
						| QMessageBox::Cancel);
		if (r == QMessageBox::Yes) {
			return save();
		}
		else if (r == QMessageBox::Cancel) {
			return false;
		}
	}
	return true;
}

void SimpleDIP::open() {
	if (okToContinue()) {
		QString filename = QFileDialog::getOpenFileName(this, 
								tr("Open Images"), ".",
								tr("Image files (*)"));
		if (!filename.isEmpty()) { 
			centralArea->image->setImage(filename);
			setHistograms();

			QString shownName = QFileInfo(
			centralArea->image->imgName).fileName();
			setWindowTitle(tr("%1[*] - %2").arg(shownName)
								   .arg(tr("Simple DIP")));

			moveImage();
			setWindowModified(false);
		}
	}
}

void SimpleDIP::moveImage() {
	int w = centralArea->image->img->width();
	int h = centralArea->image->img->height();

	if (w < 600) w = (600 - w) / 2;
	else w = 0;

	if (h < 600) h = (600 - h) / 2;
	else h = 0;

	centralArea->image->move(w, h);
}
	
bool SimpleDIP::save() {
	if (centralArea->image->img != NULL)
		return saveAs();
	return false;
}

bool SimpleDIP::saveAs() {
	if (centralArea->image->img != NULL) {
		QString filename = QFileDialog::getSaveFileName(this,
								tr("Save Image"), ".",
								tr("Image Files (*.bmp)"));
		if (filename.isEmpty())
			return false;

		return saveImage(filename);
	}
	return false;
}

void SimpleDIP::tempSave() {
	if (centralArea->image->img != NULL) {
		centralArea->image->tempSaveImage();
		tools->colorTab->resetColorTab();
	}
}

bool SimpleDIP::saveImage(const QString &filename) {
	return centralArea->image->writeImage(filename);
}

void SimpleDIP::tempRestore() {
	if (centralArea->image->img != NULL) {
		centralArea->image->tempRestoreImage();
		setHistograms();
		tools->colorTab->resetColorTab();
	}
}

void SimpleDIP::setImageModified() {
	setWindowModified(true);
}

void SimpleDIP::setHistograms() {
	if (centralArea->image->img != NULL) {
		info->histogramR->setHistogram(
				centralArea->image->imgHistogramR, 256);
		info->histogramG->setHistogram(
				centralArea->image->imgHistogramG, 256);
		info->histogramB->setHistogram(
				centralArea->image->imgHistogramB, 256);
	}
}

bool SimpleDIP::checkTabSwitch() {
	int currTabIndex = tools->toolTabs->currentIndex();
	if (currTabIndex == prevTabIndex) {
		prevTabIndex = currTabIndex;
		return true;
	}
	else {
		prevTabIndex = currTabIndex;
		return false;
	}
}

void SimpleDIP::originalImage() {
	if (centralArea->image->img != NULL) {
		centralArea->image->originalImage();
		centralArea->image->getHistogram();
		setHistograms();

		centralArea->image->update();
		setWindowModified(false);
		tools->resetToolTabs();
		emit imageModified();
	}
}

/* The following methods are image processing slots */
void SimpleDIP::getRedChannel() {
	if (centralArea->image->img != NULL) {
		centralArea->image->tempSaveImage();
		centralArea->image->redChannel();
		setHistograms();
		tools->resetToolTabs();
		emit imageModified();
	}
}

void SimpleDIP::getGreenChannel() {
	if (centralArea->image->img != NULL) {
		centralArea->image->tempSaveImage();
		centralArea->image->greenChannel();
		setHistograms();
		tools->resetToolTabs();
		emit imageModified();
	}
}

void SimpleDIP::getBlueChannel() {
	if (centralArea->image->img != NULL) {
		centralArea->image->tempSaveImage();
		centralArea->image->blueChannel();
		setHistograms();
		tools->resetToolTabs();
		emit imageModified();
	}
}

void SimpleDIP::getGreyScale() {
	if (centralArea->image->img != NULL) {
		centralArea->image->tempSaveImage();
		centralArea->image->greyScale();
		setHistograms();
		tools->resetToolTabs();
		emit imageModified();
	}
}

void SimpleDIP::redChange(int rate) {
	if (centralArea->image->img != NULL) {
		centralArea->image->redChannelChange(rate);
		setHistograms();
		emit imageModified();
	}
}

void SimpleDIP::greenChange(int rate) {
	if (centralArea->image->img != NULL) {
		centralArea->image->greenChannelChange(rate);
		setHistograms();
		emit imageModified();
	}
}

void SimpleDIP::blueChange(int rate) {
	if (centralArea->image->img != NULL) {
		centralArea->image->blueChannelChange(rate);
		setHistograms();
		emit imageModified();
	}
}

void SimpleDIP::colorsChange() {
	if (centralArea->image->img != NULL) {
		if (!checkTabSwitch())
			centralArea->image->tempSaveImage();
		int rateR = tools->colorTab->redSlider->value();
		int rateG = tools->colorTab->greenSlider->value();
		int rateB = tools->colorTab->blueSlider->value();
		int rateBright = tools->colorTab->brightnessSlider->value();
		
		centralArea->image->colorsChange(
				rateR, rateG, rateB, rateBright);
		setHistograms();
		emit imageModified();
	}
}

void SimpleDIP::brightnessChange(int rate) {
	if (centralArea->image->img != NULL) {
		centralArea->image->brightness(rate);
		setHistograms();
		emit imageModified();
	}
}

void SimpleDIP::contrastChange(int rate) {
	if (centralArea->image->img != NULL) {
		centralArea->image->contrast(rate);
		setHistograms();
		emit imageModified();
	}
}

void SimpleDIP::hisEqualization() {
	if (centralArea->image->img != NULL) {
		centralArea->image->tempSaveImage();
		centralArea->image->histogramEqualization();
		setHistograms();
		tools->resetToolTabs();
		emit imageModified();
	}
}

void SimpleDIP::fixedHalftoning() {
	if (centralArea->image->img != NULL) {
		centralArea->image->tempSaveImage();

		int** arr = new int*[3];
		for (int i = 0; i < 3; ++i)
			arr[i] = new int[3];
		arr[0][0] = 7;
		arr[0][1] = 9;
		arr[0][2] = 5;
		arr[1][0] = 2;
		arr[1][1] = 1;
		arr[1][2] = 4;
		arr[2][0] = 6;
		arr[2][1] = 3;
		arr[2][2] = 8;

		centralArea->image->fixedHalftoning(3, 3, arr);
		setHistograms();
		tools->resetToolTabs();
		emit imageModified();
	}
}

void SimpleDIP::expandHalftoning() {
	if (centralArea->image->img != NULL) {
		centralArea->image->tempSaveImage();

		int** arr = new int*[3];
		for (int i = 0; i < 3; ++i)
			arr[i] = new int[3];
		arr[0][0] = 7;
		arr[0][1] = 9;
		arr[0][2] = 5;
		arr[1][0] = 2;
		arr[1][1] = 1;
		arr[1][2] = 4;
		arr[2][0] = 6;
		arr[2][1] = 3;
		arr[2][2] = 8;

		centralArea->image->expandHalftoning(3, 3, arr);
		setHistograms();
		tools->resetToolTabs();
		emit imageModified();
	}
}

void SimpleDIP::resizeImg() {
	if (centralArea->image->img != NULL) {
		if (!checkTabSwitch())
			centralArea->image->tempSaveImage();
		int rate = tools->transformTab->resizeSlider->value();
		centralArea->image->resizeImage(rate);
		emit imageModified();
	}
}

void SimpleDIP::laplaceTransform() {
	if (centralArea->image->img != NULL) {
		centralArea->image->tempSaveImage();
		centralArea->image->laplace();
		setHistograms();
		tools->resetToolTabs();
		emit imageModified();
	}
}

void SimpleDIP::blur() {
	if (centralArea->image->img != NULL) {
		centralArea->image->tempSaveImage();
		centralArea->image->blur();
		setHistograms();
		tools->resetToolTabs();
		emit imageModified();
	}
}

void SimpleDIP::weightedBlur() {
	if (centralArea->image->img != NULL) {
		centralArea->image->tempSaveImage();
		centralArea->image->weightedBlur();
		setHistograms();
		tools->resetToolTabs();
		emit imageModified();
	}
}

void SimpleDIP::laplaceEnhance() {
	if (centralArea->image->img != NULL) {
		centralArea->image->tempSaveImage();
		centralArea->image->laplaceEnhance();
		setHistograms();
		tools->resetToolTabs();
		emit imageModified();
	}
}

void SimpleDIP::unsharpMaskEnhance() {
	if (centralArea->image->img != NULL) {
		centralArea->image->tempSaveImage();
		centralArea->image->unsharpMasking();
		setHistograms();
		tools->resetToolTabs();
		emit imageModified();
	}
}

void SimpleDIP::highBoostEnhance() {
	if (centralArea->image->img != NULL) {
		centralArea->image->tempSaveImage();
		centralArea->image->highBoost();
		setHistograms();
		tools->resetToolTabs();
		emit imageModified();
	}
}

void SimpleDIP::fft() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();
        centralArea->image->spectrum();
        tools->resetToolTabs();
        emit imageModified();
    }
}

void SimpleDIP::ifft() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();
        centralArea->image->inverseSpectrum();
        tools->resetToolTabs();
        emit imageModified();
    }
}


void SimpleDIP::LPGF() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();
        centralArea->image->lowpassGaussian(30);
        tools->resetToolTabs();
        emit imageModified();
    }
}

void SimpleDIP::HPGF() {
    if (centralArea->image->img != NULL) {
        centralArea->image->tempSaveImage();
        centralArea->image->highpassGaussian(160);
        tools->resetToolTabs();
        emit imageModified();
    }
}

void SimpleDIP::createActions() {
	// open option in menubar
	openAction = new QAction(tr("&Open..."), this);
	openAction->setShortcut(QKeySequence::Open);
	openAction->setStatusTip(tr("Open an .bmp image file"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

	// save option in menubar
	saveAction = new QAction(tr("&Save"), this);
	saveAction->setShortcut(QKeySequence::Save);
	saveAction->setStatusTip(tr("Save the current image"));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

	// save as option in menubar
	saveAsAction = new QAction(tr("Save As..."), this);
	saveAsAction->setStatusTip(tr("Save the current image under a "
								  "new file name"));
	connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

	// quit option in menubar
	quitAction = new QAction(tr("&Quit..."), this);
	quitAction->setShortcut(tr("Ctrl+Q"));
	quitAction->setStatusTip(tr("Exit the application"));
	connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));	

	// color menu actions
	originalImageAction = new QAction(tr("Original Image"), this);
	originalImageAction->setStatusTip(
			tr("Redo down to the original image"));
	connect(originalImageAction, SIGNAL(triggered()),
			this, SLOT(originalImage()));

	redChannelAction = new QAction(tr("Red Channel"), this);
	redChannelAction->setStatusTip(
			tr("Get the red channel of the picture"));
	connect(redChannelAction, SIGNAL(triggered()), 
			this, SLOT(getRedChannel()));

	greenChannelAction = new QAction(tr("Green Channel"), this);
	greenChannelAction->setStatusTip(
			tr("Get the green channel of the picture"));
	connect(greenChannelAction, SIGNAL(triggered()), 
			this, SLOT(getGreenChannel()));

	blueChannelAction = new QAction(tr("Blue Channel"), this);
	blueChannelAction->setStatusTip(
			tr("Get the blue channel of the picture"));
	connect(blueChannelAction, SIGNAL(triggered()), 
			this, SLOT(getBlueChannel()));
				
	greyScaleAction = new QAction(tr("Grey Scale"), this);
	greyScaleAction->setStatusTip(
			tr("Get the grey scale of the picture"));
	connect(greyScaleAction, SIGNAL(triggered()), 
			this, SLOT(getGreyScale()));

	hisEqualizationAction = new QAction(tr("Histogram Equalization"), this);
	hisEqualizationAction->setStatusTip(
			tr("Histogram Equalization"));
	connect(hisEqualizationAction, SIGNAL(triggered()),
			this, SLOT(hisEqualization()));

	expandHalftoningAction = new QAction(tr("Expand Halftoning"), this);
	expandHalftoningAction->setStatusTip(
			tr("Expand Halftoning"));
	connect(expandHalftoningAction, SIGNAL(triggered()),
			this, SLOT(expandHalftoning()));

	fixedHalftoningAction = new QAction(tr("Fixed Halftoning"), this);
	fixedHalftoningAction->setStatusTip(
			tr("Fixed Halftoning"));
	connect(fixedHalftoningAction, SIGNAL(triggered()),
			this, SLOT(fixedHalftoning()));

	// filter menu action
	laplaceAction = new QAction(tr("&Laplace"), this);
	laplaceAction->setStatusTip(
			tr("Laplace Filtering for edge detection of the image"));
	connect(laplaceAction, SIGNAL(triggered()),
			this, SLOT(laplaceTransform()));

	blurAction = new QAction(tr("&Blur"), this);
	blurAction->setStatusTip(
			tr("Slightly blur the image"));
	connect(blurAction, SIGNAL(triggered()),
			this, SLOT(blur()));

	weightedBlurAction = new QAction(tr("&Weighted Blur"), this);
	weightedBlurAction->setStatusTip(
			tr("Using the weighted smooth filter to blur the image"));
	connect(weightedBlurAction, SIGNAL(triggered()),
			this, SLOT(weightedBlur()));

	laplaceEnhanceAction = new QAction(tr("&Laplace Enhance"), this);
	laplaceEnhanceAction->setStatusTip(
			tr("Using Laplace Factor to enhance the image"));
	connect(laplaceEnhanceAction, SIGNAL(triggered()),
			this, SLOT(laplaceEnhance()));

	unsharpMaskingAction = new QAction(tr("&Unsharp Masking"), this);
	unsharpMaskingAction->setStatusTip(
			tr("Using the original image to subtract its blured "
			   "version and then adds it by itself to get a unsharp "
			   "masking enhancement"));
	connect(unsharpMaskingAction, SIGNAL(triggered()),
			this, SLOT(unsharpMaskEnhance()));

	highBoostAction = new QAction(tr("&High Boost"), this);
	highBoostAction->setStatusTip(
			tr("Using the original image to subtract its blured "
			   "version, scales it for a specific factor and then "
			   " adds it by itself to get a high boost enhancement"));
	connect(highBoostAction, SIGNAL(triggered()),
			this, SLOT(highBoostEnhance()));

    fftAction = new QAction(tr("FFT"), this);
    fftAction->setStatusTip(
            tr("Calculate the fourier transformation of the current "
               "image."));
    connect(fftAction, SIGNAL(triggered()),
            this, SLOT(fft()));

    ifftAction = new QAction(tr("IFFT"), this);
    ifftAction->setStatusTip(
            tr("Calculate the fourier transformation of the current "
               "image."));
    connect(ifftAction, SIGNAL(triggered()),
            this, SLOT(ifft()));

    LPGFAction = new QAction(tr("LP Gaussian Filter"), this);
    LPGFAction->setStatusTip(
            tr("Using Gaussian lowpass filter to blur the image"));
    connect(LPGFAction, SIGNAL(triggered()),
            this, SLOT(LPGF()));

    HPGFAction = new QAction(tr("HP Gaussian Filter"), this);
    HPGFAction->setStatusTip(
            tr("Using Gaussian lowpass filter to blur the image"));
    connect(HPGFAction, SIGNAL(triggered()),
            this, SLOT(HPGF()));
}

void SimpleDIP::createMenus() {
	QFont menuFont("oldEnglish", 11);
	menuBar()->setFont(menuFont);

	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveAsAction);
	fileMenu->addAction(quitAction);

	toolMenu = menuBar()->addMenu(tr("&Tool"));
	toolMenu->addAction(originalImageAction);

	colorMenu = menuBar()->addMenu(tr("&Color"));

	channelMenu = new QMenu(tr("Channels"));
	channelMenu->addAction(redChannelAction);
	channelMenu->addAction(greenChannelAction);
	channelMenu->addAction(blueChannelAction);
	channelMenu->addAction(greyScaleAction);
	colorMenu->addMenu(channelMenu);

	autoMenu = new QMenu(tr("Auto"));
	autoMenu->addAction(hisEqualizationAction);
	colorMenu->addMenu(autoMenu);

	halftoningMenu = new QMenu(tr("Halftoning"));
	halftoningMenu->addAction(fixedHalftoningAction);
	halftoningMenu->addAction(expandHalftoningAction);
	colorMenu->addMenu(halftoningMenu);

	filterMenu = menuBar()->addMenu(tr("Fil&ter"));
	
	blurMenu = new QMenu(tr("&Blur"));
	blurMenu->addAction(blurAction);
	blurMenu->addAction(weightedBlurAction);
	filterMenu->addMenu(blurMenu);

	enhanceMenu = new QMenu(tr("&Enhance"));
	enhanceMenu->addAction(laplaceEnhanceAction);
	enhanceMenu->addAction(unsharpMaskingAction);
	enhanceMenu->addAction(highBoostAction);
	filterMenu->addMenu(enhanceMenu);

	edgeDetectMenu = new QMenu(tr("Edge &Detect"));
	edgeDetectMenu->addAction(laplaceAction);
	filterMenu->addMenu(edgeDetectMenu);

    fftMenu = menuBar()->addMenu(tr("FFT")); 
    fftMenu->addAction(fftAction);
    fftMenu->addAction(ifftAction);
    fftMenu->addAction(LPGFAction);
    fftMenu->addAction(HPGFAction);
}

void SimpleDIP::createStatusBar() {
	statusbar = statusBar();
}

void SimpleDIP::createToolDockWidget() {
	toolDockWidget = new QDockWidget(tr("Tool Box"));
	toolDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea |
									Qt::RightDockWidgetArea);
	tools = new ToolTabs();
	toolDockWidget->setWidget(tools);
	addDockWidget(Qt::RightDockWidgetArea, toolDockWidget);
}

void SimpleDIP::createInfoDockWidget() {
	infoDockWidget = new QDockWidget(tr("Information"));
	infoDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea |
									Qt::RightDockWidgetArea);
	info = new Information();
	infoDockWidget->setWidget(info);
	addDockWidget(Qt::LeftDockWidgetArea, infoDockWidget);
}

void SimpleDIP::createConnects() {
	connect(this, SIGNAL(imageModified()), 
			this, SLOT(setImageModified()));

	// color tab sliders
	connect(tools->colorTab->redSlider, SIGNAL(valueChanged(int)),
			this, SLOT(colorsChange()));
	connect(tools->colorTab->greenSlider, SIGNAL(valueChanged(int)),
			this, SLOT(colorsChange()));
	connect(tools->colorTab->blueSlider, SIGNAL(valueChanged(int)),
			this, SLOT(colorsChange()));
	connect(tools->colorTab->brightnessSlider, SIGNAL(valueChanged(int)),
			this, SLOT(colorsChange()));
	connect(tools->colorTab->contrastSlider, SIGNAL(valueChanged(int)),
			this, SLOT(contrastChange(int)));
	
	// transformation tab sliders
	connect(tools->transformTab->resizeSlider, SIGNAL(valueChanged(int)),
			this, SLOT(resizeImg()));

	// when ok button is pressed, the current changes will be
	// applied to the image
	connect(tools->colorTab->okButton, SIGNAL(clicked()),
			this, SLOT(tempSave()));
	connect(tools->colorTab->cancelButton, SIGNAL(clicked()),
			this, SLOT(tempRestore()));

	connect(tools->transformTab->okButton, SIGNAL(clicked()),
			this, SLOT(tempSave()));
	connect(tools->transformTab->cancelButton, SIGNAL(clicked()),
			this, SLOT(tempRestore()));
}
