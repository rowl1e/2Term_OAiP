#include <stdio.h>
#include <stdlib.h>
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

float getfloat () {
    float x;
    while (!scanf("%f", &x) || getchar() != '\n') {
        printf("Invalid input. Try again: ");
        rewind(stdin);
    }
    return x;
}

float getfloatMin (int min) {
    float x;
    while (!scanf("%f", &x) || x < min || getchar() != '\n') {
        printf("Invalid input. Try again: ");
        rewind(stdin);
    }
    return x;
}

char* get_str () {
    char* str;
    char c;
    int i = 0;
    str = malloc (1);
    while(i <= 1)
        while((c = getchar())!= EOF && c != '\n'){
            str = (char*) realloc (str, i + 1);
            str[i] = c;
            i++;
        }
    str[i] = '\0';
    return str;
}