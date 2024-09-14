#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "instant.h"

int max(int a, int b) {
    if(a > b) return a;
    else return b;
}

int alternative(int* nums, int i) {
    if (i < 0) {
        return 0;
    }
    return max(alternative(nums, i - 2) + nums[i], alternative(nums, i - 1));
}

int dynamic(int* nums, int i) {
    if (i <= 0) {
        return 0;
    }
    int previous = 0;
    int next = 0;
    for(; i >= 0; i--) {
        int guess = previous+nums[i];
        previous = next;
        if(guess > next) {
            next = guess;
        }
    }
    return next;
}

int* read_file(const char* name, int* restrict size) {
    FILE* file = stdin;
    if(strcmp(name, "-") != 0) {
        file = fopen(name, "r");
        if(file == NULL) {
            puts("Arquivo não encontrado");
            exit(1);
        }
    }
    fscanf(file, "%d\n", size);
    int* arr = calloc(sizeof(int), *size);
    for (int i = 0; i < *size; i++) {
        fscanf(file, "%d", arr + i);
    }
    fclose(file);
    return arr;
}

int main(int argc, char** argv) {
    if(argc < 3) {
        puts("Faltam argumentos");
        return 1;
    }
    char* stat = argv[1];
    bool is_alt = false;
    int size = 0;

    switch (stat[0]) {
        case 'D':
        case 'A':
            is_alt = stat[0] == 'A';
            break;
        default:
            puts("Valor inválido de estratégia");
            return 1;
    }
    int* arr = read_file(argv[2], &size);

    instant before = now();
    int val = is_alt? alternative(arr, size-1) : dynamic(arr, size-1);
    instant after = now();

    print_time_elapsed(after, before);

    FILE* output = fopen("saida.txt", "w");
    fprintf(output, "%d\n", val);
    fclose(output);

    free(arr);
    return 0;
}
