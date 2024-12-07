#include "game.h"

BOOL checkCollision(int xObject1, int yObject1, int wObject1, int hObject1,
    int xObject2, int yObject2, int wObject2, int hObject2) { 
    // importée depuis starun (voir : https://github.com/ulyssepmt/Starun/blob/main/collision.c) 

    RECT rcEntitie1 = { xObject1, yObject1, xObject1 + wObject1, yObject1 + hObject1 };

    RECT rcEntitie2 = { xObject2, yObject2, xObject2 + wObject2, yObject2 + hObject2 };

    RECT res;

    return IntersectRect(&res, &rcEntitie1, &rcEntitie2);

}

void gameLogic(struct SNAKE* pSnake, struct FOOD* pFood, HDC hdc, 
    HBRUSH head, HBRUSH body, HBRUSH mask, int dir) {

    struct SNAKE* current = pSnake->next;

    int dirX = 0,
        dirY = 0,
        prevX = 0,
        prevY = 0,
        tempX = 0,
        tempY = 0,
        score = 0;

    char scoreBuf[15];

    BOOL init = FALSE, 
        collision = FALSE;

    if (dir == -1) {
        dir = 0; // droite par défaut
    }

    putFood(pFood, hdc);

    while (TRUE) {

        if (GetKeyState(VK_RIGHT) & 0x8000) dir = 0;

        if (GetKeyState(VK_DOWN) & 0x8000) dir = 1;

        if (GetKeyState(VK_LEFT) & 0x8000) dir = 2;

        if (GetKeyState(VK_UP) & 0x8000) dir = 3;

        switch (dir) {

        case 0: dirX = 10; dirY = 0; break; // Droite

        case 1: dirX = 0; dirY = 10; break; // Bas

        case 2: dirX = -10; dirY = 0; break; // Gauche

        case 3: dirX = 0; dirY = -10; break; // Haut
        }

        prevX = pSnake->x, prevY = pSnake->y; //1er segment
      
        /*char buf[256];
        sprintf(buf, "x=%d & y=%d", prevX, prevY); 
        MessageBoxA(0, buf, "msg", MB_OK); 
        */
        //if (pSnake->x + pSnake->w >= WIDTH || pSnake->y + pSnake->h >= HEIGHT || pSnake->x < 0 || pSnake->y < 0) {

        // maj de la direction de la tête
        pSnake->x += dirX;

        pSnake->y += dirY;

        if (pSnake->x >= WIDTH || pSnake->y >= HEIGHT || pSnake->x < 0 || pSnake->y < 0) {

            printText(hdc, mask, L"GAME OVER: The snake hurt itself against the wall !", 0);

            break;
        }

        if (checkCollision(pSnake->x, pSnake->y, pSnake->w, pSnake->h, pFood->x, pFood->y, pFood->w, pFood->h)) {

            drawPixel(hdc, pFood->x, pFood->y, pFood->w, pFood->h, mask);

            score += 10;

            addBody(&pSnake, 0, 0, 10, 10, 0);  // ajout d'un nouveau segment 

            putFood(pFood, hdc);
        }


        drawPixel(hdc, pSnake->x, pSnake->y, pSnake->w, pSnake->h, head);

        current = pSnake->next;

        if (collision) {

            printText(hdc, mask, L"GAME OVER: The snake bumped into itself !", 0);

            break;
        }

        while (current != NULL) {
 
            tempX = current->x, tempY = current->y;

            current->x = prevX;

            current->y = prevY;

            if ((pSnake->x == current->x && pSnake->y == current->y) && init) {

                collision = TRUE;

                break;
            }

            // efface l'ancienne position
            drawPixel(hdc, tempX, tempY, current->w, current->h, mask);

            drawPixel(hdc, current->x, current->y, current->w, current->h, body);
            // segment suivant
            prevX = tempX;

            prevY = tempY;

            current = current->next;
        }

        printScore(hdc, score, scoreBuf);

        if (score >= 1000) {

            printText(hdc, mask, L"YOU WIN ! You're so fat you've been promoted to king of snakes !", 1);

            break;
        }
        init = TRUE; 

        Sleep(40);
    }
}

int initializeGame(struct SNAKE** pSnake, struct FOOD* pFood, HWND* snakeWin, HDC* hdc, HBRUSH mask) {

    *snakeWin = FindWindow(_T("SNAKE"), _T("SNAKE"));

    if (!*snakeWin) {

        MessageBox(NULL, _T("Window 'SNAKE' not found!"), _T("Error"), MB_OK);

        return 1;
    }

    *hdc = GetDC(*snakeWin);
    if (!*hdc) {

        MessageBox(NULL, _T("Failed to get HDC!"), _T("Error"), MB_OK);

        return 1;
    }

    *pSnake = (struct SNAKE*)malloc(sizeof(struct SNAKE));
    if (!*pSnake) {

        MessageBox(NULL, _T("Failed to allocate memory for snake!"), _T("Error"), MB_OK);

        return 1;
    }

    (*pSnake)->next = NULL;

    (*pSnake)->x = 310;

    (*pSnake)->y = 200;

    (*pSnake)->w = 10;

    (*pSnake)->h = 10;
  
    pFood->color = CreateSolidBrush(RGB(255, 0, 0));

    pFood->w = 10;

    pFood->h = 10;

    addBody(pSnake, 320, 200, (*pSnake)->w, (*pSnake)->h, 1);

    addBody(pSnake, 330, 200, (*pSnake)->w, (*pSnake)->h, 2);

    addBody(pSnake, 340, 200, (*pSnake)->w, (*pSnake)->h, 3);

    SelectObject(*hdc, mask);

    PatBlt(*hdc, 0, 0, WIDTH, HEIGHT, PATCOPY);

    //srand(time(NULL)); 

    return 0;
}

DWORD WINAPI runGame(LPVOID lp) {
    struct SNAKE* snake = NULL;

    struct FOOD food = { 0 };

    struct FOOD* pFood = &food;

    HWND snakeWin = NULL;

    HDC hdc = NULL;

    HBRUSH head = CreateSolidBrush(RGB(0, 200, 200)); // Couleur du serpent

    HBRUSH body = CreateSolidBrush(RGB(0, 255, 0)); // Couleur de la tête

    HBRUSH mask = CreateSolidBrush(RGB(0, 0, 0));

    if (!printMenu()) {

        if (mask) {

            DeleteObject(mask);
        }
        MessageBox(NULL, _T("Failed to initialize game menu!"), _T("Error"), MB_OK);

        ExitProcess(EXIT_FAILURE);
        //return 1;
    }
    while (TRUE) {
        if (GetKeyState(VK_SPACE) & 0x8000) {

            if (initializeGame(&snake, pFood, &snakeWin, &hdc, mask) == 1) {

                MessageBox(NULL, _T("Failed to initialize snake game!"), _T("Error"), MB_OK);

                break;
            }
            gameLogic(snake, pFood, hdc, head, body, mask, -1);

            clean(&snake, &snakeWin, &hdc);
        }

        Sleep(50);
    }
    if (hdc && snakeWin) {

        ReleaseDC(snakeWin, hdc);
    }
    if (mask) {

        DeleteObject(mask);
    }
    else if (body) {

        DeleteObject(body);
    }
    else if (head) {

        DeleteObject(head);
    }

    ExitProcess(EXIT_FAILURE);

    return 0;
}