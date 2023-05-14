#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include "../functions.h"

void compressFile(char *inputFileName, char *compressedFileName) {
    Word *dictionary;
    int dictionarySize;
    createDictionary (inputFileName, &dictionary, &dictionarySize);

    FILE *inputFile = fopen(inputFileName, "r");
    FILE *compressedFile = fopen(compressedFileName, "w");

    if (inputFile == NULL || compressedFile == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    for(int i = 0; i < dictionarySize; i++) {
        fputs(dictionary[i].word, compressedFile);
        if (i < dictionarySize - 1) fputc(' ', compressedFile);
        else fputc('\n', compressedFile);
    }

    int bufferSize = 1024;
    char *buffer = malloc(bufferSize);
    char *word = malloc(MAX_WORD_LENGTH);
    char *tempWord = malloc(1);

    while (fgets(buffer, bufferSize, inputFile)) {
        int i = 0;
        while (buffer[i] == ' ') {
            fputc(' ', compressedFile);
            i++;
        }
        word = strtok(buffer, " ");
        while (word != NULL) {
            tempWord = realloc(tempWord, strlen(word) + 1);
            strcpy(tempWord, word);
            if (wordToPut(&tempWord, dictionary, dictionarySize) == 1) {
                fputs(tempWord, compressedFile);
            }
            else {
                fputs(word, compressedFile);
            }
            if(word[strlen(word) - 1] != '\n'){
                fputc(' ', compressedFile);
            }
            word = strtok(NULL, " ");
        }
    }

    int currentPos = ftell(compressedFile);
    fflush(compressedFile);
    ftruncate(fileno(compressedFile), currentPos - 1);

    free(word);
    free(buffer);
    free(tempWord);
    free(dictionary);
    fclose(inputFile);
    fclose(compressedFile);
}

int main () {
    char *inputFileName = "../bookpart.txt";
    char *compressedFileName = "../compressed.txt";

    printf("\nCompress File\n");
    printf("Press ENTER to cointinue...(To exit press ESC)\n");
    if (_getch() == 27) {
        printf("Ending...\n");
        system("pause");
        return 0;
    }
    printf("Continue...\nProcessing File...\n");
    compressFile(inputFileName, compressedFileName);
    printf("Done.\n");

    system("pause");
    return 0;
}