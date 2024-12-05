#include "main.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
    switch (Msg) {

    case WM_CREATE:


    case WM_PAINT: //background de la fenêtre
    {
        PAINTSTRUCT ps;
        HDC hdc; 
        HBRUSH noir; 

        hdc = BeginPaint(hWnd, &ps);
        noir = CreateSolidBrush(RGB(0, 0, 0)); // black background
        SelectObject(hdc, noir);
        PatBlt(hdc, 0, 0, WIDTH, HEIGHT, PATCOPY);

        EndPaint(hWnd, &ps);
        DeleteObject(noir);

        break;
    }

    case WM_SYSCOMMAND:
    {
        if ((wParam & 0xfff0) == SC_CLOSE) {
            DestroyWindow(hWnd);
            return 0;
        }
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, Msg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {


    WNDCLASSEXA c;
    c.cbSize = sizeof(WNDCLASSEX);
    c.style = CS_DBLCLKS;
    c.lpfnWndProc = WndProc;
    c.cbClsExtra = 0;
    c.cbWndExtra = 0;
    c.hInstance = hInstance;
    c.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    c.hCursor = LoadCursor(NULL, IDC_ARROW);
    c.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    c.lpszMenuName = NULL;
    c.lpszClassName = _T("SNAKE");
    c.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&c)) {
        MessageBox(NULL, _T("Failed to register class !"), _T("ERROR"), MB_OK);
        return 1; 
    }

    WIDTH = 700; 
    HEIGHT = 600; 

    HWND win = CreateWindowEx(NULL, _T("SNAKE"), _T("SNAKE"),
        WS_OVERLAPPED | WS_SYSMENU,
        ((GetSystemMetrics(SM_CXSCREEN) / 2) - (WIDTH / 2)), 
        ((GetSystemMetrics(SM_CYSCREEN) / 2) - (HEIGHT/ 2)), 
        WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);

    if (!win) {
        MessageBox(NULL, _T("Failed to create window !"), _T("ERROR"), MB_OK);
        return 1;

    }
    RECT snakeWindowRect; 

    GetClientRect(win, &snakeWindowRect); //taille réelle ou les pixels doivent être dessinés (sans bordure et entête de fenêtre)

    WIDTH = snakeWindowRect.right - snakeWindowRect.left;

    HEIGHT = snakeWindowRect.bottom - snakeWindowRect.top;

    ShowWindow(win, nCmdShow);

    UpdateWindow(win);

    HANDLE hSnakeThread = CreateThread(0, 0, runGame, 0, 0, 0);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}