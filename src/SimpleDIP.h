#ifndef SIMPLEDIP_H
#define SIMPLEDIP_H

#include <QMainWindow>

#include "CentralArea.h"
#include "ToolTabs.h"
#include "Information.h"
#include "Dialogs.h"

class QAction;

class SimpleDIP : public QMainWindow {
	Q_OBJECT;
public:
	SimpleDIP();

protected:
	void closeEvent(QCloseEvent* event);

signals:
	void imageModified();

private slots:
	// file operations
	void open();
	bool save();         // when the save option is selected
	bool saveAs();       // when the saveAs option is selected
	void tempSave();     // when the ok buttons are pressed
	void tempRestore();  // when the cancel buttons are pressed
	void setImageModified();

	// image processing slots
	void getRedChannel();
	void getGreenChannel();
	void getBlueChannel();
	void getGreyScale();

	void redChange(int rate);
	void greenChange(int rate);
	void blueChange(int rate);
	void colorsChange();
	void contrastChange(int rate);

	void brightnessChange(int rate);
	void hisEqualization();
	void fixedHalftoning();
	void expandHalftoning();

	void laplaceTransform();

	void blur();
	void weightedBlur();

	void laplaceEnhance();
	void unsharpMaskEnhance();
	void highBoostEnhance();

    void spatialFiltering();
    void applySpatialFiltering(int** filter);

	void resizeImg();

    void gaussianNoise();
    void addGaussianNoise(int mean, int sd);
    void impulseNoise();
    void addImpulseNoise(double pa, double pb);

    void medianFiltering();
    void maximumFiltering();
    void minimumFiltering();

	void originalImage();

    void fft();
    void ifft();
    void LPGF();
    void HPGF();

private:
	bool okToContinue();
	void writeSettings();

	void createActions();
	void createMenus();
	void createStatusBar();
	void createToolDockWidget();
	void createInfoDockWidget();
	void createConnects();

    // actions
    void createFileMenuActions();
    void createToolMenuActions();
    void createColorMenuActions();
    void createFilterMenuActions();
    void createFFTMenuActions();


	bool saveImage(const QString &filename);

	void moveImage();

	void resetSliders();
	void setHistograms();

	bool checkTabSwitch();

//--file menu
	QMenu* fileMenu;
	// actions of file menu
	QAction* openAction;
	QAction* saveAction;
	QAction* saveAsAction;
	QAction* quitAction;

//--tool menu
	QMenu* toolMenu;
	QAction* originalImageAction;

//--color menu
	QMenu* colorMenu;
	QMenu* channelMenu;    // submenu in color menu
	// actions of channel menu
	QAction* redChannelAction;
	QAction* greenChannelAction;
	QAction* blueChannelAction;
	QAction* greyScaleAction;

	QMenu* autoMenu;       // submenu in color menu
	QAction* hisEqualizationAction;

	QMenu* halftoningMenu; // submenu in color menu
	QAction* fixedHalftoningAction;
	QAction* expandHalftoningAction;

//--filter menu
	QMenu* filterMenu;

	QMenu* edgeDetectMenu;
	QAction* laplaceAction;

	QMenu* blurMenu;
	QAction* blurAction;
	QAction* weightedBlurAction;

	QMenu* enhanceMenu;
	QAction* laplaceEnhanceAction;
	QAction* unsharpMaskingAction;
	QAction* highBoostAction;

    QMenu* noiseMenu;
    QAction* gaussianNoiseAction;
    QAction* impulseNoiseAction;

    QMenu* nonlinearFilteringMenu;
    QAction* medianFilteringAction;
    QAction* maximumFilteringAction;
    QAction* minimumFilteringAction;

    QAction* spatialFilteringAction;
//--fourier menu
    QMenu* fftMenu;
    QAction* fftAction;
    QAction* ifftAction;
    QAction* LPGFAction;
    QAction* HPGFAction;

// others
	QDockWidget* toolDockWidget;
	QDockWidget* infoDockWidget;

	QStatusBar* statusbar;

	CentralArea* centralArea;
	ToolTabs* tools;
	Information* info;


	int prevTabIndex;
};

#endif
