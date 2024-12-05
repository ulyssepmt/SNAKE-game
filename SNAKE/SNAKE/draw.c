#include "draw.h"

void debug(DWORD err) {

    char buf[256];

    sprintf(buf, "err = %lu", err);

    MessageBoxA(0, buf, _T("MESSAGE0"), MB_OK);
}

void drawPixel(HDC hdc, int x, int y, int w, int h, HBRUSH color) {

    SelectObject(hdc, color);

    PatBlt(hdc, x, y, w, h, PATCOPY);
}


void putFood(struct FOOD* pFood, HDC hdc) {
    //HWND hwnd = FindWindow(_T("SNAKE"), _T("SNAKE"));
    //GetWindowRect(hwnd, &rect); 
    pFood->x = 30 + rand() % (WIDTH - 50);  

    pFood->y = 10 + rand() % (HEIGHT - 50);

    if (pFood->x <= 30 && pFood->y <= 10) {
        do {
            pFood->x = 30 + rand() % (WIDTH - 50);

            pFood->y = 10 + rand() % (HEIGHT - 50);

        } while (pFood->x <= 30 && pFood->y <= 10);
    }

    drawPixel(hdc, pFood->x, pFood->y, pFood->w, pFood->h, pFood->color);
}

void printScore(HDC hdc, int score, char scoreBuf[15]) {

    sprintf(scoreBuf, "[score = %d]", score);

    scoreBuf[strlen(scoreBuf) + 1] = '\0';

    SetTextColor(hdc, RGB(0, 0, 0));

    SetBkColor(hdc, RGB(0, 220, 255));

    TextOutA(hdc, 0, 0, scoreBuf, strlen(scoreBuf));
}

void printText(HDC hdc, HBRUSH black, LPCWSTR msgToPlayer, int idText) {

    SIZE msgToPlayerSize;

    SelectObject(hdc, black);

    PatBlt(hdc, 0, 0, WIDTH, HEIGHT, PATCOPY);

    GetTextExtentPoint32W(hdc, msgToPlayer, lstrlen(msgToPlayer), &msgToPlayerSize);

    if (idText == 0) {

        SetBkColor(hdc, RGB(255, 0, 0));

        SetTextColor(hdc, RGB(0, 0, 0));

        TextOutW(hdc, (WIDTH / 2) - (msgToPlayerSize.cx / 2), (HEIGHT / 4) - msgToPlayerSize.cy / 2, msgToPlayer, lstrlen(msgToPlayer));
        
        Beep(300, 1000);
    }
    else {

        SetBkColor(hdc, RGB(0, 255, 0));

        SetTextColor(hdc, RGB(0, 0, 0));

        TextOutW(hdc, (WIDTH / 2) - (msgToPlayerSize.cx / 2), (HEIGHT / 4) - msgToPlayerSize.cy, msgToPlayer, lstrlen(msgToPlayer));

        Beep(700, 1000);
    }

    msgToPlayer = L"Press [SPACE] key to start a new game.";

    SetBkColor(hdc, RGB(0, 0, 0));

    SetTextColor(hdc, RGB(255, 255, 255));

    GetTextExtentPoint32W(hdc, msgToPlayer, lstrlen(msgToPlayer), &msgToPlayerSize);

    TextOutW(hdc, (WIDTH / 2) - (msgToPlayerSize.cx / 2), (HEIGHT / 2) + 50, msgToPlayer, lstrlen(msgToPlayer));



}
BOOL printMenu() {
    HWND snakeWin = NULL;

    HDC hdc = NULL,
        hMem = NULL;

    HBITMAP hbSnake = NULL;

    LPCWSTR welcomeStr,
        credStr,
        infoStr;

    HFONT hFont,
        oldFont;

    RECT rect = { 0, 0, WIDTH, HEIGHT };

    snakeWin = FindWindow(_T("SNAKE"), _T("SNAKE"));

    if (!snakeWin)
        return FALSE;

    hbSnake = (HBITMAP)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1),
        IMAGE_BITMAP,
        0, 0,
        LR_DEFAULTSIZE | LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS);

    if (!hbSnake)
        return FALSE;

    hdc = GetDC(snakeWin);
    if (!hdc) {
        DeleteObject(hbSnake);
        return FALSE;
    }

    hMem = CreateCompatibleDC(hdc);

    if (!hMem) {

        ReleaseDC(snakeWin, hdc);

        DeleteObject(hbSnake);

        return FALSE;
    }

    welcomeStr = L"SNAKE game v1.0\n____________";
    infoStr = L"*****************************************************\nPress [SPACE] key to start a new game !\nUse [<][^][>] keys to move.\n\nHAVE FUN!\n\n*****************************************************\n";
    credStr = L"Game coded in C by sk0za, finished on 05/12/2024.";

    hFont = CreateFontW(40, 20, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, FF_ROMAN, TEXT("Small Fonts"));

    if (!hFont) {

        DeleteDC(hMem);

        ReleaseDC(snakeWin, hdc);

        DeleteObject(hbSnake);

        return FALSE;
    }

    oldFont = SelectObject(hdc, hFont);

    SetBkColor(hdc, RGB(0, 0, 0));

    SetTextColor(hdc, RGB(0, 255, 0));

    DrawTextW(hdc, welcomeStr, -1, &rect, DT_CENTER | DT_TOP);

    SelectObject(hMem, hbSnake);

    BitBlt(hdc, 0, 80, WIDTH, 57, hMem, 0, 0, SRCCOPY);

    SelectObject(hdc, oldFont);

    DeleteObject(hFont);

    hFont = CreateFontW(20, 10, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, FF_ROMAN, TEXT("Small Fonts"));

    if (!hFont) {

        DeleteDC(hMem);

        ReleaseDC(snakeWin, hdc);

        DeleteObject(hbSnake);

        return FALSE;
    }

    oldFont = SelectObject(hdc, hFont);

    rect.top = HEIGHT / 3;

    SetTextColor(hdc, RGB(255, 0, 0));

    DrawTextW(hdc, infoStr, -1, &rect, DT_CENTER | DT_TOP);

    rect.top = (HEIGHT / 2) + (HEIGHT / 4);
    
    SetTextColor(hdc, RGB(0, 0, 0));
    
    SetBkColor(hdc, RGB(0, 225, 255));
    
    DrawTextW(hdc, credStr, -1, &rect, DT_CENTER | DT_TOP);

    SelectObject(hdc, oldFont);

    DeleteObject(hFont);

    DeleteObject(hbSnake);

    DeleteDC(hMem);

    ReleaseDC(snakeWin, hdc);

    return TRUE;
}