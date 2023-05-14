#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "get.h"
#include "tasks.h"

int menu (monitor_t** monitors, int* n) {
    void (*tasks[])(monitor_t**, int*) = {addMonitors, deletingMonitor, sortByTwo, printMonitors};
    while (1) {
        printf("Menu: "
               "\t1. Add a monitor\n"
               "\t2. Delete a monitor\n"
               "\t3. Sort monitors by two options\n"
               "\t4. Print monitors\n"
               "\t5. Exit\n");
        int choice = getintMinMax(1, 5);
        if (choice == 5){
            printf("The program has ended.\n");   
            system("pause");
            exit(1);
        }
        else {
            tasks[choice - 1](monitors, n);
            printf("\n");
        }
    }
}

int main () {
    monitor_t* monitors;
    printf("List of monitors is blank, how much you want to add?\n");
    int n = 0;
    while(n == 0){
        n = getintMin(0);
        if (n == 0) {
            printf("\nYou have to add at least 1 monitor. ");
            printf("Press Esc if you want exit(Enter if continue).\n");
            if(_getch() == 27) {
                printf("Ending...\n");
                break;
            }
            rewind(stdin);
        }
        printf("Continue...\n");
    }
    if (n > 0){
        arrayCreation(&monitors, &n);
        addMonitors1st(&monitors, &n);
        menu(&monitors, &n);
        free(monitors);
    }
    system("pause");
    return 0;
}