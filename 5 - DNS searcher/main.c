#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main() {
    Cache *cache = init_cache();
    int choice;

    while (1) {
        printf("1. Search by domain name\n"
               "2. Search domains by IP\n"
               "3. Add new\n"
               "4. Exit\n"
               "Enter choice: ");
        choice = getint_min_max(1, 4);

        if (choice == 1) {
            search(cache);
            print_cache(cache);
        } else if (choice == 2) {
            search_domains();
        } else if (choice == 3) {
            add_entry();
        } else if (choice == 4) {
            break;
        }
        system("pause");
        printf("\n");
    }
    
    free_cache(cache);
    return 0;
}