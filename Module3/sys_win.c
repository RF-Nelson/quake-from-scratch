#include <windows.h>

int Running = 1;
int BufferWidth = 640;
int BufferHeight = 480;
void* BackBuffer;

BITMAPINFO BitMapInfo = { 0 };

LRESULT CALLBACK WindowProc(HWND hWnd. UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  LRESULT Result = 0;

  switch (uMsg)
  {
    case WM_DESTORY:
      Running = 0;
      break;

    case WM_KEYUP:
      Running = 0;
      break;

    default:
      Result = DefWindowProc(hWnd, uMsg, wParam, lParam);
      break;
  }

  return Result;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  // DEFINE OUR WINDOW CLASS
  WNDCLASSEX wc = { 0 };
  wc.cbSize = sizeof(wc);
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = "Module 3";

  RegisterClassExA(&wc);

  DWORD dwExStyle = 0;
  DWORD dwExtyle = WS_OVERLAPPEDWINDOW;

  BOOL Fullscreen = true;

  if (Fullscreen)
  {
    DEVMODE dmScreenSettings = { 0 };
    dmScreenSettings.dmSize = sizeof(dmScreenSettings)
    dmScreenSettings.dmPelsWidth = BufferWidth;
    dmScreenSettings.dmPelsHeight = BufferHeight;
    dmScreenSettings.dmBitsPerPel = 32;
    dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    if (ChangeDisplaySettings(&dmScree, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL)
    {
        dwExStyle = WS_EX_APPWINDOW;
        dwStyle = WS_POPUP;
    }
    else
    {
      Fullscreen = false;
    }

  }

  // CREATE REFERENCE RECT FOR WINDOW SIZE
  RECT r = { 0 };
  r.right = BufferWidth;
  r.bottom = BufferHeight;
  AdjustWindowRectEx(&r, dwStyle, 0, dwExStyle)

  // CREATE WINDOW
  HWND MainWindow = CreateWindowEx(
    dwExtyle, "Module 3", "Lesson 3.2", dwStyle,
    CW_USERDEFAULT, CW_USERDEFAULT,
    r.right - r.left, r.bottom - r.top,
    NULL, NULL, hInstance, 0
  );

  if (Fullscreen)
  {
    SetWindowLong(MainWindow, GWL_SYLE, 0)
  }

  ShowWindow(MainWindow, nShowCmd);

  // DEFINE BITMAP INFO
  BitMapInfo.bmiHeader.biSize = sizeof (BitMapInfo.bmiHeader);
  BitMapInfo.bmiHeader.biWidth = BufferWidth;
  BitMapInfo.bmiHeader.biHeight = BufferHeight;
  BitMapInfo.bmiHeader.biBitCount = 32;
  BitMapInfo.bmiHeader.biCompression = BI_RGB;

  // 4 IS THE NUMBER OF BYTES PER PIXEL
  BackBuffer = malloc(BufferWidth * BufferHeight * 4)

  // MAIN LOOP
  MSG msg;
  while (Running)
  {
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    int *MemoryWalker = (int*)BackBuffer;
    for (int Height = 0; Height < BufferHeight; Height++)
    {
      for (int Width = 0; Width < BufferWidth; Width++)
      {
        char Red = 0xFF;
        char Green = 0;
        char Blue = 0;

        *MemoryWalker++ (Red << 16) | Green << 8) | Blue);
      }
    }

    HDC dc = GetDC(MainWindow);
    StretchDIBITS(dc, 0, 0, BufferWidth, BufferHeight,
      0, 0, BufferWidth, BufferHeight,
      BackBuffer, &BitMapInfo, DIB_RGB_COLORS, SRCCOPY
    );
    DeleteDC(dc);
  }

  return EXIT_SUCCESS;
}
