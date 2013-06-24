/* 
 * File:   function.h
 * Author: artur
 *
 * Created on 10 kwiecień 2013, 21:00
 */

#ifndef FUNCTION_H
#define	FUNCTION_H
#define TWO_T_PI 2.0 * 3.14159265358979323846264338327
#define PI 3.14159265358979323846264338327
#define RASTR_A  10.0
#define MICH_M  10.0

double rastrigin(double params[], int dim);

double michalewicz(double params[], int dim);

double parabol(double params[], int dim);

double linear(double params[], int dim);

#endif	/* FUNCTION_H */

