/* 
 * File:   PSO.h
 * Author: artur
 *
 * Created on 22 kwiecień 2013, 09:44
 */

#ifndef PSO_H
#define	PSO_H
#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct _PsoParams {
        int iterations;
        int particlesNum;
        int dim;
        double (*func)(double*, int);
        double fiSwarm;
        double fiParticles;
        double omegaVal;
        double psoMinPerVecElem;
        double psoMaxPerVecElem;
    } PsoParams;

    PsoParams* createPsoParams(int iterations,
            int particlesNum,
            int dim,
            double (*func)(double*, int),
            double fiSwarm,
            double fiParticles,
            double omegaVal,
            double psoMinPerVecElem,
            double psoMaxPerVecElem);

    void freePsoParams(PsoParams *p);

    /*
     * Właściwa funkcja optymalizacyjna, zwarca najlepszy wektor po n iteracjach
     */
    double* PSO(PsoParams *p);

#ifdef	__cplusplus
}
#endif

#endif	/* PSO_H */

