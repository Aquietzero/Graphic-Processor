#ifndef RECORD_H
#define RECORD_H

#include <QFile>
#include <QTextStream>

#include <QVector>
#include <QStringList>
#include <QString>

#include "Image.h"

#define RANGE 10000
#define N_WH 8
#define N_Partition 10
#define N_Level 8
#define PI 3.1415926

//double H_Weight = 4;
//double S_Weight = 1;
//double I_Weight = 9;
//double WEIGHT[] = {1, 1, 1, 1, 5, 5, 5, 5, 11, 9};
double H_Weight = 0;
double S_Weight = 0;
double I_Weight = 20;
double WEIGHT[] = {3, 3, 3, 3, 5, 5, 5, 5, 15, 7};

class Record{
    public:
        Record(){}
        Record(QString);
        Record(QVector<QVector<QVector<double> > >, int, int, QString);

        QVector<QVector<QVector<double> > > histograms;
        int width;
        int height;
        QString fname;
};

class Record2{
    public:
        QString fname;
        double similarity;
};

int redFunc(int grey, int r, int g, int b, int range);
int greenFunc(int grey, int r, int g, int b, int range);
int blueFunc(int grey, int r, int g, int b, int range);

int quantizationH(int level);
int quantizationS(int level);
int quantizationI(int level);

double histogramCompare(QVector<double>, QVector<double>);
double imgMatching(QVector<QVector<QVector<double> > >);

QVector<Record> ImgRecords();
QStringList matchedImgsName(Record, QVector<Record>);

int similarityCmp(Record2, Record2);

#endif
