#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include "../functions.h"

void decompressFile (char *compressedFileName, char *decompressedFileName) {
    FILE *compressedFile = fopen(compressedFileName, "r");
    FILE *decompressedFile = fopen(decompressedFileName, "w");

    if (compressedFile == NULL || decompressedFile == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    int bufferSize = 2048;
    char *buffer = malloc(bufferSize);
    char *word = malloc(MAX_WORD_LENGTH);
    char *tempWord = malloc(1);

    int index = 0;
    Word *dictionary = malloc (0 * sizeof(Word));
    int dictionarySize = 0;
    while (fscanf(compressedFile, "%s", word)) {
        dictionary = realloc(dictionary, (index + 1) * sizeof(Word));
        strcpy(dictionary[index++].word, word);
        if (fgetc(compressedFile) == '\n') break;
    }
    dictionarySize = index;

    while (fgets(buffer, bufferSize, compressedFile)) {
        int i = 0;
        while (buffer[i] == ' ') {
            fputc(' ', decompressedFile);
            i++;
        }
        word = strtok(buffer, " ");
        while (word != NULL) {
            tempWord = realloc(tempWord, strlen(word) + 1);
            strcpy(tempWord, word);
            if (wordToPut(&tempWord, dictionary, dictionarySize) == 1) {
                fputs(tempWord, decompressedFile);
            }
            else {
                fputs(word, decompressedFile);
            }
            if(word[strlen(word) - 1] != '\n')
                fputc(' ', decompressedFile);
            word = strtok(NULL, " ");
        }
    }

    int currentPos = ftell(decompressedFile);
    fflush(decompressedFile);
    ftruncate(fileno(decompressedFile), currentPos - 1);

    free(word);
    free(buffer);
    free(tempWord);
    free(dictionary);
    fclose(compressedFile);
    fclose(decompressedFile);
}

int main () {
    char *compressedFileName = "../compressed.txt";
    char *decompressedFileName = "../decompressed.txt";
    printf("\nDecompress File\n");
    printf("Press ENTER to cointinue...(To exit press ESC)\n");
    if (_getch() == 27) {
        printf("Ending...\n");
        system("pause");
        return 0;
    }
    printf("Continue...\nProcessing File...\n");
    decompressFile(compressedFileName, decompressedFileName);
    printf("Done.\n");

    system("pause");
    return 0;
}