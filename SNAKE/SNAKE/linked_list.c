#include "game.h"

struct SNAKE* createBody(int x, int y, int w, int h, int id) {
    struct SNAKE* newBody = (struct SNAKE*)malloc(sizeof(struct SNAKE));
    newBody->x = x;
    newBody->y = y;
    newBody->w = w;
    newBody->h = h;
    newBody->next = NULL;

    return newBody;
}

void addBody(struct SNAKE** head_ref, 
    int x, int y, int w, int h, int id) {

    struct SNAKE* newBody = createBody(x, y, w, h, id);

    struct SNAKE* last = *head_ref;

    if (*head_ref == NULL) {

        *head_ref = newBody;

        return;
    }

    while (last->next != NULL) {

        last = last->next;
    }

    last->next = newBody;
}

void clean(struct SNAKE** snakeHead, HWND* hwnd, HDC* hdc) {

    struct SNAKE* current = *snakeHead;

    while (current != NULL) {

        struct SNAKE* next = current->next;

        free(current);

        current = next;
    }
    *snakeHead = NULL;

    if (hdc && *hdc) {

        ReleaseDC(*hwnd, *hdc);

        *hdc = NULL;
    }

    if (hwnd && *hwnd) {

        DestroyWindow(*hwnd);

        *hwnd = NULL;
    }
}