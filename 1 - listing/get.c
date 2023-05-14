#include <stdio.h>
#include "get.h"

int getintMin (int min) {
    int integer;
    while (!scanf("%d", &integer) || integer < min || getchar() != '\n') {
        printf("Invalid input. Try again: ");
        rewind(stdin);
    }
    return integer;
}

int getintMinMax (int min, int max) {
    int integer;
    while (!scanf("%d", &integer) || integer < min || integer > max || getchar() != '\n') {
        printf("Invalid input. Try again: ");
        rewind(stdin);
    }
    return integer;
}

float getfloatMin (int min) {
    float x;
    while (!scanf("%f", &x) || x < min || getchar() != '\n') {
        printf("Invalid input. Try again: ");
        rewind(stdin);
    }
    return x;
}

double getdoubleMin (int min) {
    double x;
    while (!scanf("%lf", &x) || x < min || getchar() != '\n') {
        printf("Invalid input. Try again: ");
        rewind(stdin);
    }
    return x;
}