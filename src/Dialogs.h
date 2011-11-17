#ifndef DIALOGS_H
#define DIALOGS_H

#include <QDialog>

class QSpinBox;
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

#endif
