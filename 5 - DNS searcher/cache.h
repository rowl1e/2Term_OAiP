#ifndef CACHE_H
#define CACHE_H

#define MAX_CACHE_SIZE 3

typedef struct node {
    char *key;
    char *value;
    struct node *prev;
    struct node *next;
    struct node *next_in_bucket;
} Node;

typedef struct cache {
    int size;
    Node *head;
    Node *tail;
    Node *hash[MAX_CACHE_SIZE];
} Cache;

#endif //CACHE_H