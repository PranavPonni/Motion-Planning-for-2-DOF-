#include "function.h"
#define MAX_CSV 7
int main(void) {
    int yes = 0;
    int new_x = 0, new_y = 0;
    int bd_x = 1000, bd_y = 1000;
    int robot_x = 1000, robot_y = 1000;
    double robot_ang = 0, l1_ang = 0, l2_ang = 0;
    
    FILE *fp = fopen("data.csv", "r");
    if (fp == NULL) {
        printf("Cannot open file\n");
        return -1;
    }

    int numPositions = 0;
    Parameters Position[MAX_CSV];

    for (int i = 0; i < MAX_CSV && fscanf(fp, "%lf,%lf,%lf,%s", &Position[i].x, &Position[i].y, &Position[i].z, Position[i].name) == 4; i++) {
        numPositions++;
    }
    fclose(fp);

    FILE *fp2 = fopen("robotmove.csv", "w+");
    if (fp2 == NULL) {
        printf("Cannot create movements.csv\n");
        return -1;
    }
    fputs("X,Y,Robot_Angle,L1_Angle,L2_Angle,Action\n", fp2);

    char action1[] = "Initial";
    char action2[] = "Rotate_Base";
    char action3[] = "Move_X";
    char action4[] = "Move_Y";
    char action5[] = "Collect";
    char action6[] = "Pick up";

    fprintf(fp2, "%d,%d,%.2lf,%.2lf,%.2lf,%s\n", robot_x, robot_y, robot_ang, l1_ang, l2_ang, action1);

        int check;
    for (int i = 0; i < numPositions; i++) {
        check = CheckInRange(&yes, &Position[i], &new_x, &new_y, &bd_x, &bd_y);
        if (yes == 1) {
            if (bd_x > robot_x) {
                robot_ang = 0;
            } else if (bd_x < robot_x) {
                robot_ang = 180;
            }
            fprintf(fp2, "%d,%d,%.2lf,%.2lf,%.2lf,%s\n", robot_x, robot_y, robot_ang, l1_ang, l2_ang, action2);
            robot_x = bd_x;
            fprintf(fp2, "%d,%d,%.2lf,%.2lf,%.2lf,%s\n", robot_x, robot_y, robot_ang, l1_ang, l2_ang, action3);

            if (bd_y > robot_y) {
                robot_ang = 90;
            } else if (bd_y < robot_y) {
                robot_ang = -90;
            }
            fprintf(fp2, "%d,%d,%.2lf,%.2lf,%.2lf,%s\n", robot_x, robot_y, robot_ang, l1_ang, l2_ang, action2);
            robot_y = bd_y;
            fprintf(fp2, "%d,%d,%.2lf,%.2lf,%.2lf,%s\n", robot_x, robot_y, robot_ang, l1_ang, l2_ang, action4);

            robot_ang = atan2(new_y, new_x) * 180 / M_PI;
            InverseKinematics(&Position[i], new_x, new_y, &l1_ang, &l2_ang);
            fprintf(fp2, "%d,%d,%.2lf,%.2lf,%.2lf,%s\n", robot_x, robot_y, robot_ang, l1_ang, l2_ang, action5);
            fprintf(fp2, "%s %s\n", Position[i].name, action6);
        } else {
            printf("\n(%.2lf, %.2lf, %.2lf), object: %s\n", Position[i].x, Position[i].y, Position[i].z, Position[i].name);
            printf("In these coordinates, the object cannot be reached by the robot arm. It is out of range\n\n");
        }
    }

    bd_x = 1000, bd_y = 1000;
    if (bd_x > robot_x) {
        robot_ang = 0;
    } else if (bd_x < robot_x) {
        robot_ang = 180;
    }
    fprintf(fp2, "%d,%d,%.2lf,%.2lf,%.2lf,%s\n", robot_x, robot_y, robot_ang, l1_ang, l2_ang, action2);
    robot_x = bd_x;
    fprintf(fp2, "%d,%d,%.2lf,%.2lf,%.2lf,%s\n", robot_x, robot_y, robot_ang, l1_ang, l2_ang, action3);

    if (bd_y > robot_y) {
        robot_ang = 90;
    } else if (bd_y < robot_y) {
        robot_ang = -90;
    }
    fprintf(fp2, "%d,%d,%.2lf,%.2lf,%.2lf,%s\n", robot_x, robot_y, robot_ang, l1_ang, l2_ang, action2);
    robot_y = bd_y;
    fprintf(fp2, "%d,%d,%.2lf,%.2lf,%.2lf,%s\n", robot_x, robot_y, robot_ang, l1_ang, l2_ang, action4);

    robot_ang = 0, l1_ang = 0, l2_ang = 0;
    fprintf(fp2, "%d,%d,%.2lf,%.2lf,%.2lf,%s\n", robot_x, robot_y, robot_ang, l1_ang, l2_ang, action2);
    fputs("Returned home", fp2);

    fclose(fp2);
    return 0;
}
