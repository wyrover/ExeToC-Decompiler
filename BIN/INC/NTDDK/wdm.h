#define IN
#define OUT
#define VOID void
#define CONST const

typedef NTSTATUS(__stdcall *PDRIVER_DISPATCH) ( DWORD, DWORD );

typedef void (__stdcall *PDRIVER_UNLOAD) (IN struct _DRIVER_OBJECT *DriverObject);

typedef NTSTATUS(__stdcall *PDRIVER_ADD_DEVICE) (struct _DRIVER_OBJECT *DriverObject,struct _DEVICE_OBJECT *PhysicalDeviceObject);

typedef struct _DRIVER_EXTENSION {
    struct _DRIVER_OBJECT *DriverObject;
    PDRIVER_ADD_DEVICE AddDevice;
    ULONG Count;
    UNICODE_STRING ServiceKeyName;
} DRIVER_EXTENSION, *PDRIVER_EXTENSION;

typedef void (__stdcall *PDRIVER_STARTIO) ( struct _DEVICE_OBJECT *DeviceObject, struct _IRP *Irp);

typedef struct _DRIVER_OBJECT {
    CSHORT Type;	//	0,2
    CSHORT Size;	//	2,2

    DWORD DeviceObject;//4,4	PDEVICE_OBJECT DeviceObject;
    ULONG Flags;		//	8,4

    PVOID DriverStart;	//	c,4
    ULONG DriverSize;	//	10,4
    PVOID DriverSection;	//	14,4
    PDRIVER_EXTENSION DriverExtension;	//	18,4

    UNICODE_STRING DriverName;	//	1c,8

    PUNICODE_STRING HardwareDatabase;	//24,4

    DWORD FastIoDispatch;//28,4	PFAST_IO_DISPATCH FastIoDispatch;

    DWORD DriverInit;//2c,4	PDRIVER_INITIALIZE DriverInit;
    PDRIVER_STARTIO DriverStartIo;	//	30,4
    PDRIVER_UNLOAD DriverUnload;	//	34,4
    //PDRIVER_DISPATCH MajorFunction[IRP_MJ_MAXIMUM_FUNCTION + 1];
	PDRIVER_DISPATCH MajorFunction[0x1c];	//38,?
	//DWORD MajorFunction[0x1c];

} DRIVER_OBJECT, *PDRIVER_OBJECT;

typedef struct _DISPATCHER_HEADER {
    UCHAR Type;
    UCHAR Absolute;
    UCHAR Size;
    UCHAR Inserted;
    LONG SignalState;
    LIST_ENTRY WaitListHead;
} DISPATCHER_HEADER;

typedef struct _KEVENT {
    DISPATCHER_HEADER Header;
} KEVENT, *PKEVENT, *PRKEVENT;

typedef unsigned char BOOLEAN;

typedef struct _IO_REMOVE_LOCK_COMMON_BLOCK {
    BOOLEAN     Removed;
    BOOLEAN     Reserved [3];
    LONG        IoCount;
    KEVENT      RemoveEvent;

} IO_REMOVE_LOCK_COMMON_BLOCK;


typedef struct _IO_REMOVE_LOCK {
    IO_REMOVE_LOCK_COMMON_BLOCK Common;
} IO_REMOVE_LOCK, *PIO_REMOVE_LOCK;

NTSTATUS __stdcall IoAcquireRemoveLockEx (PIO_REMOVE_LOCK RemoveLock, PVOID Tag, PCSTR File, ULONG Line, ULONG RemlockSize);

typedef DWORD ULONG_PTR;	//yes, its really DWORD

typedef ULONG_PTR SIZE_T, *PSIZE_T, *PULONG_PTR;

