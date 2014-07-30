//      WinSock2.h

typedef unsigned int    SOCKET;
typedef unsigned short  u_short;

#define WSADESCRIPTION_LEN      256
#define WSASYS_STATUS_LEN       128

typedef struct WSAData {
        WORD                    wVersion;
        WORD                    wHighVersion;
        char                    szDescription[257];		//[WSADESCRIPTION_LEN+1];
        char                    szSystemStatus[129];	//[WSASYS_STATUS_LEN+1];
        unsigned short          iMaxSockets;
        unsigned short          iMaxUdpDg;
        char FAR *              lpVendorInfo;
} WSADATA, FAR * LPWSADATA;

struct sockaddr {
        u_short sa_family;              /* address family */
        char    sa_data[14];            /* up to 14 bytes of direct address */
};

int     __stdcall WSAStartup(WORD wVersionRequested,LPWSADATA lpWSAData);
SOCKET  __stdcall accept(SOCKET s, sockaddr *addr,int *addrlen);
int     __stdcall bind(SOCKET s,const sockaddr *name,int namelen);
int     __stdcall listen(SOCKET s,int backlog);
int     __stdcall recv(SOCKET s,char *buf,int len,int flags);
int     __stdcall send(SOCKET s,const char *buf,int len,int flags);
SOCKET  __stdcall socket(int af,int type,int protocol);


