#include <Windows.h>
#include <Winuser.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Userenv.h>
#include <iostream>
#include <string>


using namespace std;

#define _WIN32_WINNT 0x0500

HHOOK _hook;

KBDLLHOOKSTRUCT kbdStruct;

int previous_key_time = 0;
int current_key_time = 0;

int first_key_input = 0;
int bad_usb_detector = 0;

int program_end = 0;
int authenticate_user = 0;

int powershell=0;
int powershell_waring=0;

void SetHook();
void key_decoder(DWORD vkCode);
int auth_user();
LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam);
void SetHook();
void ReleaseHook();


void key_decoder(DWORD vkCode)
{
	current_key_time = clock();

	if (first_key_input != 0)
	{

		if ((current_key_time - previous_key_time) <= 1)
		{
			printf("time interval < 0.001 seconds\n");
			bad_usb_detector++;
		}
		else
		{
			printf("time interval > 0.001 seconds\n");
		}

	}

	if (bad_usb_detector == 10)
	{
		printf("bad usb detected!\n");

		LockWorkStation();

		bad_usb_detector = 0;
	}

	first_key_input = 1;

	previous_key_time = current_key_time;


	switch(powershell)
	{
	case(0):
		if(vkCode==0x50)	powershell=1;	else powershell=0;	break;
	case(1):
		if(vkCode==0x4f)	powershell=2;	else powershell=0;	break;
	case(2):
		if(vkCode==0x57)	powershell=3;	else powershell=0;	break;
	case(3):
		if(vkCode==0x45)	powershell=4;	else powershell=0;	break;
	case(4):
		if(vkCode==0x52)	powershell=5;	else powershell=0;	break;
	case(5):
		if(vkCode==0x53)	powershell=6;	else powershell=0;	break;
	case(6):
		if(vkCode==0x48)	powershell=7;	else powershell=0;	break;
	case(7):
		if(vkCode==0x45)	powershell=8;	else powershell=0;	break;
	case(8):
		if(vkCode==0x4c)	powershell=9;	else powershell=0;	break;
	case(9):
		if(vkCode==0x4c)	LockWorkStation();	else powershell=0;	break;

	}



	switch (vkCode)
	{
	case(0x41) :
		printf("a");
		break;
	case(0x42) :
		printf("b");
		break;
	case(0x43) :
		printf("c");
		break;
	case(0x44) :
		printf("d");
		break;
	case(0x45) :
		printf("e");
		break;
	case(0x46) :
		printf("f");
		break;
	case(0x47) :
		printf("g");
		break;
	case(0x48) :
		printf("h");
		break;
	case(0x49) :
		printf("i");
		break;
	case(0x4a) :
		printf("j");
		break;
	case(0x4b) :
		printf("k");
		break;
	case(0x4c) :
		printf("l");
		break;
	case(0x4d) :
		printf("m");
		break;
	case(0x4e) :
		printf("n");
		break;
	case(0x4f) :
		printf("o");
		break;
	case(0x50) :
		printf("p");
		break;
	case(0x51) :
		printf("q");
		break;
	case(0x52) :
		printf("r");
		break;
	case(0x53) :
		printf("s");
		break;
	case(0x54) :
		printf("t");
		break;
	case(0x55) :
		printf("u");
		break;
	case(0x56) :
		printf("v");
		break;
	case(0x57) :
		printf("w");
		break;
	case(0x58) :
		printf("x");
		break;
	case(0x59) :
		printf("y");
		break;
	case(0x5a) :
		printf("z");
		break;

	default:
		break;
	}

	printf("\n");

}


int auth_user()
{

	HANDLE hUserToken = 0;

	string ex = "";
	string user_id="";
	string user_password="";

	LPCSTR user_id_lp = "";
	LPCSTR user_password_lp = "";

	ReleaseHook();
	
	//fflush(stdin);
	//cin.clear();
	//cout.flush();

	//FreeLibraryAndExitThread;
	std::cout << "\n 후킹을 해제하는 중입니다. \n" << endl;
	std::cout << "\n 화면에 커서가 나타나면 Enter키를 입력해주세요 : \n" << endl;
	std::cin >> ex;

	//Sleep(10000);

	system("cls");

	std::cout << "윈도우 로그인 계정 ID를 입력해주세요 :" << endl;
	std::cin >> user_id;


	cout << "윈도우 로그인 계정 비밀번호를 입력해주세요 : " << endl;
	std::cin >> user_password;



	//user_id_lp = new CHAR[user_id.size() + 1];
	//strcpy(user_id_lp, user_id.c_str);
	//user_password_lp = new TCHAR[user_password.size() + 1];

	user_id_lp = user_id.c_str();
	user_password_lp = user_password.c_str();


	//check_open_proceess( "program start" );

	if (LogonUser(
		user_id_lp,
		".",
		user_password_lp,
		LOGON32_LOGON_INTERACTIVE,
		LOGON32_PROVIDER_DEFAULT,
		&hUserToken) == 0)
	{
		//printf("error!");
		authenticate_user = 0;
	}

	else{

		//printf("good!");
		authenticate_user = 1;
	}

	return authenticate_user;

}

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0)
	{

		kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);

		if (wParam == WM_KEYDOWN)
		{

			key_decoder(kbdStruct.vkCode);


		}

		if (wParam == WM_SYSKEYDOWN && kbdStruct.vkCode == VK_F3)
//		if (wParam ==WM_KEYDOWN && kbdStruct.vkCode == 0x41)
		{


			//printf("aaa\n");

			program_end = auth_user();

			if (program_end == 0)
			{
				printf("사용자 계정 정보와 일치하지 않습니다! 프로그램이 종료되지 않습니다.\n");
				SetHook();
				return true;

			}
			else
			{

				printf("일치 \n");
				exit(1);

			}

		}
/*
		if (wParam == WM_SYSKEYDOWN && kbdStruct.vkCode == VK_F12)
		{
			LockWorkStation();
			return true;
		}
*/
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
	PostMessage(HWND_BROADCAST, WM_NULL, 0, 0);
}

int main(int argc, char* argv[])
{

	HWND hwnd = GetConsoleWindow();
	HMENU hmenu = GetSystemMenu(hwnd, FALSE);
	HINSTANCE hinstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
	while (DeleteMenu(hmenu, 0, MF_BYPOSITION));


	printf("종료하시려면 Alt+f3키를 눌러주세요\n");

	SetHook();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{

	}

}
