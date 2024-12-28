#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

void _strlen() {
    const char *string = "hello, world!";
    printf("size of the string is: %zu\n", strlen(string));
}

void _strcpy() {
    const char *string = "hello, C";
    size_t size = strlen(string);
    char copy_string[size];

    strcpy(copy_string, string);
    printf("copy string: %s\n", copy_string);
}

char *__strncopy__(char *dest, const char *src, size_t n) {
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++) 
        dest[i] = src[i];

    for ( ; i < n; i++)
        dest[i] = '\0';

    return dest;
}

void _strncopy() {
    char string[] = "programming is fun";
    size_t size = strlen(strtok(string, " "));
    char copy_string[size];

    strncpy(copy_string, string, sizeof(copy_string));
    printf("copy string is: %s\n", copy_string);
}

void _strcat() {
    char first[32] = "hello, ";
    char *second = "world";

    strcat(first, second);
    printf("new string is: %s\n", first);
}

void _strncat() {
    char first[32] = "hello, ";
    char second[] = "beautiful world";
    size_t size = strlen(strtok(second, " "));

    strncat(first, second, size);
    printf("first new string: %s\n", first);
}

void _strcmp() {
    char *first_string = "computer";
    char *second_string = "machine";

    int output = strcmp(first_string, second_string);
}

void _strncmp() {
    char *first_string = "superhero";
    char *second_string = "supermarket";

    printf("strncmp: value is: %s\n", (strncmp(first_string, second_string, 5) == 0) ? "true" : "false");
}

void _strchr() {
    char *string = "hello, world";
    char *pos = strchr(string, 'o'); // primero o y me das el resto despues de o

    long size = pos - string; 
    printf("strchr: %s\n", pos);
}

void _strrchr() {
    char *string = "hello, world!";
    char *buffer = strrchr(string, 'o'); // encuentre el ultimo de o y me despues de ese o

    printf("strrchar: %s\n", buffer);
}

void _strstr() {
    char *string = "learning C is fun";
    char *token = strstr(string, "C"); // encuentra el primer C y me da el resto 
    printf("strstr: %s\n", token);
}

void _strtok() {
    char string[] = "one,two,three,four";
    char *token = strtok(string, ","); // antes de ","

    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }
}

void _memset() {
    char string[] = "hello, world!";
    char *pos = strchr(string, ' ');
    size_t size_pos = strlen(pos);
    size_t size = strlen(strtok(string, ","));

    memset(string, '*', size);

    strncat(string, pos, size_pos);
    printf("memset: %s\n", string);
}

void _memcpy() {
    char *string = "learn C";
    size_t size = strlen(string);
    char buffer[size + 1];

    memcpy(buffer, string, sizeof(buffer));
    printf("memcpy: %s\n", buffer);
}

void _memcmp() {
    char *str_one = "abcedf";
    char *str_two = "abcxyz";

    printf("memcmp: %s\n", memcmp(str_one, str_two, 3) == 0 ? "true" : "false");
}

void tokenize_args(char *argv[], char *input) {
    int argc = 0;
    char *ptr = input;
    char *start;

    while (*ptr != '\0' && argc < 10) {
        while (isspace((unsigned int)*ptr)) {
            ptr++;
        }

        if (*ptr == '"' || *ptr == '\'') {
            // holds ' or " in order to know when to stop the loop
            // once the ptr is equal to delim it meants that we went through a word
            char delim = *ptr;
            ptr++;
            input = ptr;

            while (*ptr != delim && *ptr != '\0') {
                ptr++;
            }

            if (*ptr == delim) {
                *ptr = '\0';
                ptr++;
            }

            argv[argc++] = input;
        } else if (*ptr != '\0') {
            // holds the value that we want to store and since ptr is constaly upding we always get the newest value
            input = ptr;
            // just a pointer to play around with ptr in order to replace when the ptr is equal to \\  
            start = ptr; 
            while (*ptr != '\0' && !isspace((unsigned int)*ptr)) {
                if (*ptr == '\\') {
                    ptr++; 
                    if (*ptr != '\0') {
                        *start++ = *ptr++;
                    }
                } else {
                    *start++ = *ptr++;
                }
            }

            if (*start != '\0') {
                *start = '\0';
                ptr++;
            }

            argv[argc++] = input;
        }
    }

    argv[argc] = NULL;
}

int main(void) {
    _strlen();
    _strcpy();
    _strncopy();
    _strcat();
    _strncat();
    _strcmp();
    _strncmp();
    _strchr();
    _strrchr();
    _strstr();
    _strtok();
    _memset();
    _memcpy();
    _memcmp();

    // char input[] = "git commit -m \"test run\"";
    // char input[] = "        git commit -m \'test run\'";
    // char input[] = "hello, world \"tmp/file/name\" 'arg 3'";
    // char input[] = "hello, beautiful world";
    // char input[] = "hello, world\\ \\ script";
    char input[] = "w\\o\\r\\l\\d beautiful, code \"test run\"";
    char *argv[10];

    tokenize_args(argv, input);

    for (int i = 0; argv[i] != NULL; i++) {
        printf("argv[%d] = \"%s\"\n", i, argv[i]);
    }

    return 0;
}