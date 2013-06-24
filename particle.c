#include "particle.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * PRIVATE
 */

double randBeet(double min, double max) {
    double random = ((double) rand()) / (double) RAND_MAX;
    random = min + (random * (max - min));
    return random;
}

/*
 * PUBLIC
 */

Particle* createParticle(PsoParams *p) {

    Particle* psoParticle = (Particle*) malloc(sizeof (Particle));
    if (psoParticle != NULL) {
        double negDiff = -1 * (p->psoMaxPerVecElem - p->psoMinPerVecElem);
        double posDiff = fabs(negDiff);
        srand((unsigned) time(NULL));
        psoParticle->psoParams = p;
        psoParticle->currentPosition = (double*) malloc(sizeof (double) * p->dim);
        psoParticle->acceleration = (double*) malloc(sizeof (double) * p->dim);
        psoParticle->lastBestPosition = (double*) malloc(sizeof (double) * p->dim);
        int i;
        for (i = 0; i < p->dim; i++) {

            /*
             * Pozycja : Wektor pozycji - rozmiar zależny od wymiarowości zadania; 
             * Inicjalizowany liczbami pseudolosowymi o rozkładzie jednorodnym od zadanej wartości minimalnej do maksymalnej. 
             * Jednakże, jeżeli coś wiemy na temat optymalizowanego zadania możemy przyjąć liczby bliskie zakładanemu optimum. 
             */
            psoParticle->currentPosition[i] = randBeet(p->psoMinPerVecElem, p->psoMaxPerVecElem);

            /*
             * Przyśpieszenie: Wektor przyśpieszenia -rozmiar zależny od wymiarowości zadania; 
             * Inicjalizowany liczbami pseudolosowymi o rozkładzie jednorodnym od ujemnej różnicy zadanej wartości maksymalnej i minimalnej, 
             * do dodatniej wartości takiej różnicy . 
             * Każdy element wektoru odnosi się do prędkości dla wymiaru n, gdzie n jest numerem elementu w wektorze. 
             */

            psoParticle->acceleration[i] = randBeet(negDiff, posDiff);

            /*
             * Najlepsza pozycja: Wektor najlepszej pozycji - rozmiar zależny od wymiarowości zadania; 
             * Inicjalizowany wektorem pozycji przy tworzeniu cząsteczki. 
             * Jego wartość zostaje zmieniona, gdy cząsteczka znalazła lepiej oceniane położenie. 
             * Wektor ten staje się później jednym z dwóch atraktorów cząsteczki.
             */
            psoParticle->lastBestPosition[i] = psoParticle->currentPosition[i];
        }
        /*
         * obliczam watość funkcji żeby potem nie wykonywać tego kosztownego obliczenia za każdym razem
         */
        psoParticle->lastBestEval = p->func(psoParticle->currentPosition, p->dim);

    }
    return psoParticle;
}

void moveParticle(Particle *p, double* swarmLastBestPos) {

    int i;
    /*
     * obliczam nowe przyspieszenia
     */
    for (i = 0; i < p->psoParams->dim; i++) {
        p->acceleration[i] = p->psoParams->omegaVal * p->acceleration[i]
                + p->psoParams->fiParticles * randBeet(0.0, 1.0)
                * (p->lastBestPosition[i] - p->currentPosition[i])
                + p->psoParams->fiSwarm * randBeet(0.0, 1.0)
                + (swarmLastBestPos[i] - p->lastBestPosition[i]);

        /*
         * przestawiam i-tą składową wektora pozycji
         */
        p->currentPosition[i] += p->acceleration[i];
    }
}

int checkParticleLastBestPos(Particle *p) {

    int retVal = 0;
    double newPosEval = p->psoParams->func(p->currentPosition, p->psoParams->dim);

    if (newPosEval < p->lastBestEval) {
        p->lastBestEval = newPosEval;
        /*
         * memmove() bo chcę skopiować tablicę a nie usawić drugi wskaźnik do niej
         */
        memmove(p->lastBestPosition, p->currentPosition, p->psoParams->dim * sizeof (double));
        /*
         * info o tym że nastąpiła zmiana
         */
        retVal = 1;
    }
    return retVal;
}

void freeParticle(Particle *p) {
    free(p->acceleration);
    free(p->lastBestPosition);
    free(p->currentPosition);
    free(p);
}

