#include "string.h"

unsigned int strlen(const char* str) {
    unsigned int sum;
    while (*str != '\0') {
        sum++;
        str++;
    }
    return sum;
}

int strcmp(const char* str1, const char* str2) {
    while (1) {
        if (*str1 == *str2) {
            if (*str1 || *str2) {
                str1++;
                str2++;
            } else {
                return 1;
            }
        } else {
            return 0;
        }
    }
}

void strcpy(const char* source, char* dest) {
    while (*source) {
        *dest = *source;
        source++;
        dest++;
    }
    *dest = '\0';
}

int string_starts_with(char *str, char *prefix) {
    int i = 0;

    while (prefix[i] != 0) {
        if (str[i] != prefix[i])
            return 0;
        i++;
    }

    return 1;
}