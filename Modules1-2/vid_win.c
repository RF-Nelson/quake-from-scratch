#include "quakedef.c"
#include "winquake.h"

int BufferWidth = 640;
int BufferHeight = 480;
int WindowHeight = 640;
int WindowWidth = 480;
int BytesPerPixel = 4;
void* BackBuffer = NULL;
HWND MainWindow;

BITMAPINFO BitMapInfo = { 0 };

void VID_Init(void)
{
  VID_SetMode(WindowWidth, WindowHeight);

  // DEFINE BITMAP INFO
  BitMapInfo.bmiHeader.biSize = sizeof (BitMapInfo.bmiHeader);
  BitMapInfo.bmiHeader.biWidth = BufferWidth;
  BitMapInfo.bmiHeader.biHeight = -BufferHeight;
  BitMapInfo.bmiHeader.biBitCount = 8 * BytesPerPixel;
  BitMapInfo.bmiHeader.biCompression = BI_RGB;

  BackBuffer = malloc(BufferWidth * BufferHeight * BytesPerPixel);

  HDC DeviceContext = GETDC(MainWindow);
  PatBlt(DeviceContext, 0, 0, BufferHeight, BufferWidth, BLACKNESS);
  ReleaseDC(MainWindow, DeviceContext);
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM, lParam)
{
  // catch any relevant messages here
  switch (uMsg)
  {
  case WM_ACTIVATE:
    break;

  case WM_CREATE:
    break;

  case WM_DESTROY:
      Sys_Shutdown()
      break;

  case WM_KEYDOWN:
  {

  } break;

  default:
      Result = DefWindowProc(hWnd, uMsg, wParam, lParam);
  }

  return Result;
}

void VID_SetMode(void)
{
  if (BackBuffer)
  {
    VID_Shutdown();
  }

  WindowWidth = Width;
  WindowHeight = Height;

  WNDCLASSEX wc = { 0 };
  wc.lpfnWndProc = MainWndProc;
  wc.hInstance = GlobalInstance;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.lpszClassName = "Module 3";

  if (!RegisterClassEx(&wc)
  {
      exit(EXIT_FAILURE);
  }

  DWORD WindowExStyle = 0;
  DWORD WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

  BOOL Fullscreen = FALSE;

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
  MainWindow = CreateWindowEx(
    WindowExStyle, "Module 3", "Lesson 3.5", WindowStyle,
    CW_USERDEFAULT, CW_USERDEFAULT,
    r.right - r.left, r.bottom - r.top,
    NULL, NULL, GlobalInstance, 0
  );

  ShowWindow(MainWindow, SW_SHOWDEFAULT);
}

void VID_Shutdown(void)
{
  free(BackBuffer);
}
