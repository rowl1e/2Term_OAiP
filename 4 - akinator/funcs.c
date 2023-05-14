#include <stdlib.h>
#include <string.h>
#include "get.h"
#include "struct.h"
#include "funcs.h"

#define MAX_NAME_LENGTH 1024

Node* new_node(char* name, int index) {
    Node* node = malloc(sizeof(Node));
    if(node == NULL) {
        printf("Can't allocate memory\n");
        exit(1);
    }
    strncpy(node->name, name, MAX_NAME_LENGTH);
    node->index = index;
    node->yes = NULL;
    node->no = NULL;
    return node;
}

Node* create_new_tree () {
    Node* root = NULL;
    char str[MAX_NAME_LENGTH];
    printf("\nAdd first question: ");
    fgets(str, MAX_NAME_LENGTH, stdin);
    str[strcspn(str, "\n")] = 0;
    root = new_node(str, 1);

    printf("If yes: ");
    fgets(str, MAX_NAME_LENGTH, stdin);
    str[strcspn(str, "\n")] = 0;
    root->yes = new_node(str, 2);

    printf("If no: ");
    fgets(str, MAX_NAME_LENGTH, stdin);
    str[strcspn(str, "\n")] = 0;
    root->no = new_node(str, 3);
    return root;
}

void add_item(Node* current_node) {
    char new_item[MAX_NAME_LENGTH];
    char question[MAX_NAME_LENGTH];
    printf("What is the name of the game? ");
    fgets(new_item, MAX_NAME_LENGTH, stdin);
    new_item[strcspn(new_item, "\n")] = 0;
    printf("Write a question that distinguishes %s from %s: ", new_item, current_node->name);
    fgets(question, MAX_NAME_LENGTH, stdin);
    question[strcspn(question, "\n")] = 0;
    Node* new_question = new_node(question, current_node->index);
    Node* new_node_ = new_node(new_item, current_node->index * 2);
    Node* old_node_ = new_node(current_node->name, current_node->index * 2 + 1);
    new_question->yes = new_node_;
    new_question->no = old_node_;
    *current_node = *new_question;
}

void traverse_tree(Node* current_node, Stats* stats) {
    if (current_node->yes == NULL && current_node->no == NULL) {
        printf("I think it's %s. I guessed? ", current_node->name);
        if (get_answer()) {
            printf("Hooray! I guessed!\n");
            stats->games_won++;
        } else {
            printf("Oh no! I didn't guess.\n");
            printf("Do you want to add new object? ");
            if (get_answer()) {
                add_item(current_node);
            }
        }
        return;
    }

    printf("%s ", current_node->name);
    if (get_answer()) {
        traverse_tree(current_node->yes, stats);
    } else {
        traverse_tree(current_node->no, stats);
    }
}

Node* load_db(FILE* file, int index) {
    int current_index;
    char name[MAX_NAME_LENGTH];
    char line[MAX_NAME_LENGTH];
    fseek(file, 0, SEEK_SET);
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "[%d] %[^\n]s", &current_index, name);
        if (current_index == index) {
            Node* node = new_node(name, index);
            node->yes = load_db(file, index * 2);
            node->no = load_db(file, index * 2 + 1);
            return node;
        }
    }
    return NULL;
}

void save_db(FILE* file, Node* current_node) {
    if (current_node == NULL) return;
    fprintf(file, "[%d] %s\n", current_node->index, current_node->name);
    save_db(file, current_node->yes);
    save_db(file, current_node->no);
}

void print_possible_results(Node* current_node) {
    if (current_node == NULL) return;
    if (current_node->yes == NULL && current_node->no == NULL) {
        printf("  > %s\n", current_node->name);
    } else {
        print_possible_results(current_node->yes);
        print_possible_results(current_node->no);
    }
}

void save_stats(FILE* file, Stats* stats) {
    fprintf(file, "%d %d\n", stats->games_played, stats->games_won);
}

void load_stats(FILE* file, Stats* stats) {
    fscanf(file, "%d %d\n", &stats->games_played, &stats->games_won);
}

void print_stats(Stats* stats) {
    float value = 100.0 * stats->games_won / stats->games_played;
    printf("Games played: %d\n", stats->games_played);
    printf("Games won: %d\n", stats->games_won);
    printf("Win rate: %.2f%%\n", value);
}