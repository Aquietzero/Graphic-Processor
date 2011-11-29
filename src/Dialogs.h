#ifndef DIALOGS_H
#define DIALOGS_H

#include <QDialog>

class QSpinBox;
class QSlider;
class QDoubleSpinBox;
class QLabel;
class QPushButton;
class QLineEdit;

class GaussianNoiseDialog : public QDialog {

    Q_OBJECT;

public:
    GaussianNoiseDialog(QDialog* parent = NULL);
    
    
signals:
    void applySettings(int mean, int sd);
    void closeAndApplySettings();
    void closeNotApplySettings();

public slots:
    void applyNotClose();
    void closeAndApply();
    void closeNotApply();

private:
    QPushButton* apply;
    QPushButton* done;
    QPushButton* cancel;

    QSpinBox* meanBox;
    QSpinBox* sdBox;
};

class ImpulseNoiseDialog : public QDialog {

    Q_OBJECT;

public:
    ImpulseNoiseDialog(QDialog* parent = NULL);
    
    
signals:
    void applySettings(double pa, double pb);
    void closeAndApplySettings();
    void closeNotApplySettings();

public slots:
    void applyNotClose();
    void closeAndApply();
    void closeNotApply();

private:
    QPushButton* apply;
    QPushButton* done;
    QPushButton* cancel;

    QDoubleSpinBox* paBox;
    QDoubleSpinBox* pbBox;
};

class SpatialFilteringDialog : public QDialog {

    Q_OBJECT;

public:
    SpatialFilteringDialog(QDialog* parent = NULL);

signals:
    void applySettings(int** filter);
    void closeAndApplySettings();
    void closeNotApplySettings();

public slots:
    void applyNotClose();
    void closeAndApply();
    void closeNotApply();

private:
    QPushButton* apply;
    QPushButton* done;
    QPushButton* cancel;

    QLineEdit** filterEntries;
};

class ColorExtractDialog : public QDialog {

    Q_OBJECT;

public:
    ColorExtractDialog(QDialog* parent = NULL);

signals:
    void applySettings(int r, int g, int b, int range);
    void closeAndApplySettings();
    void closeNotApplySettings();

public slots:
    void applyNotClose();
    void closeAndApply();
    void closeNotApply();

private slots:
    void setRedValue(int);
    void setGreenValue(int);
    void setBlueValue(int);
    void setRangeValue(int);

private:
    QPushButton* apply;
    QPushButton* done;
    QPushButton* cancel;

    QLabel* redValue;
    QLabel* greenValue;
    QLabel* blueValue;
    QLabel* rangeValue;

    QSlider* redComponent;
    QSlider* greenComponent;
    QSlider* blueComponent;
    QSlider* rangeComponent;
};

#endif
