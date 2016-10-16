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
/*
int previous_key_time = 0;
int current_key_time = 0;
*/

clock_t previous_key_time, current_key_time;
double judgement;

int first_key_input = 0;
int bad_usb_detector = 0;

int program_end = 0;
int authenticate_user = 0;

int powershell=0;
int powershell_waring=0;

int position = -1;
int string_length = -1;
string char_add="";
string current_string="";

int previous_string_length=-1;
string previous_string="";

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
		/*
		if ((current_key_time - previous_key_time) <= 1)
		{
			printf("time interval < 0.001 seconds\n");
			bad_usb_detector++;
		}
		else
		{
			printf("time interval > 0.001 seconds\n");
		}
		*/
		
		//printf("%.6lf seconds\n", (current_key_time-previous_key_time)/(double)1000);

		judgement = (current_key_time-previous_key_time)/(double)1000;
		
		if ( judgement <= 0.001)
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


	//char
	if(  ((vkCode>=0x30)&&(vkCode<=0x5A)) || vkCode==0x20)
	{

		position = position+1;
		string_length = string_length+1;

		switch (vkCode)
		{
		case(0x20) :
			char_add=" ";
			break;		
		case(0x30) :
			char_add="0";
			break;
		case(0x31) :
			char_add="1";
			break;
		case(0x32) :
			char_add="2";
			break;
		case(0x33) :
			char_add="3";
			break;
		case(0x34) :
			char_add="4";
			break;
		case(0x35) :
			char_add="5";
			break;
		case(0x36) :
			char_add="6";
			break;
		case(0x37) :
			char_add="7";
			break;
		case(0x38) :
			char_add="8";
			break;
		case(0x39) :
			char_add="9";
			break;
		case(0x41) :
			char_add="a";
			break;
		case(0x42) :
			char_add="b";
			break;
		case(0x43) :
			char_add="c";
			break;
		case(0x44) :
			char_add="d";
			break;
		case(0x45) :
			char_add="e";
			break;
		case(0x46) :
			char_add="f";
			break;
		case(0x47) :
			char_add="g";
			break;
		case(0x48) :
			char_add="h";
			break;
		case(0x49) :
			char_add="i";
			break;
		case(0x4a) :
			char_add="j";
			break;
		case(0x4b) :
			char_add="k";
			break;
		case(0x4c) :
			char_add="l";
			break;
		case(0x4d) :
			char_add="m";
			break;
		case(0x4e) :
			char_add="n";
			break;
		case(0x4f) :
			char_add="o";
			break;
		case(0x50) :
			char_add="p";
			break;
		case(0x51) :
			char_add="q";
			break;
		case(0x52) :
			char_add="r";
			break;
		case(0x53) :
			char_add="s";
			break;
		case(0x54) :
			char_add="t";
			break;
		case(0x55) :
			char_add="u";
			break;
		case(0x56) :
			char_add="v";
			break;
		case(0x57) :
			char_add="w";
			break;
		case(0x58) :
			char_add="x";
			break;
		case(0x59) :
			char_add="y";
			break;
		case(0x5a) :
			char_add="z";
			break;

		default:
			char_add="";
			break;
		}

		cout << char_add << endl; //

		if( char_add.compare("") == 0   ) {}
		else current_string.insert(position, char_add);						//input char
			
			//string_inspec+=char_add;
			//string_inspec.insert(position, char_add);						//input char


	//string inspec
		if( current_string.find("powershell")==-1 )		{}
		else LockWorkStation();
		 

	}

	//special_key event
		if(vkCode==0x24 && position!=-1)						position=-1;															//home
		else if (vkCode==0x23 && position!=string_length)		position=string_length;													//end
		else if (vkCode==0x08 && position!=-1)			   {current_string.erase(position, 1);	position=position-1;	string_length=string_length-1;}			//back_space
		else if (vkCode==0x2E && position!=string_length)							   {current_string.erase(position+1, 1);	string_length=string_length-1;}			//del
		else if (vkCode==0x25 && position!=-1)				position=position-1;												//left_arrow
		else if (vkCode==0x27 && position!=string_length)		position=position+1;												//right_arrow
		else if (vkCode==0x26)							   {position=previous_string_length; string_length=previous_string_length; current_string=previous_string;}	//up_arrow
		else if (vkCode==0x0D)							   {previous_string_length=string_length; position=-1; string_length=-1; previous_string=current_string; current_string="";}   //enter


		cout << current_string<< endl;
		printf("position = %d\n",position);
		printf("string_length = %d\n",string_length);



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
				printf("사용자 계정 정보와 일치하지 않으므로\n");
				printf("프로그램이 종료되지 않습니다.\n");
				printf("\n");
				printf("BadUSB 탐지를 다시 시작 합니다.\n");
				printf("종료하시려면 Alt+f3키를 눌러주세요\n");
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
