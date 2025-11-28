#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#endif

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause_screen() {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');
    getchar(); // Wait for Enter
}

void get_string_input(char *buffer, int size) {
    fgets(buffer, size, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

int get_int_input() {
    int value;
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%d", &value) != 1) {
        return -1; // Error indicator
    }
    return value;
}

float get_float_input() {
    float value;
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%f", &value) != 1) {
        return -1.0f; // Error indicator
    }
    return value;
}
