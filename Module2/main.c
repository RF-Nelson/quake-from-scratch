#include <windows.h>

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM, lParam)
{
    // catch any relevant messages here
    // switch (uMsg)
    
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = MainWndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = "Module 2";

    if (!RegisterClass(&wc)) {
        exit(EXIT_FAILURE);
    }

    HWND mainwindow;
    DWORD WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
    
    RECT r;
    r.top = r.left = 0;
    r.right = 800;
    r.bottom - 600;

    AdjustWindowRect(&r, WindowStyle, FALSE);

    mainwindow = CreateWindowEx(
        0,
        "Module 2",
        "Lesson 2.1",
        WindowStyle,
        200,
        200,
        r.right - r.left,
        r.bottom - r.top,
        NULL,
        NULL,
        hInstance,
        0
    );

    ShowWindow(mainwindow, SW_SHOWDEFAULT);

    HDC DeviceContext = GETDC(mainwindow);
    PatBlt(DeviceContext, 0, 0, 800, 600, BLACKNESS);
    ReleaseDV(mainWindow, DeviceContext);

    return 0;
}
