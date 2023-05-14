#ifndef WORD_H
#define WORD_H

#define MAX_WORD_LENGTH 100

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
    int used;
} Word;

#endif //WORD_H