#ifndef SIMPLEDIP_H
#define SIMPLEDIP_H

#include <QMainWindow>
#include "CentralArea.h"
#include "ToolTabs.h"
#include "Information.h"

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
	void tempRestore();  // when the ok buttons are pressed
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

	void resizeImg();

	void originalImage();

private:
	bool okToContinue();
	void writeSettings();

	void createActions();
	void createMenus();
	void createStatusBar();
	void createToolDockWidget();
	void createInfoDockWidget();
	void createConnects();

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

	QDockWidget* toolDockWidget;
	QDockWidget* infoDockWidget;

	QStatusBar* statusbar;

	CentralArea* centralArea;
	ToolTabs* tools;
	Information* info;

	int prevTabIndex;
};

#endif