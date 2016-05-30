// fcitx-remote.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#pragma comment(lib, "user32.lib")

using namespace std;

// The first parameter is not correct, but it works. So it's fine here.
static const HKL ENG_LAYOUT = LoadKeyboardLayout((LPCWSTR)"00000409", 2);

BOOL isEngLayout()
{
    return GetKeyboardLayout(0) == ENG_LAYOUT;
}

BOOL toggleInputMethod()
{
    INPUT ips[4];
    memset(ips, 0, sizeof(ips));
    for (int i = 0; i < 4; i++) {
        ips[i].type = INPUT_KEYBOARD;
    }
    ips[0].ki.wVk = ips[2].ki.wVk = VK_LWIN;
    ips[1].ki.wVk = ips[3].ki.wVk = VK_SPACE;
    ips[2].ki.dwFlags = ips[3].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(4, ips, sizeof(INPUT));
    return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
    if (argc > 1)
    {
        if (!_tcscmp(argv[1], _T("-c")))
        {
            if (!isEngLayout())
            {
                toggleInputMethod();
            }
        }
        else if (!_tccmp(argv[1], _T("-o")))
        {
            if (isEngLayout())
            {
                toggleInputMethod();
            }
        }
    }
    else
    {
        cout << (2 - isEngLayout()) << endl;
    }
    return 0;
}
