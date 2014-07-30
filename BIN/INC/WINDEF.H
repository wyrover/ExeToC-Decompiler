
typedef char *LPCSTR;
typedef BYTE * LPBYTE;
typedef HANDLE *PHANDLE;
typedef const void far      *LPCVOID;

struct RECT
{
    int    left;
    int    top;
    int    right;
    int    bottom;
} ;

typedef RECT * LPRECT;
typedef UINT WPARAM;
typedef long LPARAM;
typedef DWORD far           *LPDWORD;

struct POINT
{
    long  x;
    long  y;
} ;


//typedef LPSTR PTSTR, LPTSTR;
typedef LPSTR PTSTR;
typedef LPSTR LPTSTR;

typedef int                 INT;
