#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 50
#define MAX_WORDS 1000

typedef struct {
    char word[MAX_WORD_LENGTH];
    int frecuency;
} WordFrecuency;

char *to_lower_case(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }

    return str;
}

int main(void) {
    FILE *file = fopen("words.txt", "r");
    if (file == NULL) {
        perror("fopen");
        exit(1);
    }

    char buffer[MAX_WORD_LENGTH];
    WordFrecuency list[MAX_WORDS];
    int word_count = 0;
    while (fscanf(file, "%s", buffer) != EOF) {
        to_lower_case(buffer);
        int found = 0;

        for (int i = 0; i < word_count; i++) {
            if (strcmp(list[i].word, buffer) == 0) {
                list[i].frecuency++;
                found = 1;
                break;
            }
        }

        if (!found && word_count < MAX_WORDS) {
            strcpy(list[word_count].word, buffer);
            list[word_count].frecuency++;
            word_count++;
        }
    } 

    fclose(file);

    printf("word\t\tfrecuency\n");
    printf("================\n");
    for (int i = 0; i < word_count; i++) {
        printf("%-20s%d\n", list[i].word, list[i].frecuency);
    }

    return 0;
}

// word         Frecuencia
// =======================   
// the                 6
// quick               3
// brown               3
// fox                 3
// jumps               1
// over                3
// lazy                3
// dog.                1
// congratulations!    1
// if                  1
// jumped              1
// dog                 1
// then                1
// why                 1
// did                 1
// jump                1
// dog?                1
// to                  1
// recuperate          1