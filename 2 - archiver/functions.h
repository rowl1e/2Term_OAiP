#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include "word.h"

int getintMinMax (int min, int max);

void printAllWords (Word *words, int numWords);
void printDictionary (Word *dictionary, int numOfPairs);

int isWord(char *str);
void clear(char *word);
int compareWords(const void *a, const void *b);

void readWords(FILE *file, Word **words, int *numWords);
int findBestWords(Word *words, int numWords, int *shortestIndex, int *longestIndex);
void fillDictionary (Word *words, int numWords, Word **dictionary, int *dictionarySize);
void createDictionary (char *inputFileName, Word **dictionary, int *dictionarySize);

char *replaceSubstring(char *str, const char *oldSubstring, const char *newSubstring);
void wordReplace(char **word, int i, Word *dictionary, int dictionarySize);
int wordToPut (char **word, Word *dictionary, int dictionarySize);

#endif // FUNCTIONS_H