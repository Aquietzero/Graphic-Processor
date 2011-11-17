#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include <time.h>
#include <cmath>

double gaussGenerator();
double gaussGenerator(double mean, double standardDeviation);

double impulseGenerator(double pa, double pb);

#endif
