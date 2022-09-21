//
// Created by jzadorozhnaya on 21.09.22.
//
#include <stdio.h>
#include <string.h>
#define BUF_SIZE 1024

int main()
{
    char world[BUF_SIZE];
    fgets(world, sizeof(world), stdin);
    world[strlen(world) - 1] = '\0';
    printf("Hello, %s!", world);
    return 0;
}