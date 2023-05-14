#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "functions.h"

int getintMinMax (int min, int max) {
    int integer;
    while (!scanf("%d", &integer) || integer < min || integer > max || getchar() != '\n') {
            printf("Invalid input. Try again:\n");
            rewind(stdin);
    }
    return integer;
}

void printAllWords (Word *words, int numWords) {
    printf("==================================================================\n");
    for(int i = 0; i < numWords; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    printf("==================================================================\n");
}

void printDictionary (Word *dictionary, int numOfPairs) {
    if(numOfPairs % 2 != 0 || numOfPairs == 0) {
        printf("Something went wrong.\nEnding the program...\n");
        exit(0);
    }
    printf("==================================================================\n");
    int i = 0, j = 1;
    while (i < numOfPairs - 1 && j < numOfPairs) {
        printf("%s %s\n", dictionary[i].word, dictionary[j].word);
        i += 2;
        j += 2;
    }
    printf("==================================================================\n");
}

int isWord(char *word) {
    for (int i = 0; word[i]; i++) {
        if (!isalpha(word[i]) && word[i] != '\'') return 0;
    }
    return 1;
}

void clear(char *word) {
    int j = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        if (isalpha(word[i]) || word[i] == '\'') {
            word[j++] = word[i];
        }
    }
    word[j] = '\0';
}

int compareWords(const void *a, const void *b) {
    Word *wordA = (Word *)a;
    Word *wordB = (Word *)b;
    if (strlen(wordB->word) != strlen(wordA->word)) return (int)strlen(wordB->word) - (int)strlen(wordA->word);
    if (wordA->count > wordB->count) return -1;
    if (wordA->count < wordB->count) return 1;
    if (wordA->count == wordB->count) return 0;
}

void readWords(FILE *file, Word **words, int *numWords) {
    char *buffer = malloc(1);
    *words = malloc(0 * sizeof(Word));
    while (fscanf(file, "%s", buffer) != EOF) {
        clear(buffer);
        int found = 0;
        for (int i = 0; i < *numWords; i++) {
            if (strcmp((*words)[i].word, buffer) == 0) {
                (*words)[i].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            ++(*numWords);
            *words = realloc(*words, (*numWords + 1) * sizeof(Word));
            strcpy((*words)[*numWords - 1].word, buffer);
            (*words)[*numWords - 1].count = 1;
            (*words)[*numWords - 1].used = 0;
        }
    }
}

int findBestWords(Word *words, int numWords, int *shortestIndex, int *longestIndex) {
    int max = 0;
    for (int i = 0; i < numWords; i++) {
        if (words[i].used) continue;
        for (int j = numWords - 1; j > i; j--) {
            if (words[j].used) continue;
            int len1 = strlen(words[i].word);
            int len2 = strlen(words[j].word);
            int val = len1 * words[i].count + len2 * words[j].count - (len1 * words[j].count + len2 * words[i].count + len1 + len2 + 2);
            if (val > max) {
                max = val;
                *longestIndex = i;
                *shortestIndex = j;
            }
        }
    }
    if(max != 0) return 0;
    return 1;
}

void fillDictionary (Word *words, int numWords, Word **dictionary, int *dictionarySize) {
    int longestIndex = 0;
    int shortestIndex = numWords - 1;

    int i = 0, j = 1;
    int tempL = -1;
    int tempS = -1;
    while (!findBestWords(words, numWords, &shortestIndex, &longestIndex)) {
        if(tempL != longestIndex && tempS != shortestIndex) {
            words[longestIndex].used = 1;
            words[shortestIndex].used = 1;
            *dictionary = realloc (*dictionary, (i + 2) * sizeof(Word));
            (*dictionary)[i] = words[longestIndex];
            (*dictionary)[j] = words[shortestIndex];
            tempL = longestIndex;
            tempS = shortestIndex;
            i += 2;
            j += 2;
        }
    }
    *dictionarySize = i;
}

void createDictionary (char *inputFileName, Word **dictionary, int *dictionarySize) {
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    Word *words;
    int numWords = 0;
    readWords(inputFile, &words, &numWords);
    qsort(words, numWords, sizeof(Word), compareWords);

    *dictionary = malloc (0 * sizeof(Word*));
    *dictionarySize = 0;
    fillDictionary(words, numWords, dictionary, dictionarySize);
    
    fclose(inputFile);
}

char *replaceSubstring(char *str, const char *oldSubstring, const char *newSubstring) {
    char *result;
    int i, count = 0;
    int newSubstringLength = strlen(newSubstring);
    int oldSubstringLength = strlen(oldSubstring);

    for (i = 0; str[i] != '\0'; i++) {
        if (strstr(&str[i], oldSubstring) == &str[i]) {
            count++;
            i += oldSubstringLength - 1;
        }
    }

    result = malloc(i + count * (newSubstringLength - oldSubstringLength) + 1);

    i = 0;
    while (*str) {
        if (strstr(str, oldSubstring) == str) {
            strcpy(&result[i], newSubstring);
            i += newSubstringLength;
            str += oldSubstringLength;
        } else {
            result[i++] = *str++;
        }
    }

    result[i] = '\0';
    return result;
}

void wordReplace(char **word, int i, Word *dictionary, int dictionarySize) {
    char *newWord = NULL;
    size_t newWordLength = 0;
    if (i % 2 == 0 && i + 1 < dictionarySize) {
        newWordLength = strlen(dictionary[i + 1].word);
        newWord = realloc(*word, (newWordLength + i) * sizeof(char));
        if (newWord != NULL) {
            *word = newWord;
            strncpy(*word, dictionary[i + 1].word, newWordLength);
            (*word)[newWordLength] = '\0';
        } else {
            printf("Can't allocate memory.\n");
            exit(1);
        }
    } else if (i % 2 == 1 && i - 1 >= 0) {
        newWordLength = strlen(dictionary[i - 1].word);
        newWord = realloc(*word, (newWordLength + 1) * sizeof(char));
        if (newWord != NULL) {
            *word = newWord;
            strncpy(*word, dictionary[i - 1].word, newWordLength);
            (*word)[newWordLength] = '\0';
        } else {
            printf("Can't allocate memory.\n");
            exit(2);
        }
    }
}

int wordToPut (char **word, Word *dictionary, int dictionarySize) {
    int found = 0;
    char *temp1 = malloc(strlen(*word) + 1);
    char *temp2 = malloc(1);
    char *temp3 = malloc(strlen(*word) + 1);
    strcpy(temp1, *word);
    strcpy(temp3, *word);
    clear(temp1);

    for (int i = 0; i < dictionarySize; i++) {
        if (strcmp(temp1, dictionary[i].word) == 0) {
            if (!isWord(*word)) {
                temp2 = realloc(temp2, strlen(temp1) + 1);
                strcpy(temp2, temp1);
                wordReplace(&temp2, i, dictionary, dictionarySize);
                temp3 = replaceSubstring(temp3, temp1, temp2);
                *word = realloc(*word, strlen(temp3) + 1);
                strcpy(*word, temp3);
            }
            else if (isWord(*word)){
                wordReplace(&(*word), i, dictionary, dictionarySize);
            }
            found = 1;
            break;
        }
    }
    
    free(temp1);
    free(temp2);
    free(temp3);
    return found;
}