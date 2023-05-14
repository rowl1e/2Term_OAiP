#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "get.h"

#define MAX_NAME_LENGTH 1024

int getint_min_max (int min, int max) {
    int integer;
    while (!scanf("%d", &integer) || integer < min || integer > max || getchar() != '\n') {
            printf("Try again: ");
            rewind(stdin);
    }
    return integer;
}

bool get_answer() {
    char answer[MAX_NAME_LENGTH];
    while (true) {
        fgets(answer, MAX_NAME_LENGTH, stdin);
        answer[strcspn(answer, "\n")] = 0;
        if (strncmp(answer, "yes", 2) == 0) {
            return true;
        } else if (strncmp(answer, "no", 2) == 0) {
            return false;
        } else {
            printf("Please enter 'yes' or 'no': ");
        }
    }
}