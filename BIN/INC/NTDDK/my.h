#define IN
#define OUT

#include "ntddk.h"
//#include "ntdef.h"
//#include "wdm.h"

NTSTATUS
__stdcall
DriverEntry(
    IN PDRIVER_OBJECT  DriverObject,
    IN PUNICODE_STRING RegistryPath
    );

int __cdecl sprintf(char *, const char *, ...);

void __stdcall KeAttachProcess(PEPROCESS pProcess);
void __stdcall KeDetachProcess();

