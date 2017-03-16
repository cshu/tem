
#define UNICODE 0

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wchar.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    MessageBox(NULL, L"Goodbye, 來 world!", L"Note", MB_OK);
    return 0;
}
