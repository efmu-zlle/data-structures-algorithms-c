#include <stdio.h>
#include <string.h>

void recursive_string(char str[], int left, int right) {
    if (left >= right) {
        return;
    }

    char temp = str[left];
    str[left] = str[right];
    str[right] = temp;

    recursive_string(str, left + 1, right - 1);
}

int main(void) {
    char str[] = "hello";
    recursive_string(str, 0, strlen(str) - 1);

    printf("%s\n", str);

    return 0;
}