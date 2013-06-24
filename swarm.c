#include "particle.h"
#include "swarm.h"
#include "PSO.h"
#include <stdio.h>
#include <stdlib.h>

Swarm * createSwarm(PsoParams *p) {

    Swarm *s = (Swarm*) malloc(sizeof (Swarm));
    if (s != NULL) {
        s->psoParams = p;
        s->swarmBestPosition = (double*) malloc(sizeof (double) * p->dim);
        s->particles = (Particle**) malloc(sizeof (Particle*) * p->particlesNum);
        int i;
        for (i = 0; i < p->particlesNum; i++) {
            s->particles[i] = createParticle(p);
            if (i == 0) {
                /*
                 * memmove() bo chcę skopiować tablicę a nie usawić drugi wskaźnik do niej
                 */
                memmove(s->swarmBestPosition, s->particles[i]->currentPosition, p->dim * sizeof (double));
            }
        }
        /*
         * obliczam watość funkcji żeby potem nie wykonywać tego kosztownego obliczenia za każdym razem
         */
        s->lastBestEval = p->func(s->swarmBestPosition, p->dim);
    }
    return s;

}

void freeSwarm(Swarm * s) {
    int i;
    /*
     * dla każdej cząstki w roju
     */
    for (i = 0; i < s->psoParams->particlesNum; i++) {
        freeParticle(s->particles[i]);
    }
    free(s->particles);
    free(s);
}

void moveSwarm(Swarm * s) {

    int i;
    /*
     * dla każdej cząstki w roju
     */
    for (i = 0; i < s->psoParams->particlesNum; i++) {
        moveParticle(s->particles[i], s->swarmBestPosition);

        if (checkParticleLastBestPos(s->particles[i]) == 1) {
            checkSwarmLastBestPos(s, s->particles[i]);
        }
    }
}

void checkSwarmLastBestPos(Swarm *s, Particle * p) {
    if (p->lastBestEval < s->lastBestEval) {
        s->lastBestEval = p->lastBestEval;
        /*
         * memmove() bo chcę skopiować tablicę a nie usawić drugi wskaźnik do niej
         */
        memmove(s->swarmBestPosition, p->lastBestPosition, s->psoParams->dim * sizeof (double));
    }
}


