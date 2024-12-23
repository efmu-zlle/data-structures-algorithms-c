#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <unistd.h>

#define MAX_WORD_LENGTH 50
#define MAX_WORDS 100

typedef struct {
    char word[MAX_WORD_LENGTH];
    int frecuency;
} WordFrecuency;

int main(void) {
    FILE *file = fopen("words.txt", "r");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    char buffer[MAX_WORD_LENGTH];
    WordFrecuency list[MAX_WORDS];
    int count = 0;
    while (fscanf(file, "%s", buffer) != EOF) {
        // loop through the list and search for the current value
        int found = 0;

        strcpy(list[count].word, buffer);
        list[count].frecuency++;
        count++;
    } // need logic here 

    fclose(file);
    return 0;
}

// Palabra         Frecuencia
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