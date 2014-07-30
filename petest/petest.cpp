// petest.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <stdio.h>
#include "resource.h"
#include "test_class.h"
//----------------------------------------
void test_class()
{
	CTest1 *pTst = new CTest1;
	pTst->func1();
	pTst->func1();
	pTst->func1();
}
//----------------------------------------
void test_printf()
{
	printf("hello %d and %d", 3, 4);
}
//----------------------------------------
int test_api()
{
	Sleep(100);
	ShowWindow(NULL,1);
	return 88;
}
//----------------------------------------
struct st_TestStruc
{
	int m1;
	int m2;
	int m3;
};
int test_Struc1(st_TestStruc* p)
{
	return p->m1 * 2 + p->m2 * 3 + p->m3;
}
void test_Struc2(st_TestStruc* p)
{
	p->m1 = 9;
	p->m3 = 8;
	p->m2 = 7;
}

int test_Struc()
{
	st_TestStruc st;
	st.m1 = 2;
	st.m2 = 3;
	st.m3 = 1;
	test_Struc2(&st);
	return test_Struc1(&st);
}
//----------------------------------------
void __stdcall nop3(int i);
int test_switch_case(int i)
{
	int n = 0;
	switch(i)
	{
	case 1: n+= 2; break;
	case 2: n+= 5; break;
	case 4: n+= 9; break;
	default: n+=6; break;
	}
	//nop3(n*(n+3));
	//nop3(n*(n+3));
	//nop3(n*(n+3));
	return n;
}
//----------------------------------------
int nop1(int i)
{
	return i+2;
}
int nop2(int i1, int i2)
{
	return i1+i2+3;
}
int g_int;
void __stdcall nop3(int i)
{
	g_int = i;
}
int ttest_main()
{
	int i1 = nop1(1);
	nop3(i1);
	int i2 = nop2(2,3);
	nop3(i2);
	int i3 = nop1(4);
	nop3(i3);
	int i4 = nop2(5,6);
	return i1+i3+7;
}
int test_main1()
{
	for(int i = 0; i< 100; i++)
	{
		nop3(i);
		for(int j=0; j < 22; j++)
		{
			nop3(nop2(i,j));
		}
	}
	return 5;
}
int test_Array(int arg[6][6])
{
	for (int i =1; i< 6; i++)
	{
		for(int j = 1; j < 6; j++)
		{
			arg[i-1][j] = i+j;
		}
	}
	return 9;
}
int test_main()
{
//	test_class();
//	return 0;
	test_printf();
	return 0;
	test_api();
	return 0;
	//-----------
	//nop3(test_switch_case(9));
	//return 0;
	//-----------
	nop3(test_Struc());
	return 0;
	//-----------
	int buf[6][6];
	return test_Array(buf);
}
//----------------------------------------

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	Sleep(test_main());
	/*
	Sleep(test_main()/1000);
.text:0040102A                 mov     ecx, eax
.text:0040102C                 mov     eax, 10624DD3h
.text:00401031                 imul    ecx
.text:00401033                 sar     edx, 6
.text:00401036                 mov     eax, edx
.text:00401038                 shr     eax, 1Fh
.text:0040103B                 add     edx, eax
.text:0040103D                 push    edx             ; dwMilliseconds
.text:0040103E                 call    ds:Sleep


		Sleep(test_main()/10000);
.text:0040102A 024                 mov     ecx, eax
.text:0040102C 024                 mov     eax, 68DB8BADh
.text:00401031 024                 imul    ecx
.text:00401033 024                 sar     edx, 0Ch
.text:00401036 024                 mov     eax, edx
.text:00401038 024                 shr     eax, 1Fh
.text:0040103B 024                 add     edx, eax
.text:0040103D 024                 push    edx             ; dwMilliseconds
.text:0040103E 028                 call    ds:Sleep

	*/

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PETEST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_PETEST);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_PETEST);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_PETEST;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
