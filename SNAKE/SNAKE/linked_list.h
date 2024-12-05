#pragma once
#include "game.h"

void addBody(struct SNAKE** head_ref, int x, int y, int w, int h, int id); 
void clean(struct SNAKE** snakeHead, HWND* hwnd, HDC* hdc); 