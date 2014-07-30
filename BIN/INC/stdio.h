//	stdio.h for exe2c

extern "C" {
int __cdecl printf(const char *, ...);
char * __cdecl strchr(char *, char);
        void *  __cdecl memcpy(void *, const void *, size_t);
        int     __cdecl memcmp(const void *, const void *, size_t);
        void *  __cdecl memset(void *, int, size_t);
        char *  __cdecl _strset(char *, int);
        char *  __cdecl strcpy(char *, const char *);
        char *  __cdecl strcat(char *, const char *);
        int     __cdecl strcmp(const char *, const char *);
        size_t  __cdecl strlen(const char *);

 int __cdecl _chdir(const char *);
 char * __cdecl _getcwd(char *, int);
 int __cdecl _mkdir(const char *);
 int __cdecl _rmdir(const char *);


 char * __cdecl _fullpath(char *, const char *, size_t);

 void   __cdecl _splitpath(const char *, char *, char *, char *, char *);
 void   __cdecl _makepath(char *, const char *, const char *, const char *, const char *);

// long __cdecl _findfirst(const char *, struct _finddata_t *);
// int __cdecl _findnext(long, struct _finddata_t *);
 long __cdecl _findfirst(const char *, DWORD *);
 int __cdecl _findnext(long, DWORD *);
 int __cdecl _findclose(long);

// void * __cdecl memccpy(void *, const void *, int, unsigned int);
// int __cdecl memicmp(const void *, const void *, unsigned int);
 void * __cdecl memccpy(void *, const void *, int, DWORD);
 int __cdecl memicmp(const void *, const void *, DWORD);
 int __cdecl strcmpi(const char *, const char *);
 int __cdecl stricmp(const char *, const char *);
 char * __cdecl strdup(const char *);
 char * __cdecl strlwr(char *);
 int __cdecl strnicmp(const char *, const char *, size_t);
 char * __cdecl strnset(char *, int, size_t);
 char * __cdecl strrev(char *);
 char * __cdecl strset(char *, int);
 char * __cdecl strupr(char *);

 char *  __cdecl strchr(const char *, int);
 int     __cdecl _strcmpi(const char *, const char *);
 int     __cdecl _stricmp(const char *, const char *);
 int     __cdecl strcoll(const char *, const char *);
 int     __cdecl _stricoll(const char *, const char *);
 int     __cdecl _strncoll(const char *, const char *, size_t);
 int     __cdecl _strnicoll(const char *, const char *, size_t);
 size_t  __cdecl strcspn(const char *, const char *);
 char *  __cdecl _strdup(const char *);
 char *  __cdecl _strerror(const char *);
 char *  __cdecl strerror(int);
 char *  __cdecl _strlwr(char *);
 char *  __cdecl strncat(char *, const char *, size_t);
 int     __cdecl strncmp(const char *, const char *, size_t);
 int     __cdecl _strnicmp(const char *, const char *, size_t);
 char *  __cdecl strncpy(char *, const char *, size_t);
 char *  __cdecl _strnset(char *, int, size_t);
 char *  __cdecl strpbrk(const char *, const char *);
 char *  __cdecl strrchr(const char *, int);
 char *  __cdecl _strrev(char *);
 size_t  __cdecl strspn(const char *, const char *);
 char *  __cdecl strstr(const char *, const char *);
 char *  __cdecl strtok(char *, const char *);
 char *  __cdecl _strupr(char *);
 size_t  __cdecl strxfrm (char *, const char *, size_t);

}	//extern "C"

