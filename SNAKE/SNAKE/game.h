#pragma once
#include "main.h"

extern struct SNAKE {
    int x;
    int y;
    int w;
    int h;
    struct SNAKE* next;
};

struct FOOD {
    int x;
    int y;
    int w;
    int h;
    HBRUSH color;
};

DWORD WINAPI runGame(LPVOID lp); 

BOOL checkCollision(int xObject1, int yObject1, int wObject1, int hObject1,
    int xObject2, int yObject2, int wObject2, int hObject2); 