typedef struct _IO_STATUS_BLOCK {	//sizeof = 8
    //union {
        NTSTATUS Status;
    //    PVOID Pointer;
    //};

	ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef CCHAR KPROCESSOR_MODE;

typedef void (__stdcall *PDRIVER_CANCEL) ( struct _DEVICE_OBJECT *DeviceObject, struct _IRP *Irp);

typedef struct _MDL {
    struct _MDL *Next;		//+00
    CSHORT Size;			//+04
    CSHORT MdlFlags;		//+06
    struct _EPROCESS *Process;	//+08
    PVOID MappedSystemVa;		//+0c
    PVOID StartVa;
    ULONG ByteCount;
    ULONG ByteOffset;
} MDL, *PMDL;
typedef struct _LARGE_INTEGER {
	ULONG LowPart;
	LONG HighPart;
} LARGE_INTEGER;

typedef
VOID
(__stdcall *PKNORMAL_ROUTINE) (
    IN PVOID NormalContext,
    IN PVOID SystemArgument1,
    IN PVOID SystemArgument2
    );

typedef
VOID
(__stdcall *PKKERNEL_ROUTINE) (
    IN struct _KAPC *Apc,
    IN OUT PKNORMAL_ROUTINE *NormalRoutine,
    IN OUT PVOID *NormalContext,
    IN OUT PVOID *SystemArgument1,
    IN OUT PVOID *SystemArgument2
    );

typedef
VOID
(__stdcall *PKRUNDOWN_ROUTINE) (
    IN struct _KAPC *Apc
    );

typedef struct _KAPC {
    CSHORT Type;		//+00
    CSHORT Size;		//+02
    ULONG Spare0;		//+04
    struct _KTHREAD *Thread;	//+08
    LIST_ENTRY ApcListEntry;	//+0c
    PKKERNEL_ROUTINE KernelRoutine;		//+14
    PKRUNDOWN_ROUTINE RundownRoutine;	//+18
    PKNORMAL_ROUTINE NormalRoutine;		//+1c
    PVOID NormalContext;		//+20

    //
    // N.B. The following two members MUST be together.
    //

    PVOID SystemArgument1;		//+24
    PVOID SystemArgument2;		//+28
    CCHAR ApcStateIndex;		//+2c
    KPROCESSOR_MODE ApcMode;	//+2d
    BOOLEAN Inserted;			//+2e
	char	reserve;			//+2f	i add
} KAPC, *PKAPC;

typedef struct _FILE_OBJECT {
    CSHORT Type;
    CSHORT Size;
	/*
    PDEVICE_OBJECT DeviceObject;
    PVOID DoNotUse1;
    PVOID FsContext;
    PVOID FsContext2;
    PSECTION_OBJECT_POINTERS SectionObjectPointer;
    PVOID PrivateCacheMap;
    NTSTATUS FinalStatus;
    struct _FILE_OBJECT *RelatedFileObject;
    BOOLEAN LockOperation;
    BOOLEAN DeletePending;
    BOOLEAN ReadAccess;
    BOOLEAN WriteAccess;
    BOOLEAN DeleteAccess;
    BOOLEAN SharedRead;
    BOOLEAN SharedWrite;
    BOOLEAN SharedDelete;
    ULONG Flags;
    UNICODE_STRING FileName;
    LARGE_INTEGER CurrentByteOffset;
    ULONG Waiters;
    ULONG Busy;
    PVOID LastLock;
    KEVENT Lock;
    KEVENT Event;
    PIO_COMPLETION_CONTEXT CompletionContext;
	*/
} FILE_OBJECT;
typedef struct _FILE_OBJECT *PFILE_OBJECT;

/*
typedef struct _IRP {	//sizeof = 70h
    CSHORT Type;		//+00
    USHORT Size;		//+02
    PMDL MdlAddress;	//+04

    ULONG Flags;		//+08

    union {
        struct _IRP *MasterIrp;
        LONG IrpCount;	//+0c
        PVOID SystemBuffer;
    } AssociatedIrp;

    LIST_ENTRY ThreadListEntry;	//+10

    IO_STATUS_BLOCK IoStatus;	//+18h

    KPROCESSOR_MODE RequestorMode;	//+20

    BOOLEAN PendingReturned;	//+21

    CHAR StackCount;			//+22
    CHAR CurrentLocation;		//+23

    BOOLEAN Cancel;				//+24

    KIRQL CancelIrql;			//+25

    CCHAR ApcEnvironment;		//+26

    UCHAR AllocationFlags;		//+27
	
    PIO_STATUS_BLOCK UserIosb;	//+28
    PKEVENT UserEvent;			//+2c
    //union {
    //    struct {
    //        PIO_APC_ROUTINE UserApcRoutine;
    //        PVOID UserApcContext;
    //    } AsynchronousParameters;
        LARGE_INTEGER AllocationSize;	//+30
    //} Overlay;

    PDRIVER_CANCEL CancelRoutine;	//+38

    PVOID UserBuffer;				//+3c

    //PVOID CompletionKey;			//+40

	//PVOID DriverContext[4];			//+40
	//PETHREAD Thread;				//+50
	//PCHAR AuxiliaryBuffer;			//+54
	//LIST_ENTRY ListEntry;			//+58
	//ULONG PacketType;				//+60
		//60 Tail.Overlay.CurrentStackLocation
	//PFILE_OBJECT OriginalFileObject;//+64

	KAPC Apc;	//+40, sizeof = 30

} IRP, *PIRP;
*/

typedef
VOID
(__stdcall *PIO_APC_ROUTINE) (
    IN PVOID ApcContext,
    IN PIO_STATUS_BLOCK IoStatusBlock,
    IN ULONG Reserved
    );
typedef struct _KDEVICE_QUEUE_ENTRY {
    LIST_ENTRY DeviceListEntry;
    ULONG SortKey;
    BOOLEAN Inserted;
	char reserve1;
	char reserve2;
	char reserve3;
} KDEVICE_QUEUE_ENTRY, *PKDEVICE_QUEUE_ENTRY;

typedef struct _ETHREAD{} *PETHREAD;

typedef struct _IRP {
    CSHORT Type;
    USHORT Size;

    //
    // Define the common fields used to control the IRP.
    //

    //
    // Define a pointer to the Memory Descriptor List (MDL) for this I/O
    // request.  This field is only used if the I/O is "direct I/O".
    //

    PMDL MdlAddress;

    //
    // Flags word - used to remember various flags.
    //

    ULONG Flags;

    //
    // The following union is used for one of three purposes:
    //
    //    1. This IRP is an associated IRP.  The field is a pointer to a master
    //       IRP.
    //
    //    2. This is the master IRP.  The field is the count of the number of
    //       IRPs which must complete (associated IRPs) before the master can
    //       complete.
    //
    //    3. This operation is being buffered and the field is the address of
    //       the system space buffer.
    //

    union {
        struct _IRP *MasterIrp;
        LONG IrpCount;
        PVOID SystemBuffer;
    } AssociatedIrp;

    //
    // Thread list entry - allows queueing the IRP to the thread pending I/O
    // request packet list.
    //

    LIST_ENTRY ThreadListEntry;

    //
    // I/O status - final status of operation.
    //

    IO_STATUS_BLOCK IoStatus;

    //
    // Requestor mode - mode of the original requestor of this operation.
    //

    KPROCESSOR_MODE RequestorMode;

    //
    // Pending returned - TRUE if pending was initially returned as the
    // status for this packet.
    //

    BOOLEAN PendingReturned;

    //
    // Stack state information.
    //

    CHAR StackCount;
    CHAR CurrentLocation;

    //
    // Cancel - packet has been canceled.
    //

    BOOLEAN Cancel;

    //
    // Cancel Irql - Irql at which the cancel spinlock was acquired.
    //

    KIRQL CancelIrql;

    //
    // ApcEnvironment - Used to save the APC environment at the time that the
    // packet was initialized.
    //

    CCHAR ApcEnvironment;

    //
    // Allocation control flags.
    //

    UCHAR AllocationFlags;

    //
    // User parameters.
    //

    PIO_STATUS_BLOCK UserIosb;
    PKEVENT UserEvent;
    union {
        struct {
            PIO_APC_ROUTINE UserApcRoutine;
            PVOID UserApcContext;
        } AsynchronousParameters;
        LARGE_INTEGER AllocationSize;
    } Overlay;

    //
    // CancelRoutine - Used to contain the address of a cancel routine supplied
    // by a device driver when the IRP is in a cancelable state.
    //

    PDRIVER_CANCEL CancelRoutine;

    //
    // Note that the UserBuffer parameter is outside of the stack so that I/O
    // completion can copy data back into the user's address space without
    // having to know exactly which service was being invoked.  The length
    // of the copy is stored in the second half of the I/O status block. If
    // the UserBuffer field is NULL, then no copy is performed.
    //

    PVOID UserBuffer;

    //
    // Kernel structures
    //
    // The following section contains kernel structures which the IRP needs
    // in order to place various work information in kernel controller system
    // queues.  Because the size and alignment cannot be controlled, they are
    // placed here at the end so they just hang off and do not affect the
    // alignment of other fields in the IRP.
    //

    union {

        struct {

            union {

                //
                // DeviceQueueEntry - The device queue entry field is used to
                // queue the IRP to the device driver device queue.
                //

                KDEVICE_QUEUE_ENTRY DeviceQueueEntry;

                struct {

                    //
                    // The following are available to the driver to use in
                    // whatever manner is desired, while the driver owns the
                    // packet.
                    //

                    PVOID DriverContext[4];

                } ;

            } ;

            //
            // Thread - pointer to caller's Thread Control Block.
            //

            PETHREAD Thread;

            //
            // Auxiliary buffer - pointer to any auxiliary buffer that is
            // required to pass information to a driver that is not contained
            // in a normal buffer.
            //

            PCHAR AuxiliaryBuffer;

            //
            // The following unnamed structure must be exactly identical
            // to the unnamed structure used in the minipacket header used
            // for completion queue entries.
            //

            struct {

                //
                // List entry - used to queue the packet to completion queue, among
                // others.
                //

                LIST_ENTRY ListEntry;

                union {

                    //
                    // Current stack location - contains a pointer to the current
                    // IO_STACK_LOCATION structure in the IRP stack.  This field
                    // should never be directly accessed by drivers.  They should
                    // use the standard functions.
                    //

                    struct _IO_STACK_LOCATION *CurrentStackLocation;

                    //
                    // Minipacket type.
                    //

                    ULONG PacketType;
                };
            };

            //
            // Original file object - pointer to the original file object
            // that was used to open the file.  This field is owned by the
            // I/O system and should not be used by any other drivers.
            //

            PFILE_OBJECT OriginalFileObject;

        } Overlay;

        //
        // APC - This APC control block is used for the special kernel APC as
        // well as for the caller's APC, if one was specified in the original
        // argument list.  If so, then the APC is reused for the normal APC for
        // whatever mode the caller was in and the "special" routine that is
        // invoked before the APC gets control simply deallocates the IRP.
        //

        KAPC Apc;

        //
        // CompletionKey - This is the key that is used to distinguish
        // individual I/O operations initiated on a single file handle.
        //

        PVOID CompletionKey;

    } Tail;

} IRP, *PIRP;


//void IofCompleteRequest(PIRP Irp,CCHAR PriorityBoost);

typedef struct _IO_TIMER{} *PIO_TIMER;

#define DEVICE_TYPE ULONG

typedef ULONG_PTR KSPIN_LOCK;

typedef struct _KDEVICE_QUEUE {	//sizeof = 14h
    CSHORT Type;
    CSHORT Size;
    LIST_ENTRY DeviceListHead;
    KSPIN_LOCK Lock;
    BOOLEAN Busy;
} KDEVICE_QUEUE, *PKDEVICE_QUEUE;

typedef
VOID
(__stdcall *PKDEFERRED_ROUTINE) (
    IN struct _KDPC *Dpc,
    IN PVOID DeferredContext,
    IN PVOID SystemArgument1,
    IN PVOID SystemArgument2
    );

typedef struct _KDPC {	//sizeof = 20h
    CSHORT Type;
    UCHAR Number;
    UCHAR Importance;
    LIST_ENTRY DpcListEntry;
    PKDEFERRED_ROUTINE DeferredRoutine;
    PVOID DeferredContext;
    PVOID SystemArgument1;
    PVOID SystemArgument2;
    PULONG_PTR Lock;
} KDPC, *PKDPC;

typedef PVOID PSECURITY_DESCRIPTOR;


enum IO_ALLOCATION_ACTION
{
    KeepObject = 1,
    DeallocateObject,
    DeallocateObjectKeepRegisters
};

//
// Define device driver adapter/controller execution routine.
//

typedef
IO_ALLOCATION_ACTION
(__stdcall *PDRIVER_CONTROL) (
    IN struct _DEVICE_OBJECT *DeviceObject,
    IN struct _IRP *Irp,
    IN PVOID MapRegisterBase,
    IN PVOID Context
    );

typedef struct _WAIT_CONTEXT_BLOCK {  //sizeof = 28
    KDEVICE_QUEUE_ENTRY WaitQueueEntry;
    PDRIVER_CONTROL DeviceRoutine;
    PVOID DeviceContext;
    ULONG NumberOfMapRegisters;
    PVOID DeviceObject;
    PVOID CurrentIrp;
    PKDPC BufferChainingDpc;
} WAIT_CONTEXT_BLOCK, *PWAIT_CONTEXT_BLOCK;
//
// Volume Parameter Block (VPB)
//

#define MAXIMUM_VOLUME_LABEL_LENGTH  (32 * sizeof(WCHAR)) // 32 characters

typedef struct _VPB {
    CSHORT Type;
    CSHORT Size;
    USHORT Flags;
    USHORT VolumeLabelLength; // in bytes
    struct _DEVICE_OBJECT *DeviceObject;
    struct _DEVICE_OBJECT *RealDevice;
    ULONG SerialNumber;
    ULONG ReferenceCount;
    WCHAR VolumeLabel[32];	//[MAXIMUM_VOLUME_LABEL_LENGTH / sizeof(WCHAR)];
} VPB, *PVPB;

typedef struct _DEVICE_OBJECT {
    CSHORT Type;
    USHORT Size;
    LONG ReferenceCount;
    struct _DRIVER_OBJECT *DriverObject;
    struct _DEVICE_OBJECT *NextDevice;
    struct _DEVICE_OBJECT *AttachedDevice;
    struct _IRP *CurrentIrp;
    PIO_TIMER Timer;
    ULONG Flags;                                // See above:  DO_...
    ULONG Characteristics;                      // See ntioapi:  FILE_...
    PVPB Vpb;
    PVOID DeviceExtension;
    DEVICE_TYPE DeviceType;
    CCHAR StackSize;
	char reserve1;
	char reserve2;
	char reserve3;
    union {
        LIST_ENTRY ListEntry;
        WAIT_CONTEXT_BLOCK Wcb;
    } Queue;
    ULONG AlignmentRequirement;
    KDEVICE_QUEUE DeviceQueue;
    KDPC Dpc;

    //
    //  The following field is for exclusive use by the filesystem to keep
    //  track of the number of Fsp threads currently using the device
    //

    ULONG ActiveThreadCount;
    PSECURITY_DESCRIPTOR SecurityDescriptor;
    KEVENT DeviceLock;

    USHORT SectorSize;
    USHORT Spare1;

    struct _DEVOBJ_EXTENSION  *DeviceObjectExtension;
    PVOID  Reserved;
} DEVICE_OBJECT;
typedef struct _DEVICE_OBJECT *PDEVICE_OBJECT; // ntndis
/*
typedef struct _DEVICE_OBJECT {		//sizeof = b8
    CSHORT Type;		//00
    USHORT Size;		//02
    LONG ReferenceCount;		//+04
    struct _DRIVER_OBJECT *DriverObject;	//+08
    struct _DEVICE_OBJECT *NextDevice;		//+0c
    struct _DEVICE_OBJECT *AttachedDevice;	//+10
    struct _IRP *CurrentIrp;				//+14
    PIO_TIMER Timer;						//+18
    ULONG Flags;                //+1c              // See above:  DO_...
    ULONG Characteristics;                      // See ntioapi:  FILE_...
    PVOID DoNotUse1;
    PVOID DeviceExtension;		//+28h
    DEVICE_TYPE DeviceType;		//+2c
    CCHAR StackSize;			//+30
	char reserve1;
	char reserve2;
	char reserve3;
    //union {
	struct {		//	临时改一下
    //    LIST_ENTRY ListEntry;
        WAIT_CONTEXT_BLOCK Wcb;		//34
    } Queue;
    ULONG AlignmentRequirement;		//5c
    KDEVICE_QUEUE DeviceQueue;		//60
    KDPC Dpc;						//74

    ULONG ActiveThreadCount;		//94
    PSECURITY_DESCRIPTOR SecurityDescriptor;
    KEVENT DeviceLock;

    USHORT SectorSize;
    USHORT Spare1;

    struct _DEVOBJ_EXTENSION  *DeviceObjectExtension;
    PVOID  Reserved;
} DEVICE_OBJECT, * PDEVICE_OBJECT;
*/

NTSTATUS IofCallDriver(PDEVICE_OBJECT DeviceObject, PIRP Irp);

void IoReleaseRemoveLockAndWaitEx(PIO_REMOVE_LOCK RemoveLock,PVOID Tag, ULONG RemlockSize );


void __stdcall RtlInitUnicodeString(PUNICODE_STRING DestinationString,PCWSTR SourceString);

void __stdcall IoDetachDevice( PDEVICE_OBJECT TargetDevice);

enum EVENT_TYPE
{
    NotificationEvent,
    SynchronizationEvent
} ;

void __stdcall KeInitializeEvent ( PRKEVENT Event, EVENT_TYPE Type, BOOLEAN State);


void __stdcall IoReleaseRemoveLockEx(PIO_REMOVE_LOCK RemoveLock, PVOID Tag, ULONG  RemlockSize );

NTSTATUS __stdcall IoDeleteSymbolicLink(PUNICODE_STRING SymbolicLinkName);

void __stdcall IoDeleteDevice( PDEVICE_OBJECT DeviceObject);

enum KWAIT_REASON
{
    Executive,
    FreePage,
    PageIn,
    PoolAllocation,
    DelayExecution,
    Suspended,
    UserRequest,
    WrExecutive,
    WrFreePage,
    WrPageIn,
    WrPoolAllocation,
    WrDelayExecution,
    WrSuspended,
    WrUserRequest,
    WrEventPair,
    WrQueue,
    WrLpcReceive,
    WrLpcReply,
    WrVirtualMemory,
    WrPageOut,
    WrRendezvous,
    Spare2,
    Spare3,
    Spare4,
    Spare5,
    Spare6,
    WrKernel,
    MaximumWaitReason
};

typedef LONG KPRIORITY;

PKEVENT __stdcall IoCreateSynchronizationEvent(PUNICODE_STRING EventName, PHANDLE EventHandle);
LONG __stdcall KeSetEvent (PRKEVENT Event, KPRIORITY Increment, BOOLEAN Wait);

typedef struct _EPROCESS{} *PEPROCESS;;
void __stdcall KeAttachProcess(PEPROCESS pProcess);
void __stdcall KeDetachProcess();


void __stdcall IoStartPacket( PDEVICE_OBJECT DeviceObject, PIRP Irp, PULONG Key, PDRIVER_CANCEL CancelFunction );

void __stdcall IoSetHardErrorOrVerifyDevice( PIRP Irp, PDEVICE_OBJECT DeviceObject);

NTSTATUS __stdcall ZwClose( HANDLE Handle);
void __stdcall MmUnmapIoSpace ( PVOID BaseAddress, SIZE_T NumberOfBytes);






typedef LARGE_INTEGER *PLARGE_INTEGER;

NTSTATUS __stdcall KeWaitForSingleObject ( PVOID Object, KWAIT_REASON WaitReason, KPROCESSOR_MODE WaitMode, BOOLEAN Alertable, PLARGE_INTEGER Timeout );

NTSTATUS __stdcall ZwReadFile( HANDLE FileHandle, HANDLE Event , PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext,PIO_STATUS_BLOCK IoStatusBlock,PVOID Buffer,ULONG Length,PLARGE_INTEGER ByteOffset,PULONG Key);



PVOID __stdcall MmMapLockedPages (PMDL MemoryDescriptorList, KPROCESSOR_MODE AccessMode);

void __fastcall IofCompleteRequest(PIRP Irp, CCHAR PriorityBoost);

PEPROCESS __stdcall IoGetCurrentProcess();


enum POOL_TYPE
{
    NonPagedPool,
    PagedPool,
    NonPagedPoolMustSucceed,
    DontUseThisType,
    NonPagedPoolCacheAligned,
    PagedPoolCacheAligned,
    NonPagedPoolCacheAlignedMustS,
    MaxPoolType
} ;

PVOID __stdcall ExAllocatePoolWithTag(POOL_TYPE PoolType, SIZE_T NumberOfBytes, ULONG Tag);

int     __cdecl _stricmp(const char *, const char *);

typedef ULONG ACCESS_MASK;
typedef ACCESS_MASK *PACCESS_MASK;
typedef struct _OBJECT_ATTRIBUTES {
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
    PVOID SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
} OBJECT_ATTRIBUTES;
typedef OBJECT_ATTRIBUTES *POBJECT_ATTRIBUTES;

NTSTATUS __stdcall ZwCreateFile(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength);

typedef struct _STRING {
    USHORT Length;
    USHORT MaximumLength;
    PCHAR Buffer;
} STRING;
typedef STRING *PSTRING;

typedef STRING ANSI_STRING;
typedef PSTRING PANSI_STRING;

typedef STRING OEM_STRING;
typedef PSTRING POEM_STRING;

NTSTATUS __stdcall RtlAnsiStringToUnicodeString(PUNICODE_STRING DestinationString, PANSI_STRING SourceString, BOOLEAN AllocateDestinationString);

void __stdcall RtlInitString(PSTRING DestinationString, PSTR SourceString);

void __stdcall ExFreePool(PVOID P);

void __stdcall RtlFreeUnicodeString(PUNICODE_STRING UnicodeString);

void __stdcall KeClearEvent (PRKEVENT Event);

int __cdecl sprintf(char *, const char *, ...);

void __stdcall IoDeleteDevice(PDEVICE_OBJECT DeviceObject);

typedef struct _KTHREAD
{
}*PKTHREAD;

PKTHREAD __stdcall KeGetCurrentThread();

typedef struct _KSEMAPHORE {
    DISPATCHER_HEADER Header;
    LONG Limit;
} KSEMAPHORE, *PKSEMAPHORE;

typedef ULONG_PTR ERESOURCE_THREAD;
typedef ERESOURCE_THREAD *PERESOURCE_THREAD;

typedef struct _OWNER_ENTRY {
    ERESOURCE_THREAD OwnerThread;
//	union {
		LONG OwnerCount;
//        ULONG TableSize;
//    };

} OWNER_ENTRY, *POWNER_ENTRY;

typedef KSPIN_LOCK *PKSPIN_LOCK;

typedef struct _ERESOURCE {
    LIST_ENTRY SystemResourcesList;
    POWNER_ENTRY OwnerTable;
    SHORT ActiveCount;
    USHORT Flag;
    PKSEMAPHORE SharedWaiters;
    PKEVENT ExclusiveWaiters;
    OWNER_ENTRY OwnerThreads[2];
    ULONG ContentionCount;
    USHORT NumberOfSharedWaiters;
    USHORT NumberOfExclusiveWaiters;
//    union {
        PVOID Address;
        //ULONG_PTR CreatorBackTraceIndex;
    //};

    KSPIN_LOCK SpinLock;
} ERESOURCE, *PERESOURCE;

BOOLEAN __stdcall ExAcquireResourceExclusiveLite(PERESOURCE Resource, BOOLEAN Wait);

void __stdcall ExReleaseResourceForThreadLite(PERESOURCE Resource, ERESOURCE_THREAD ResourceThreadId);

void __stdcall IoStartNextPacket(PDEVICE_OBJECT DeviceObject, BOOLEAN Cancelable);

NTSTATUS __stdcall KeWaitForSingleObject (PVOID Object, DWORD WaitReason, KPROCESSOR_MODE WaitMode, BOOLEAN Alertable, PLARGE_INTEGER Timeout);

typedef void (__stdcall *PWORKER_THREAD_ROUTINE)(PVOID Parameter);

typedef struct _WORK_QUEUE_ITEM {
    LIST_ENTRY List;
    PWORKER_THREAD_ROUTINE WorkerRoutine;
    PVOID Parameter;
} WORK_QUEUE_ITEM, *PWORK_QUEUE_ITEM;

void __stdcall ExQueueWorkItem(PWORK_QUEUE_ITEM WorkItem, DWORD QueueType);

void __stdcall KeInitializeEvent (PRKEVENT Event, DWORD Type, BOOLEAN State);

void *  __cdecl memmove(void *, const void *, int);

NTSTATUS __stdcall ExInitializeResourceLite(PERESOURCE Resource);

void __stdcall IoStartTimer(PDEVICE_OBJECT DeviceObject);

typedef void (__stdcall *PIO_TIMER_ROUTINE) (struct _DEVICE_OBJECT *DeviceObject, PVOID Context);

NTSTATUS __stdcall IoInitializeTimer(PDEVICE_OBJECT DeviceObject, PIO_TIMER_ROUTINE TimerRoutine, PVOID Context);

NTSTATUS __stdcall IoCreateSymbolicLink(PUNICODE_STRING SymbolicLinkName, PUNICODE_STRING DeviceName);

NTSTATUS __stdcall IoCreateDevice(PDRIVER_OBJECT DriverObject, ULONG DeviceExtensionSize, PUNICODE_STRING DeviceName, ULONG DeviceType, ULONG DeviceCharacteristics, BOOLEAN Reserved, PDEVICE_OBJECT *DeviceObject);

typedef struct _CONFIGURATION_INFORMATION {

    //
    // This field indicates the total number of disks in the system.  This
    // number should be used by the driver to determine the name of new
    // disks.  This field should be updated by the driver as it finds new
    // disks.
    //

    ULONG DiskCount;                // Count of hard disks thus far
    ULONG FloppyCount;              // Count of floppy disks thus far
    ULONG CdRomCount;               // Count of CD-ROM drives thus far
    ULONG TapeCount;                // Count of tape drives thus far
    ULONG ScsiPortCount;            // Count of SCSI port adapters thus far
    ULONG SerialCount;              // Count of serial devices thus far
    ULONG ParallelCount;            // Count of parallel devices thus far

    //
    // These next two fields indicate ownership of one of the two IO address
    // spaces that are used by WD1003-compatable disk controllers.
    //

    BOOLEAN AtDiskPrimaryAddressClaimed;    // 0x1F0 - 0x1FF
    BOOLEAN AtDiskSecondaryAddressClaimed;  // 0x170 - 0x17F

    //
    // Indicates the structure version, as anything value belong this will have been added.
    // Use the structure size as the version.
    //

    ULONG Version;

    //
    // Indicates the total number of medium changer devices in the system.
    // This field will be updated by the drivers as it determines that
    // new devices have been found and will be supported.
    //

    ULONG MediumChangerCount;

} CONFIGURATION_INFORMATION, *PCONFIGURATION_INFORMATION;

PCONFIGURATION_INFORMATION __stdcall IoGetConfigurationInformation();



NTSTATUS __stdcall PoCallDriver ( PDEVICE_OBJECT DeviceObject, PIRP Irp);

void __stdcall PoStartNextPowerIrp( PIRP    Irp);

PDEVICE_OBJECT __stdcall IoAttachDeviceToDeviceStack( PDEVICE_OBJECT SourceDevice, PDEVICE_OBJECT TargetDevice);

void __stdcall IoInitializeRemoveLockEx( PIO_REMOVE_LOCK Lock, ULONG AllocateTag, ULONG MaxLockedMinutes, ULONG HighWatermark, ULONG RemlockSize );

UCHAR __stdcall READ_REGISTER_UCHAR(PUCHAR  Register);

USHORT __stdcall READ_REGISTER_USHORT(PUSHORT Register);

ULONG __stdcall READ_REGISTER_ULONG(PULONG  Register);

void __stdcall WRITE_REGISTER_UCHAR(PUCHAR  Register,UCHAR   Value);

void __stdcall WRITE_REGISTER_USHORT(PUSHORT Register,USHORT  Value);

void __stdcall WRITE_REGISTER_ULONG(PULONG  Register,ULONG   Value);

void __stdcall WRITE_PORT_UCHAR(PUCHAR  Port,UCHAR   Value);

void __stdcall WRITE_PORT_USHORT(PUSHORT Port,USHORT  Value);

void __stdcall WRITE_PORT_ULONG(PULONG  Port,ULONG   Value);

UCHAR __stdcall READ_PORT_UCHAR(PUCHAR  Port);

USHORT __stdcall READ_PORT_USHORT(PUSHORT Port);

ULONG __stdcall READ_PORT_ULONG(PULONG  Port);

enum MEMORY_CACHING_TYPE {
    MmNonCached = 0,
    MmCached = 1,
    MmWriteCombined = MmFrameBufferCached,
    MmHardwareCoherentCached,
    MmCachingTypeDoNotUse1,
    MmCachingTypeDoNotUse2,
    MmMaximumCacheType
};

//#define PHYSICAL_ADDRESS LARGE_INTEGER
//PVOID __stdcall MmMapIoSpace (PHYSICAL_ADDRESS PhysicalAddress, SIZE_T NumberOfBytes, MEMORY_CACHING_TYPE CacheType);
PVOID __stdcall MmMapIoSpace (LARGE_INTEGER PhysicalAddress, SIZE_T NumberOfBytes, MEMORY_CACHING_TYPE CacheType);


NTSTATUS
__stdcall
DriverEntry(
    IN PDRIVER_OBJECT  DriverObject,
    IN PUNICODE_STRING RegistryPath
    );

ULONG __cdecl DbgPrint(char * Format, ...);

void __stdcall ObOpenObjectByPointer(DWORD d1,DWORD d2,DWORD d3,DWORD d4,DWORD d5,DWORD d6,DWORD d7);

long __fastcall InterlockedExchange(PLONG Target,LONG Value);


typedef struct _SECURITY_QUALITY_OF_SERVICE *PSECURITY_QUALITY_OF_SERVICE;
typedef struct _ACCESS_STATE *PACCESS_STATE;

typedef struct _IO_SECURITY_CONTEXT {
    PSECURITY_QUALITY_OF_SERVICE SecurityQos;
    PACCESS_STATE AccessState;
    ACCESS_MASK DesiredAccess;
    ULONG FullCreateOptions;
} IO_SECURITY_CONTEXT, *PIO_SECURITY_CONTEXT;

enum FILE_INFORMATION_CLASS {
    FileBasicInformation = 4,
    FileStandardInformation = 5,
    FilePositionInformation = 14,
    FileEndOfFileInformation = 20,
} ;
enum FS_INFORMATION_CLASS {
    FileFsVolumeInformation       = 1,
    FileFsLabelInformation,      // 2
    FileFsSizeInformation,       // 3
    FileFsDeviceInformation,     // 4
    FileFsAttributeInformation,  // 5
    FileFsControlInformation,    // 6
    FileFsFullSizeInformation,   // 7
    FileFsObjectIdInformation,   // 8
    FileFsMaximumInformation
} ;

enum DEVICE_RELATION_TYPE {
    BusRelations,
    EjectionRelations,
    PowerRelations,
    RemovalRelations,
    TargetDeviceRelation
} ;
typedef VOID (__stdcall *PINTERFACE_REFERENCE)(PVOID Context);
typedef VOID (__stdcall *PINTERFACE_DEREFERENCE)(PVOID Context);

typedef struct _INTERFACE {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    // interface specific entries go here
} INTERFACE, *PINTERFACE;

typedef
NTSTATUS
(__stdcall *PIO_COMPLETION_ROUTINE) (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp,
    IN PVOID Context
    );

typedef struct _GUID {
	ULONG   Data1;
	USHORT  Data2;
	USHORT  Data3;
	UCHAR   Data4[8];
} GUID;

typedef struct _IO_STACK_LOCATION {
    UCHAR MajorFunction;
    UCHAR MinorFunction;
    UCHAR Flags;
    UCHAR Control;

    //
    // The following user parameters are based on the service that is being
    // invoked.  Drivers and file systems can determine which set to use based
    // on the above major and minor function codes.
    //

    union {

        //
        // System service parameters for:  NtCreateFile
        //

        struct {
            PIO_SECURITY_CONTEXT SecurityContext;
            ULONG Options;
            USHORT  FileAttributes;
            USHORT ShareAccess;
            ULONG  EaLength;
        } Create;


        //
        // System service parameters for:  NtReadFile
        //

        struct {
            ULONG Length;
            ULONG  Key;
            LARGE_INTEGER ByteOffset;
        } Read;

        //
        // System service parameters for:  NtWriteFile
        //

        struct {
            ULONG Length;
            ULONG  Key;
            LARGE_INTEGER ByteOffset;
        } Write;


        //
        // System service parameters for:  NtQueryInformationFile
        //

        struct {
            ULONG Length;
            FILE_INFORMATION_CLASS FileInformationClass;
        } QueryFile;

        //
        // System service parameters for:  NtSetInformationFile
        //

        struct {
            ULONG Length;
            FILE_INFORMATION_CLASS FileInformationClass;
            PFILE_OBJECT FileObject;
            union {
                struct {
                    BOOLEAN ReplaceIfExists;
                    BOOLEAN AdvanceOnly;
                };
                ULONG ClusterCount;
                HANDLE DeleteHandle;
            };
        } SetFile;


        //
        // System service parameters for:  NtQueryVolumeInformationFile
        //

        struct {
            ULONG Length;
            FS_INFORMATION_CLASS FsInformationClass;
        } QueryVolume;


        //
        // System service parameters for:  NtFlushBuffersFile
        //
        // No extra user-supplied parameters.
        //


        //
        // System service parameters for:  NtDeviceIoControlFile
        //
        // Note that the user's output buffer is stored in the UserBuffer field
        // and the user's input buffer is stored in the SystemBuffer field.
        //

        struct {
            ULONG OutputBufferLength;
            ULONG InputBufferLength;
            ULONG IoControlCode;
            PVOID Type3InputBuffer;
        } DeviceIoControl;

        //
        // Non-system service parameters.
        //
        // Parameters for MountVolume
        //

        struct {
            PVOID DoNotUse1;
            PDEVICE_OBJECT DeviceObject;
        } MountVolume;

        //
        // Parameters for VerifyVolume
        //

        struct {
            PVOID DoNotUse1;
            PDEVICE_OBJECT DeviceObject;
        } VerifyVolume;

        //
        // Parameters for Scsi with internal device contorl.
        //

        struct {
            struct _SCSI_REQUEST_BLOCK *Srb;
        } Scsi;


        //
        // Parameters for IRP_MN_QUERY_DEVICE_RELATIONS
        //

        struct {
            DEVICE_RELATION_TYPE Type;
        } QueryDeviceRelations;

        //
        // Parameters for IRP_MN_QUERY_INTERFACE
        //

        struct {
            CONST GUID *InterfaceType;
            USHORT Size;
            USHORT Version;
            PINTERFACE Interface;
            PVOID InterfaceSpecificData;
        } QueryInterface;



        //
        // Parameters for IRP_MN_QUERY_CAPABILITIES
        //

        //struct {
        //    PDEVICE_CAPABILITIES Capabilities;
        //} DeviceCapabilities;

        //
        // Parameters for IRP_MN_FILTER_RESOURCE_REQUIREMENTS
        //

        //struct {
        //    PIO_RESOURCE_REQUIREMENTS_LIST IoResourceRequirementList;
        //} FilterResourceRequirements;

        //
        // Parameters for IRP_MN_READ_CONFIG and IRP_MN_WRITE_CONFIG
        //

        struct {
            ULONG WhichSpace;
            PVOID Buffer;
            ULONG Offset;
            ULONG Length;
        } ReadWriteConfig;

        //
        // Parameters for IRP_MN_SET_LOCK
        //

        struct {
            BOOLEAN Lock;
        } SetLock;

        //
        // Parameters for IRP_MN_QUERY_ID
        //

        //struct {
        //    BUS_QUERY_ID_TYPE IdType;
        //} QueryId;

        //
        // Parameters for IRP_MN_QUERY_DEVICE_TEXT
        //

        //struct {
        //    DEVICE_TEXT_TYPE DeviceTextType;
        //    LCID POINTER_ALIGNMENT LocaleId;
        //} QueryDeviceText;

        //
        // Parameters for IRP_MN_DEVICE_USAGE_NOTIFICATION
        //

        //struct {
        //    BOOLEAN InPath;
        //    BOOLEAN Reserved[3];
        //    DEVICE_USAGE_NOTIFICATION_TYPE  Type;
        //} UsageNotification;

        //
        // Parameters for IRP_MN_WAIT_WAKE
        //

        //struct {
        //    SYSTEM_POWER_STATE PowerState;
        //} WaitWake;

        //
        // Parameter for IRP_MN_POWER_SEQUENCE
        //

        //struct {
        //    PPOWER_SEQUENCE PowerSequence;
        //} PowerSequence;

        //
        // Parameters for IRP_MN_SET_POWER and IRP_MN_QUERY_POWER
        //

        //struct {
        //    ULONG SystemContext;
        //    POWER_STATE_TYPE POINTER_ALIGNMENT Type;
        //    POWER_STATE POINTER_ALIGNMENT State;
        //    POWER_ACTION POINTER_ALIGNMENT ShutdownType;
        //} Power;

        //
        // Parameters for StartDevice
        //

        //struct {
        //    PCM_RESOURCE_LIST AllocatedResources;
        //    PCM_RESOURCE_LIST AllocatedResourcesTranslated;
        //} StartDevice;


        //
        // Parameters for Cleanup
        //
        // No extra parameters supplied
        //

        //
        // WMI Irps
        //

        //struct {
        //    ULONG_PTR ProviderId;
        //    PVOID DataPath;
        //    ULONG BufferSize;
        //    PVOID Buffer;
        //} WMI;

        //
        // Others - driver-specific
        //

        struct {
            PVOID Argument1;
            PVOID Argument2;
            PVOID Argument3;
            PVOID Argument4;
        } Others;

    } Parameters;

    //
    // Save a pointer to this device driver's device object for this request
    // so it can be passed to the completion routine if needed.
    //

    PDEVICE_OBJECT DeviceObject;

    //
    // The following location contains a pointer to the file object for this
    //

    PFILE_OBJECT FileObject;

    //
    // The following routine is invoked depending on the flags in the above
    // flags field.
    //

    PIO_COMPLETION_ROUTINE CompletionRoutine;

    //
    // The following is used to store the address of the context parameter
    // that should be passed to the CompletionRoutine.
    //

    PVOID Context;

} IO_STACK_LOCATION, *PIO_STACK_LOCATION;

