#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include "struct.h"

Node* new_node(char* name, int index);

Node* create_new_tree ();

void add_item(Node* current_node);

void traverse_tree(Node* current_node, Stats* stats);
Node* load_db(FILE* file, int index);
void save_db(FILE* file, Node* current_node);

void print_possible_results(Node* current_node);

void save_stats(FILE* file, Stats* stats);
void load_stats(FILE* file, Stats* stats);
void print_stats(Stats* stats);

#endif //FUNCS_H