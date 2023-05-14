#include "get.h"
#include "struct.h"
#include "funcs.h"
#include <stdlib.h>

void menu (Node** root, Stats* stats) {
    int option;
    do {
        printf("Menu:"
               "\t1. Start Play\n"
               "\t2. Print List\n"
               "\t3. Print Stats\n"
               "\t4. Exit\n"
               "Option: ");
        option = getint_min_max(1, 4);
        switch (option) {
            case 1:
                stats->games_played++;
                printf("\nGuess the game and I'll try to guess it.\n");
                traverse_tree(*root, stats);
                break;
            case 2:
                printf("\nHere is a list of games I know:\n");
                print_possible_results(*root);
                break;
            case 3:
                printf("\nHere are your game statistics:\n");
                print_stats(stats);
                break;
        }
        if(option != 4) {
            printf("\nReturn to menu? ");
            if (!get_answer()) {
                break;
            }
        }
    } while (option != 4);
}

int main() {
    system("cls");
    char *filename = {"libr.txt"};
    char *stats_filename = {"stats.txt"};

    Node* root = NULL;
    Stats stats = {0};

    FILE* stats_file = fopen(stats_filename, "r");
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Can't open file.");
        root = create_new_tree();
        fclose(file);
    }
    else root = load_db(file, 1);

    if (stats_file != NULL) {
        load_stats(stats_file, &stats);
        fclose(stats_file);
    }
    load_stats(stats_file, &stats);

    menu(&root, &stats);


    file = fopen(filename, "w");
    stats_file = fopen(stats_filename, "w");
    save_db(file, root);
    save_stats(stats_file, &stats);
    fclose(file);
    fclose(stats_file);
    free(root);

    system("pause");
    return 0;
}