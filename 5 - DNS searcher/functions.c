#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "functions.h"

#define MAX_LENGTH 256

int getint_min_max (int min, int max) {
    int integer;
    while (!scanf("%d", &integer) || integer < min || integer > max || getchar() != '\n') {
        printf("Try again: ");
        rewind(stdin);
    }
    return integer;
}

char* get_str () {
    char* str;
    char c;
    int i = 0;
    str = (char *) malloc (1);
    while(i <= 1)
        while((c = getchar())!= EOF && c != '\n'){
            str = (char*) realloc (str, i + 1);
            str[i] = c;
            i++;
        }
    str[i] = '\0';
    return str;
}

Cache *init_cache() {
    Cache *cache = (Cache *)malloc(sizeof(Cache));
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;
    memset(cache->hash, 0, sizeof(cache->hash));
    return cache;
}

void free_cache(Cache *cache) {
    Node *current = cache->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
    free(cache);
}

int hash(char *key) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++))
        hash = ((hash << 5) + hash) + c;

    return hash % MAX_CACHE_SIZE;
}

void move_to_head(Cache *cache, Node *node) {
    if (node == cache->head) {
        return;
    }
    if (node == cache->tail) {
        cache->tail = node->prev;
        cache->tail->next = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    node->prev = NULL;
    node->next = cache->head;
    cache->head->prev = node;
    cache->head = node;
}

void remove_tail(Cache *cache) {
    Node *node = cache->tail;
    int index = hash(node->key);
    Node *prev = NULL;
    Node *current = cache->hash[index];
    while (current != NULL && strcmp(current->key, node->key) != 0) {
        prev = current;
        current = current->next_in_bucket;
    }
    if (current != NULL) {
        if (prev == NULL) {
            cache->hash[index] = current->next_in_bucket;
        } else {
            prev->next_in_bucket = current->next_in_bucket;
        }
        cache->size--;
        if (cache->size == 0) {
            cache->head = NULL;
            cache->tail = NULL;
        } else {
            cache->tail = node->prev;
            cache->tail->next = NULL;
        }
        free(node);
    }
}

void put(Cache *cache, char *key, char *value) {
    int index = hash(key);
    Node *prev = NULL;
    Node *current = cache->hash[index];
    while (current != NULL && strcmp(current->key, key) != 0) {
        prev = current;
        current = current->next_in_bucket;
    }
    if (current != NULL) {
        free(current->value);
        current->value = strdup(value);
        move_to_head(cache, current);
        return;
    }
    if (cache->size == MAX_CACHE_SIZE) {
        remove_tail(cache);
    }
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = strdup(key);
    node->value = strdup(value);
    node->prev = NULL;
    node->next = cache->head;
    node->next_in_bucket = NULL;
    if (cache->head != NULL) {
        cache->head->prev = node;
    }
    cache->head = node;
    if (cache->tail == NULL) {
        cache->tail = node;
    }
    if (prev == NULL) {
        cache->hash[index] = node;
    } else {
        prev->next_in_bucket = node;
    }
    cache->size++;
}

char *get(Cache *cache, char *key) {
    int index = hash(key);
    Node *current = cache->hash[index];
    while (current != NULL && strcmp(current->key, key) != 0) {
        current = current->next_in_bucket;
    }
    if (current != NULL) {
        move_to_head(cache, current);
        return current->value;
    }
    return NULL;
}

bool is_valid_ip(char* ip) {
    int num, dots = 0;
    char* copy = strdup(ip);
    char* ptr = strtok(copy, ".");
    
    if (ptr == NULL) {
        free(copy);
        return false; 
    }
    while (ptr) {
        for (int i = 0; i < strlen(ptr); i++) {
            if (!isdigit(ptr[i])) {
                free(copy);
                return false; 
            }
        }
        num = atoi(ptr);
        // if (num >= 0 && num <= MAX_LENGTH) {
        if (num >= 0 && num <= 255) {
            ptr=strtok(NULL, ".");
            if (ptr != NULL)
                dots++; 
        } else {
            free(copy);
            return false; 
        }
    }
    free(copy);
    
    if (dots != 3) return false; 
    return true; 
}

bool is_valid_domain(char *domain) {
    if (strlen(domain) > MAX_LENGTH) return false;

    char *tld = strrchr(domain, '.');
    if (tld == NULL) return false;
    tld++;

    for (int i = 0; i < strlen(tld); i++) {
        if (isdigit(tld[i])) return false;
    }

    char *copy = strdup(domain);
    char *saveptr;
    char *label = strtok_r(copy, ".", &saveptr);
    while (label) {
        if (strlen(label) == 0) {
            free(copy);
            return false;
        }
        if (!isalnum(label[0]) || !isalnum(label[strlen(label)-1])) {
            free(copy);
            return false;
        }

        for (int i = 0; i < strlen(label); i++) {
            if (!isalnum(label[i]) && label[i] != '-') {
                free(copy);
                return false;
            }
        }

        bool has_letter = false;
        for (int i = 0; i < strlen(label); i++) {
            if (isalpha(label[i])) {
                has_letter = true;
                break;
            }
        }
        if (!has_letter) {
            free(copy);
            return false;
        }

        label = strtok_r(NULL, ".", &saveptr);
    }

    free(copy);
    return true;
}

int entry_exists(char *domain, char *type) {
    FILE *file = fopen("dns.txt", "r");
    char file_domain[MAX_LENGTH], file_type[MAX_LENGTH];

    while (fscanf(file, "%s %*s %s %*s", file_domain, file_type) != EOF) {
        if (strcmp(file_domain, domain) == 0 && strcmp(file_type, type) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

char *search_file(char *key) {
    FILE *file = fopen("dns.txt", "r");
    char domain[MAX_LENGTH], type[MAX_LENGTH], value[MAX_LENGTH];
    char *result = NULL;

    while (fscanf(file, "%s %*s %s %s", domain, type, value) != EOF) {
        if (strcmp(type, "A") == 0 && strcmp(domain, key) == 0) {
            result = strdup(value);
            break;
        }
    }

    fclose(file);
    return result;
}

bool search_domains_func(char *ip) {
    if (!is_valid_ip(ip)) {
        printf("Invalid IP address\n");
        return false;
    }

    FILE *file = fopen("dns.txt", "r");
    char domain[MAX_LENGTH], type[MAX_LENGTH], value[MAX_LENGTH];
    bool found = false;

    while (fscanf(file, "%s %*s %s %s", domain, type, value) != EOF) {
        if (strcmp(type, "A") == 0 && strcmp(value, ip) == 0) {
            printf("  %s\n", domain);
            found = true;
        } else if (strcmp(type, "CNAME") == 0) {
            char *ip2 = search_file(value);

            if (ip2 != NULL && strcmp(ip2, ip) == 0) {
                printf("  %s\n", domain);
                found = true;
            }
        }
    }

    fclose(file);
    return found;
}

void search_domains() {
    printf("Enter IP: ");
    char *input = get_str();
    bool found = search_domains_func(input);
    if (!found) {
        printf("No domains found for the given IP address\n");
    }
}

void add_entry() {
    FILE *file = fopen("dns.txt", "a");
    char domain[MAX_LENGTH], type[MAX_LENGTH], value[MAX_LENGTH];

    printf("Enter domain: ");
    scanf("%s", domain);

    if (!is_valid_domain(domain)) {
        printf("Invalid domain\n");
        return;
    }

    if (entry_exists(domain, "A") || entry_exists(domain, "CNAME")) {
        printf("Entry already exists\n");
        return;
    }

    printf("Enter value: ");
    scanf("%s", value);

    if (is_valid_ip(value)) {
        printf("Defined as an ip\n");
        strcpy(type, "A");
    } else if (is_valid_domain(value)) {
        printf("Defined as a domain\n");
        strcpy(type, "CNAME");
    } else {
        printf("Invalid value\n");
        return;
    }

    fprintf(file, "%s IN %s %s\n", domain, type, value);
    fclose(file);
}

char *search_ip(Cache *cache, char *domain_name, char *original_domain_name, int print_miss) {
    char *ip_address = get(cache, original_domain_name);
    if (ip_address != NULL) {
        printf("HIT: %s\n", ip_address);
        return ip_address;
    } else {
        if (print_miss) {
            printf("MISS\n");
        }
        FILE *file = fopen("dns.txt", "r");
        if (file == NULL) {
            printf("Error opening file\n");
            return NULL;
        }
        char domain[MAX_LENGTH], type[MAX_LENGTH], value[MAX_LENGTH];
        while (fscanf(file, "%s %*s %s %s", domain, type, value) != EOF) {
            if (strcmp(domain, domain_name) == 0) {
                if (strcmp(type, "A") == 0) {
                    ip_address = strdup(value);
                    put(cache, original_domain_name, ip_address);
                    fclose(file);
                    return ip_address;
                } else if (strcmp(type, "CNAME") == 0) {
                    fclose(file);
                    return search_ip(cache, value, original_domain_name, 0);
                }
            }
        }
        fclose(file);
        return NULL;
    }
}

void search(Cache *cache) {
    char domain_name[MAX_LENGTH];
    printf("Enter domain name: ");
    scanf("%s", domain_name);
    char *ip_address = search_ip(cache, domain_name, domain_name, 1);
    if (ip_address != NULL) {
        printf("IP address: %s\n", ip_address);
    } else {
        printf("IP address not found\n");
    }
}

void print_cache(Cache *cache) {
    printf("#===============================#\n");
    printf("Cache:\n");
    Node *node = cache->head;
    while (node != NULL) {
        printf("<%s, %s>\n", node->key, node->value);
        node = node->next;
    }
    printf("#===============================#\n");
}