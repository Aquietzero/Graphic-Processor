#include "Random.h"

double gaussGenerator() {
    double x1, x2, s;
    do {
        x1 = 2.0 * rand() / RAND_MAX - 1;
        x2 = 2.0 * rand() / RAND_MAX - 1;
        s = x1 * x1 + x2 * x2;
    }
    while (s >= 1);

    if (s == 0) return 0;
    else        return x1 * sqrt( (-2 * log(s)) / s);
}

double gaussGenerator(double mean, double standardDeviation) {
    return gaussGenerator() * standardDeviation + mean;
}

double impulseGenerator(double pa, double pb) {
    double randNum = (double)rand() / RAND_MAX;

    if (randNum < pa)      return -1;
    if (randNum < pa + pb) return  1;
    else                   return  0;
}
