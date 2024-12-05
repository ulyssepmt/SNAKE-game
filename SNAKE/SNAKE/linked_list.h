#pragma once
#include "game.h"

void addBody(struct SNAKE** head_ref, int x, int y, int w, int h); 
void clean(struct SNAKE** snakeHead, HWND* hwnd, HDC* hdc); 