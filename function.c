#include "function.h"
#include <stdio.h>
#include <math.h>

double rastrigin(double params[], int dim) {
    int i = 0;
    double sum = 0.0;
    for (i = 0; i < dim; i++) {

        sum += (pow(params[i], 2) - RASTR_A * cos(TWO_T_PI * params[i]));
    }
    return sum + RASTR_A * dim;
}

/*
 * www.zsd.ict.pwr.wroc.pl/files/docs/functions.pdf [s 20]
 */
double michalewicz(double params[], int dim) {
    int i = 0;
    double sum = 0.0;
    for (i = 0; i < dim; i++) {
        sum += sin(params[i]) * pow(sin(((i + 1) * pow(params[i], 2)) / PI), 2 * MICH_M);
    }
    return sum * -1.0;
}

double parabol(double params[], int dim) {

    int i = 0;
    double sum = 0.0;
    for (i = 0; i < dim; i++) {
        sum += pow(params[i], 2);
    }
    return sum;
}

double linear(double params[], int dim) {
    int i = 0;
    double sum = 0.0;
    for (i = 0; i < dim; i++) {
        sum += params[i] - 1;
    }
    return sum;
}

