#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#include <stdio.h>
#include <math.h>

// Definition of lengths of L1 and L2
#define L1 500.0
#define L2 400.0
#define Base 100.0
#define X_len 10000
#define Y_len 10000

// Definition of the Parameters structure
typedef struct {
    double x;
    double y;
    double z;
    char name[10];
} Parameters;

// Declaration of CheckInRange function
int CheckInRange(int *yes, Parameters *pPosition, int *new_x, int *new_y, int *bd_x, int *bd_y);

// Declaration of InverseKinematics function
void InverseKinematics(Parameters *pPosition, double new_x, double new_y, double *l1_ang, double *l2_ang);

#endif // FUNCTION_H_INCLUDED
