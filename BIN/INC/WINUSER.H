

typedef HANDLE HACCEL;
typedef HANDLE HICON;
typedef HANDLE HMENU;
typedef HANDLE HCURSOR;
typedef HANDLE HBRUSH;
typedef HANDLE HDC;

typedef struct tagMSG {
    HWND        hwnd;
    UINT        message;
    WPARAM      wParam;
    LPARAM      lParam;
    DWORD       time;
    POINT       pt;
} MSG, *PMSG, *NPMSG, *LPMSG;


int __stdcall LoadStringA(HINSTANCE hInstance,UINT uID,LPSTR lpBuffer,int nBufferMax);
HACCEL __stdcall LoadAcceleratorsA(HINSTANCE hInstance,LPCSTR lpTableName);
BOOL __stdcall GetMessageA(LPMSG lpMsg,HWND hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax);
int __stdcall TranslateAcceleratorA(HWND hWnd,HACCEL hAccTable,LPMSG lpMsg);

HICON __stdcall LoadIconA(HINSTANCE hInstance,LPCSTR lpIconName);

HWND __stdcall CreateWindowExA(DWORD dwExStyle,LPCSTR lpClassName,LPCSTR lpWindowName,DWORD dwStyle,int X,int Y,int nWidth,int nHeight,HWND hWndParent,HMENU hMenu,HINSTANCE hInstance,LPVOID lpParam);
BOOL __stdcall ShowWindow(HWND hWnd,int nCmdShow);
BOOL __stdcall UpdateWindow(HWND hWnd);

BOOL __stdcall TranslateMessage(const MSG *lpMsg);
long __stdcall DispatchMessageA(const MSG *lpMsg);

HCURSOR __stdcall LoadCursorA(HINSTANCE hInstance,LPCSTR lpCursorName);


//BOOL __stdcall GetWindowRect(HWND hWnd,LPRECT lpRect);
BOOL __stdcall GetWindowRect(HWND hWnd,RECT * lpRect);

HWND __stdcall GetDesktopWindow();

typedef long LRESULT;

typedef LRESULT (__stdcall * WNDPROC)(HWND, UINT, WPARAM, LPARAM);

struct WNDCLASSEXA
{
    UINT        cbSize;

    UINT        style;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCSTR      lpszMenuName;
    LPCSTR      lpszClassName;

    HICON       hIconSm;
} ;

typedef WORD                ATOM;

ATOM __stdcall RegisterClassExA(const WNDCLASSEXA *);


typedef BOOL (__stdcall * DLGPROC)(HWND, UINT, WPARAM, LPARAM);

LRESULT __stdcall DefWindowProcA(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
BOOL __stdcall DestroyWindow(HWND hWnd);
int __stdcall DialogBoxParamA(HINSTANCE hInstance,LPCSTR lpTemplateName,HWND hWndParent,DLGPROC lpDialogFunc,LPARAM dwInitParam);

struct PAINTSTRUCT
{
    HDC         hdc;
    BOOL        fErase;
    RECT        rcPaint;
    BOOL        fRestore;
    BOOL        fIncUpdate;
//    BYTE        rgbReserved[32];
} ;

HDC __stdcall BeginPaint(HWND hWnd,PAINTSTRUCT *lpPaint);
BOOL __stdcall EndPaint(HWND hWnd,const PAINTSTRUCT *lpPaint);

BOOL __stdcall GetClientRect(HWND hWnd,LPRECT lpRect);

typedef DWORD   COLORREF;
COLORREF __stdcall SetPixel(HDC,int,int,COLORREF);

void __stdcall PostQuitMessage(int nExitCode);

BOOL __stdcall EndDialog(HWND hDlg,int nResult);

int __stdcall DrawTextA(HDC hDC,LPCSTR lpString,int nCount,LPRECT lpRect,UINT uFormat);

extern "C" {
void __cdecl __set_app_type(int);
int __cdecl getpid();
int __cdecl _getpid();
void __cdecl exit(int);
//__p__fmode
//__fpclear

struct _startupinfo
{
	int newmode;
} ;

void __cdecl __getmainargs(int *, char ***, char ***, int, _startupinfo *);
}

typedef HANDLE HMODULE;

HMODULE __stdcall GetModuleHandleA(LPCSTR lpModuleName);

void __stdcall GetStartupInfoA(LPSTARTUPINFOA lpStartupInfo);


int __stdcall LoadStringW(HINSTANCE hInstance, UINT uID, LPWSTR lpBuffer, int nBufferMax);

HWND __stdcall CreateWindowExW(
    DWORD dwExStyle,
    LPCWSTR lpClassName,
    LPCWSTR lpWindowName,
    DWORD dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    HWND hWndParent ,
    HMENU hMenu,
    HINSTANCE hInstance,
    LPVOID lpParam);
//------------


HACCEL __stdcall LoadAcceleratorsW(
    HINSTANCE hInstance,
    LPCWSTR lpTableName);


BOOL __stdcall GetMessageW(
    LPMSG lpMsg,
    HWND hWnd ,
    UINT wMsgFilterMin,
    UINT wMsgFilterMax);


BOOL __stdcall IsDialogMessageW(
    HWND hDlg,
    LPMSG lpMsg);


int __stdcall TranslateAcceleratorW(
    HWND hWnd,
    HACCEL hAccTable,
    LPMSG lpMsg);


BOOL __stdcall TranslateMessage(const MSG *lpMsg);


LONG __stdcall DispatchMessageW(const MSG *lpMsg);

HLOCAL __stdcall LocalFree(HLOCAL hMem);

