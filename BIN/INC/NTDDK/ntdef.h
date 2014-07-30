typedef char CHAR;
typedef short SHORT;
typedef long LONG;

typedef CHAR *PCHAR;
typedef CHAR *LPCH, *PCH;

typedef const CHAR *LPCCH, *PCCH;
typedef CHAR *NPSTR;
typedef CHAR *LPSTR, *PSTR;
typedef const CHAR *LPCSTR, *PCSTR;

typedef char CCHAR;          // winnt


typedef long NTSTATUS;

typedef void *PVOID;
typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned long ULONG;
typedef short CSHORT;

typedef UCHAR *PUCHAR;
typedef USHORT *PUSHORT;
typedef ULONG *PULONG;

typedef SHORT *PSHORT;  // winnt
typedef LONG *PLONG;    // winnt

typedef PVOID HANDLE;
typedef HANDLE *PHANDLE;

typedef UCHAR KIRQL;

typedef unsigned short wchar_t;
typedef unsigned short WCHAR;

typedef WCHAR *LPWSTR, *PWSTR;
typedef const WCHAR *LPCWSTR, *PCWSTR;

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;


//typedef __int64 LONGLONG;

typedef struct _LIST_ENTRY {
   struct _LIST_ENTRY *Flink;
   struct _LIST_ENTRY *Blink;
} LIST_ENTRY, *PLIST_ENTRY, *PRLIST_ENTRY;


