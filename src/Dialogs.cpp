#include <QtGui>
#include <QtCore>

#include "Dialogs.h"

/* Gaussian Noise Dialog is used to accept the input from the user
 * and apply the arguments as the mean and standard deviation to 
 * add the gaussian noise to the image.
 */
GaussianNoiseDialog::GaussianNoiseDialog(QDialog* parent)
    : QDialog(parent) {

    QLabel* meanLabel = new QLabel("Mean");
    QLabel* sdLabel   = new QLabel("Standard Deviation");

    meanBox = new QSpinBox;
    sdBox   = new QSpinBox;

    apply  = new QPushButton("Apply");
    done   = new QPushButton("Done");
    cancel = new QPushButton("Cancel");

    QGridLayout* inputArea = new QGridLayout;
    inputArea->addWidget(meanLabel, 0, 0);
    inputArea->addWidget(meanBox  , 0, 1);
    inputArea->addWidget(sdLabel  , 1, 0);
    inputArea->addWidget(sdBox    , 1, 1);

    QHBoxLayout* buttons = new QHBoxLayout;
    buttons->addWidget(apply);
    buttons->addWidget(done);
    buttons->addWidget(cancel);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(inputArea);
    layout->addLayout(buttons);

    connect(apply,  SIGNAL(clicked()), this, SLOT(applyNotClose()));
    connect(done,   SIGNAL(clicked()), this, SLOT(closeAndApply()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(closeNotApply()));

    this->setLayout(layout);
    this->show();
}

void GaussianNoiseDialog::applyNotClose() {
    int mean = meanBox->value();
    int sd   = sdBox->value();
    emit applySettings(mean, sd);
}

void GaussianNoiseDialog::closeAndApply() {
    emit closeAndApplySettings();
    this->close();
}

void GaussianNoiseDialog::closeNotApply() {
    emit closeNotApplySettings();
    this->close();
}


/* Impulse Noise Dialog is used to offer a dialog for the user to 
 * enter the threshold probabilities in the impulse noise model.
 * p_a is the lower impulse while p_b is the higher impulse.
 */
ImpulseNoiseDialog::ImpulseNoiseDialog(QDialog* parent)
    : QDialog(parent) {

    QLabel* paLabel = new QLabel("Probability a");
    QLabel* pbLabel = new QLabel("Probability b");

    paBox = new QDoubleSpinBox;
    pbBox = new QDoubleSpinBox;

    apply  = new QPushButton("Apply");
    done   = new QPushButton("Done");
    cancel = new QPushButton("Cancel");

    QGridLayout* inputArea = new QGridLayout;
    inputArea->addWidget(paLabel, 0, 0);
    inputArea->addWidget(paBox  , 0, 1);
    inputArea->addWidget(pbLabel  , 1, 0);
    inputArea->addWidget(pbBox    , 1, 1);

    QHBoxLayout* buttons = new QHBoxLayout;
    buttons->addWidget(apply);
    buttons->addWidget(done);
    buttons->addWidget(cancel);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(inputArea);
    layout->addLayout(buttons);

    connect(apply,  SIGNAL(clicked()), this, SLOT(applyNotClose()));
    connect(done,   SIGNAL(clicked()), this, SLOT(closeAndApply()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(closeNotApply()));

    this->setLayout(layout);
    this->show();
}

void ImpulseNoiseDialog::applyNotClose() {
    double pa = paBox->value();
    double pb = pbBox->value();

    if (pa + pb > 1)
        QMessageBox::warning(this, tr("Input Error"),
                tr("The sum of the given two probabilities should be "
                   "less than or equal to 1."), QMessageBox::Ok);
    else
        emit applySettings(pa, pb);
}

void ImpulseNoiseDialog::closeAndApply() {
    emit closeAndApplySettings();
    this->close();
}

void ImpulseNoiseDialog::closeNotApply() {
    emit closeNotApplySettings();
    this->close();
}


/* Spatial Filtering Dialog allows the user to give a filter to 
 * spatial fiter the image.
 */
SpatialFilteringDialog::SpatialFilteringDialog(QDialog* parent)
    : QDialog(parent) {

    QLabel* title = new QLabel("Spatial Filter:");

    filterEntries = (QLineEdit**)malloc(sizeof(QLineEdit*) * 9);
    for (int i = 0; i < 9; ++i) {
        filterEntries[i] = new QLineEdit;
        filterEntries[i]->setMaxLength(5);
        filterEntries[i]->setMaximumWidth(50);
        filterEntries[i]->setMaximumHeight(50);
    }

    apply  = new QPushButton("Apply");
    done   = new QPushButton("Done");
    cancel = new QPushButton("Cancel");

    QGridLayout* filter = new QGridLayout;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) 
            filter->addWidget(filterEntries[i*3+j], i, j);

    QHBoxLayout* buttons = new QHBoxLayout;
    buttons->addWidget(apply);
    buttons->addWidget(done);
    buttons->addWidget(cancel);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(title);
    layout->addLayout(filter);
    layout->addLayout(buttons);

    connect(apply,  SIGNAL(clicked()), this, SLOT(applyNotClose()));
    connect(done,   SIGNAL(clicked()), this, SLOT(closeAndApply()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(closeNotApply()));

    this->setLayout(layout);
    this->show();
}

void SpatialFilteringDialog::applyNotClose() {
    int value;
    int** filter = new int*[3];

    for (int i = 0; i < 3; ++i)
        filter[i] = new int[3];

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            value = filterEntries[i*3+j]->text().toInt();
            filter[i][j] = value;
        }

    emit applySettings(filter);
}

void SpatialFilteringDialog::closeAndApply() {
    emit closeAndApplySettings();
    this->close();
}

void SpatialFilteringDialog::closeNotApply() {
    emit closeNotApplySettings();
    this->close();
}

ColorExtractDialog::ColorExtractDialog(QDialog* parent)
    : QDialog(parent) {

    QLabel* red   = new QLabel("Red:");
    QLabel* green = new QLabel("Green:");
    QLabel* blue  = new QLabel("Blue:");
    QLabel* range = new QLabel("Range:");

    redValue   = new QLabel("0");
    greenValue = new QLabel("0");
    blueValue  = new QLabel("0");
    rangeValue = new QLabel("0");

    redComponent   = new QSlider(Qt::Horizontal);
    greenComponent = new QSlider(Qt::Horizontal);
    blueComponent  = new QSlider(Qt::Horizontal);
    rangeComponent = new QSlider(Qt::Horizontal);

    redComponent->setRange(0, 255);
    greenComponent->setRange(0, 255);
    blueComponent->setRange(0, 255);
    rangeComponent->setRange(0, 255);

    apply  = new QPushButton("Apply");
    done   = new QPushButton("Done");
    cancel = new QPushButton("Cancel");


    QGridLayout* sliders = new QGridLayout;

    sliders->addWidget(red,   0, 0);
    sliders->addWidget(green, 1, 0);
    sliders->addWidget(blue,  2, 0);
    sliders->addWidget(range, 3, 0);

    sliders->addWidget(redComponent,   0, 1);
    sliders->addWidget(greenComponent, 1, 1);
    sliders->addWidget(blueComponent,  2, 1);
    sliders->addWidget(rangeComponent, 3, 1);

    sliders->addWidget(redValue,   0, 2);
    sliders->addWidget(greenValue, 1, 2);
    sliders->addWidget(blueValue,  2, 2);
    sliders->addWidget(rangeValue, 3, 2);

    QHBoxLayout* buttons = new QHBoxLayout;
    buttons->addWidget(apply);
    buttons->addWidget(done);
    buttons->addWidget(cancel);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(sliders);
    layout->addLayout(buttons);

    connect(apply,  SIGNAL(clicked()), this, SLOT(applyNotClose()));
    connect(done,   SIGNAL(clicked()), this, SLOT(closeAndApply()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(closeNotApply()));

    connect(redComponent, SIGNAL(valueChanged(int)),
            this, SLOT(setRedValue(int)));
    connect(greenComponent, SIGNAL(valueChanged(int)),
            this, SLOT(setGreenValue(int)));
    connect(blueComponent, SIGNAL(valueChanged(int)),
            this, SLOT(setBlueValue(int)));
    connect(rangeComponent, SIGNAL(valueChanged(int)),
            this, SLOT(setRangeValue(int)));

    this->setLayout(layout);
    this->show();
}

void ColorExtractDialog::setRedValue(int red) {
    QString str;
    str = QString("%1").arg(red);
    redValue->setText(str);
}

void ColorExtractDialog::setGreenValue(int green) {
    QString str;
    str = QString("%1").arg(green);
    greenValue->setText(str);
}

void ColorExtractDialog::setBlueValue(int blue) {
    QString str;
    str = QString("%1").arg(blue);
    blueValue->setText(str);
}

void ColorExtractDialog::setRangeValue(int range) {
    QString str;
    str = QString("%1").arg(range);
    rangeValue->setText(str);
}

void ColorExtractDialog::applyNotClose() {
    emit applySettings(redComponent->value(),
                       greenComponent->value(),
                       blueComponent->value(),
                       rangeComponent->value());
}

void ColorExtractDialog::closeAndApply() {
    emit closeAndApplySettings();
    this->close();
}

void ColorExtractDialog::closeNotApply() {
    emit closeNotApplySettings();
    this->close();
}

