#ifndef STRUCT_H
#define STRUCT_H

#define MAX_NAME_LENGTH 1024

typedef struct node {
    char name[MAX_NAME_LENGTH];
    int index;
    struct node* yes;
    struct node* no;
} Node;

typedef struct {
    int games_played;
    int games_won;
} Stats;

#endif //STRUCT_H