/* 
 * File:   main.c
 * Author: artur
 *
 * Created on 10 kwiecień 2013, 19:12
 */

#include <stdio.h>
#include <stdlib.h>
#include "PSO.h"
#include "function.h"

int main(int argc, char** argv) {

    /*
     * zharkodowane parametry
     * To już Ty musisz dostarczyć z conf manager albo z linii poleceń
     */

//    //DLA RASTRIGINA
//    int partNum = 100;
//    int iters = 2000;
//    int dim = 2; //2 oznacza funkcję dwóch zmiennych ale rastrigin może być n wymiarowy, tu nie ma ograniczeń
//    double (*functionPointer)(double*, int) = rastrigin;
//    double fiSwarm = 0.01;
//    double fiParticle = 1.9;
//    double omegaVal = 0.7;
//    
//    /*
//     * inicjalizujemy pso w przestrzeni strowrzonej ze współrzędnych o takich ograniczeniah
//     */
//    double psoMinPerVecElem = -5.12;
//    double psoMaxPerVecElem = 5.12;

        // DLA F MICHALEWICZA
        int partNum = 100;
        int iters = 2000;
        int dim = 24; //2 oznacza funkcję jednej zmiennej ale michalewicz może być n wymiarowy, tu nie ma ograniczeń
        double (*functionPointer)(double*, int) = parabol;
        double fiSwarm = 0.2;
        double fiParticle = 3.1;
        double omegaVal = 23.1;
        double psoMinPerVecElem = -0.1;
        double psoMaxPerVecElem = 0.1;

    /*
     * pakujemy parametry w strukturę
     */
    PsoParams *p = createPsoParams(iters, partNum, dim, functionPointer, fiSwarm, fiParticle, omegaVal, psoMinPerVecElem, psoMaxPerVecElem);

    /*
     * optymalizacja
     */
    double *v = PSO(p);

    /*
     * To już na szybko - odczyt współrzędnych minimum i samego minimum
     */
    int i;
    for (i = 0; i < dim; i++) {
        printf("współrzędna %d = %f \n", i, v[i]);
    }
    printf("zakładane min. funkcji w tym ptk. =  %f \n", functionPointer(v, dim));

    /*
     *  Ponieważ jawnie tworzyliśmy *p, jawnie też musimy zrobić dealloc
     */
    freePsoParams(p);

    return (EXIT_SUCCESS);
}

