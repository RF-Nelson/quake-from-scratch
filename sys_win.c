#include <stdint.h>
#include <windows.h>

typedef uint8_t uint8;
typedef int32_t int32;
typedef uint32_t uint32;

#define MAX_NUM_ARGVS 3

int32 argc = 1;
uint8 *largv[MAX_NUM_ARGVS+1];

int32 Q_strcmp(uint8 *s1, uint8 *s2)
{
    while (*s1 == *s2)
    {
        if (!*s1)
            return 0;
        ++s1;
        ++s2;
    }

    return ((*s1 < *s2) ? -1 : 1);
}

// decimal or hexadecimal
// negative and positive
// "50" "12" "0x4321464fd" "0X4AbdC"
int32 Q_atoi(uint8 *str)
{
    int32 sign = 1;
    int32 val = 0;
    uint8 c;

    if (*str == '-')
    {
        sign = -1;
        str++;
    }

    // hexadecimal
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
        str += 2;
        while (1)
        {
            c = *str;
            str++;
            if (c >= '0' && c <= '9')
                val = val * 16 + c - '0';
            else if (c >= 'a' && c <= 'f')
                val = val * 16 + c - 'a' + 10;
            else if (c >= 'A' && c <= 'F')
                val = val * 16 + c - 'A' + 10;
            else
                return val*sign;
        }
    }

    // decimal
    while (1)
    {
        c = *str;
        str++;
        if (c < '0' || c > '9')
            return sign * val;
        val = val * 10 + c - '0';
    }
}

int32 COM_CheckParm(uint8 *parm)
{
    for (int32 i = 1; i < argc; i++)
    {
        if (!Q_strcmp(parm, largv[i]))
            return i;
    }

    return 0;
}

int32 CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32 nCmdShow)
{
    largv[0] = "";

    while (*lpCmdLine && (argc < MAX_NUM_ARGVS+1))
    {
        while (*lpCmdLine && ((*lpCmdLine <= 32) || (*lpCmdLine > 126)))
            lpCmdLine++;

        if (*lpCmdLine)
        {
            largv[argc] = lpCmdLine;
            argc++;

            while (*lpCmdLine && ((*lpCmdLine > 32) && (*lpCmdLine <= 126)))
                lpCmdLine++;

            if (*lpCmdLine)
            {
                *lpCmdLine = 0;
                lpCmdLine++;
            }
        }
    }

    int32 test = COM_CheckParm("-setalpha");
    int32 value = Q_atoi(largv[test+1]);
    return 0;
}
