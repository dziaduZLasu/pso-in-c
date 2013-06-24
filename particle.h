/* 
 * File:   particle.h
 * Author: artur
 *
 * Created on 10 kwiecień 2013, 19:13
 */

#ifndef PARTICLE_H
#define	PARTICLE_H

#include "PSO.h"

typedef struct _Particle {
    double lastBestEval;
    PsoParams *psoParams;
    double *currentPosition;
    double *acceleration;
    double *lastBestPosition;

} Particle;

Particle* createParticle(PsoParams *p);

void freeParticle(Particle *p);

void moveParticle(Particle *p, double* swarmLastBestPos);

int checkParticleLastBestPos(Particle *p);

#endif	/* PARTICLE_H */

