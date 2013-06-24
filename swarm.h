/* 
 * File:   swarm.h
 * Author: artur
 *
 * Created on 11 kwiecień 2013, 13:51
 */

#ifndef SWARM_H
#define	SWARM_H

#include "PSO.h"
#include "particle.h"

typedef struct _Swarm {
    double lastBestEval;
    PsoParams *psoParams;
    Particle **particles;
    double *swarmBestPosition;

} Swarm;

Swarm * createSwarm(PsoParams *p);

void freeSwarm(Swarm *s);

void moveSwarm(Swarm *s);

void checkSwarmLastBestPos(Swarm *s, Particle * p);


#endif	/* SWARM_H */

