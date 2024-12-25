#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MaxMembers 128
#define MaxNameLength 32
#define MaxNameBuffer MaxNameLength + 1

typedef struct {
    char name[MaxNameLength];
    int age;
    char gender;
} Member;

void get_string(FILE *file, char string[]) {
    char ch, delim;
    int index = 0;
    string[index] = '\0';

    while (isspace(ch = fgetc(file))) ; 

    if (ch == EOF) {
        return;
    }

    delim = ch;
    while (((ch = getc(file)) != delim) && (ch != EOF)) {
        string[index++] = ch;
    }

    string[index] = '\0';
}

int get_gender(FILE *file) {
    char ch;
    while (isspace(ch = fgetc(file))) ;

    return ch;
}

int get_members(FILE *file, Member members[]) {
    int count_members = 0;
    char string[MaxNameLength];

    get_string(file, string);

    while (count_members < MaxMembers && strcmp(string, "END") != 0) {
        strcpy(members[count_members].name, string);
        fscanf(file, "%d", &members[count_members].age);
        members[count_members].gender = get_gender(file);
        count_members++;
        get_string(file, string);
    }

    return count_members;
}

void print_members(Member members[], int number_members) {
    for (int i = 0; i < number_members; i++) {
        printf("name: %s age: %d gender: %c\n", members[i].name, members[i].age, members[i].gender);
    }

    printf("\n");
}

int search(Member members[], int num_members, char *buffer) {
    for (int i = 0; i < num_members; i++) {
        if (strcmp(members[i].name, buffer) == 0) {
            return i;
        }
    }

    return -1;
}

void sort(Member members[], int num_members) {
    for (int i = 1; i < num_members; i++) {
        Member curr = members[i];
        int k = i - 1;

        while (k >= 0 && strcmp(members[k].name, curr.name) > 0) {
            members[k + 1] = members[k];
            k--;
        }

        members[k + 1] = curr;
    }
}

int main(void) {
    FILE *file = fopen("members.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "file not found\n");
        return 1;
    }

    Member members[MaxMembers];
    char buffer[MaxNameBuffer];

    int number_members = get_members(file, members);
    if (number_members == 0) {
        fprintf(stderr, "no members found\n");
        return 1;
    }

    print_members(members, number_members);

    get_string(file, buffer);
    int index_search;
    while (strcmp(buffer, "END") != 0) {
        if ((index_search = search(members, number_members, buffer)) != -1) {
            printf("%s found at location %d\n", buffer, index_search);
        } else {
            printf("%s not found\n", buffer);
        }

        get_string(file, buffer);
    }

    fclose(file);

    printf("\n");
    sort(members, number_members);
    print_members(members, number_members);

    return 0;
}
