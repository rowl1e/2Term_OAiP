#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>
#include "cache.h"

int getint_min_max (int min, int max);
char* get_str ();

Cache *init_cache();
void free_cache(Cache *cache);

int hash(char *key);
void move_to_head(Cache *cache, Node *node);
void remove_tail(Cache *cache);
void put(Cache *cache, char *key, char *value);
char *get(Cache *cache, char *key);

bool is_valid_ip(char* ip);
bool is_valid_domain(char *domain);
int entry_exists(char *domain, char *type);

char *search_file(char *key);
bool search_domains_func(char *ip);
void search_domains();

void add_entry();

char *search_ip(Cache *cache, char *domain_name, char *original_domain_name, int print_miss);
void search(Cache *cache);
void print_cache(Cache *cache);

#endif //FUNCTIONS_H