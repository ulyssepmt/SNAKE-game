#pragma once
#include "game.h" 
#include "resource.h"

//§#define IDB_IMAGE1 129 

void drawPixel(HDC hdc, int x, int y, int w, int h, HBRUSH color); 

void putFood(struct FOOD* pFood, HDC hdc); 

void printScore(HDC hdc, int score, char scoreBuf[15]); 

void printText(HDC hdc, HBRUSH black, LPCWSTR msgToPlayer, int idText); 

BOOL printMenu(); 