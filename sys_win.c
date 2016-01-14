#include "winquake.h"
#include "quakdef.h"

int32 CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32 nCmdShow)
{
    COM_ParseCmdLine(lpCmdLine);

    int32 test = COM_CheckParm("-setalpha");
    int32 value = Q_atoi(com_argv[test+1]);
    return 0;
}
