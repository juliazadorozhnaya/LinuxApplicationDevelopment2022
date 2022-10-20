#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void range(int start, int stop, int step) {
    for (int i = start; i < stop; i += step) {
        printf("%d\n", i);
    }
}

int main(int argc, char* argv[]) {
    int start = 0, stop = 0, step = 1;

    switch (argc) {
    case 1:
        printf("--HELP--\n");
        printf("Returns a list of arithmetic progressions.\n");
        printf("Syntax: Looks like python range ([start, ]stop[, step])\n");
        printf(" start - integer number. The number of the beginning of the sequence.\n");
        printf(" stop - Required. An integer number. Generates a number up to a given number, but not including it.\n");
        printf(" step - An integer number. The difference between each number from the sequence.\n\n");
        printf("Requires at least 1 argument to follow the order given above.\n" );
        printf("Work example: gcc -g -o0 range.c -o range \n");
        printf("              ./range -- print this message\n");
        printf("              ./range N -- print numbers from 0 to N-1\n");
        printf("              ./range M N -- print numbers from M to N-1\n");
        printf("              ./range M N S -- print numbers from M to N-1 with step S\n");

        break;

    case 2:
        stop = atoi(argv[1]);
        break;

    case 3:
        start = atoi(argv[1]);
        stop = atoi(argv[2]);
        break;

    case 4:
        start = atoi(argv[1]);
        stop = atoi(argv[2]);
        step = atoi(argv[3]);
        break;

    default:
        printf("range accepts 0 to 3 arguments\n");
    }

    if (step == 0 || start > stop && step > 0 || start < stop && step < 0) {
        printf("Invalid START, STOP, STEP combination: %d %d %d\n", start, stop, step);
        return 0;
    }

    range(start, stop, step);
    return 0;
}
