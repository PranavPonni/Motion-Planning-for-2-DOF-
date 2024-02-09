#include "function.h"

int CheckInRange(int *yes, Parameters *pPosition, int *new_x, int *new_y, int *bd_x, int *bd_y) {
    // Calculate the maximum extensions of the arm
    double maxExtension = sqrt(pow(L1 + L2, 2) - pow(Base, 2));
    
    // Check if the object is within reachable x and y ranges
    if (pPosition->x < maxExtension || pPosition->x > X_len - maxExtension ||
        pPosition->y < maxExtension || pPosition->y > Y_len - maxExtension ||
        pPosition->z < 0 || pPosition->z > 900) {
        *yes = 0;
        return 0;
    }

    // Calculate the nearest black dot position
    int nearest_x = ((int)(pPosition->x / 1000)) * 1000;
    int nearest_y = ((int)(pPosition->y / 1000)) * 1000;

    // Calculate the difference between current position and nearest black dot
    *new_x = pPosition->x - nearest_x;
    *new_y = pPosition->y - nearest_y;

    // Calculate the distance from the origin
    double distanceFromOrigin = sqrt(pow(*new_x, 2) + pow(*new_y, 2) + pow(pPosition->z, 2));

    // Check if the object is within robot's reach
    if (distanceFromOrigin <= L1 + L2) {
        *yes = 1;
        *bd_x = nearest_x;
        *bd_y = nearest_y;
        return 1;
    } else {
        *yes = 0;
        return 0;
    }
}

void InverseKinematics(Parameters *pPosition, double new_x, double new_y, double *l1_ang, double *l2_ang) {

    double x = sqrt(pow(new_x, 2) + pow(new_y, 2));
    double y = pPosition->z;

    double r1 = atan2(new_y, new_x) * 180 / M_PI;
    double L3 = sqrt(pow(x, 2) + pow(y, 2));
    double a1 = atan2(y, x);
    double a2 = acos(((pow(L1, 2) + pow(L3, 2) - pow(L2, 2)) / (2 * L1 * L3)));
    double a3 = acos(((pow(L1, 2) + pow(L2, 2) - pow(L3, 2)) / (2 * L1 * L2)));

    double angle1 = (a1 + a2) * 180 / M_PI;
    double angle2 = a3 * 180 / M_PI - 180;

    printf("For the position (%.2lf, %.2lf, %.2lf) and the object '%s', the angles of the robot arms are: \n", pPosition->x, pPosition->y, pPosition->z, pPosition->name);
    printf("The mobile robot must be oriented at an angle %.2lf° from the x-axis.\n", r1);
    printf("Configuration 1:  L1 = %.2lf°, L2 = %.2lf°\n", angle1, angle2);
    *l1_ang = angle1;
    *l2_ang = angle2;

    angle1 = (a1 - a2) * 180 / M_PI;
    angle2 = -a3 * 180 / M_PI + 180;

    printf("Configuration 2: L1 = %.2lf°, L2 = %.2lf°\n\n", angle1, angle2);
}
