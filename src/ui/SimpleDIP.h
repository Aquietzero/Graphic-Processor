#ifndef SIMPLE_DIP_H
#define SIMPLE_DIP_H

#include <QMainWindow>

#include "components/CentralArea.h"
#include "components/ToolTabs.h"
#include "components/Information.h"
#include "components/Dialogs.h"
#include "components/ImageMatching.h"

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

    // File operations.
    void open();
    bool save();         // when the save option is selected
    bool saveAs();       // when the saveAs option is selected
    void tempSave();     // when the ok buttons are pressed
    void tempRestore();  // when the cancel buttons are pressed
    void setImageModified();

    // Image channel operations.
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

    // Histogram Equalization.
    void hisEqualization();
    void hisEqualizationAVG();

    // Halftoning
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

    // Resize the image.
    void resizeImg();

    // Adding noise to the image.
    void gaussianNoise();
    void addGaussianNoise(int mean, int sd);
    void impulseNoise();
    void addImpulseNoise(double pa, double pb);

    void colorExtracting();
    void applyColorExtracting(int r, int g, int b, int range);

    void medianFiltering();
    void maximumFiltering();
    void minimumFiltering();

    void originalImage();

    // Fourier transformations.
    void fft();
    void ifft();
    void LPGF();
    void HPGF();

    // Image matching.
    void imgMatching();

    private:
    bool okToContinue();
    void writeSettings();

    void createActions();
    void createMenus();
    void createStatusBar();
    void createToolDockWidget();
    void createInfoDockWidget();
    void createConnects();

    // Actions
    void createFileMenuActions();
    void createToolMenuActions();
    void createColorMenuActions();
    void createFilterMenuActions();
    void createFFTMenuActions();
    void createImgMatchingMenuActions();

    bool saveImage(const QString &filename);

    void moveImage();

    void resetSliders();
    void setHistograms();

    bool checkTabSwitch();

    // File Menu.
    QMenu* fileMenu;

    QAction* openAction;
    QAction* saveAction;
    QAction* saveAsAction;
    QAction* quitAction;

    // Tool Menu.
    QMenu* toolMenu;
    QAction* originalImageAction;

    // Color Menu.
    QMenu* colorMenu;

    QAction* extractColorAction;

    QMenu* channelMenu;    // submenu in color menu

    // Menu for color channels.
    QAction* redChannelAction;
    QAction* greenChannelAction;
    QAction* blueChannelAction;
    QAction* greyScaleAction;

    QMenu* autoMenu;       // submenu in color menu
    QAction* hisEqualizationAction;
    QAction* hisEqualizationAVGAction;

    QMenu* halftoningMenu; // submenu in color menu
    QAction* fixedHalftoningAction;
    QAction* expandHalftoningAction;

    // All kinds of filters.
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

    // Menus for fourier transformations.
    QMenu* fftMenu;
    QAction* fftAction;
    QAction* ifftAction;
    QAction* LPGFAction;
    QAction* HPGFAction;

    // Image matching.
    QMenu* imgMatchingMenu;
    QAction* imgMatchingAction;

    // Components of the ui.
    QDockWidget* toolDockWidget;
    QDockWidget* infoDockWidget;

    QStatusBar* statusbar;

    CentralArea* centralArea;
    ToolTabs* tools;
    Information* info;

    int prevTabIndex;
};

#endif
