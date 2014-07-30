// Copyright(C) 1999-2005 LiuTaoTao£¬bookaa@rorsoft.com


//	exe2c project

#ifndef	FileLoad_H
#define FileLoad_H

enum enum_EXEType
{
	enum_PE_exe		= 1,
	enum_PE_dll		= 2,
	enum_PE_sys		= 3,
};

extern enum_EXEType g_EXEType;

#define PE_EXE 1
#define MZ_EXE 2
#define OS2_EXE 3
#define COM_EXE 5
#define NE_EXE 6
#define SYS_EXE 7
#define LE_EXE 8
#define BIN_EXE 9

struct MZHEADER
{
	WORD sig;
	WORD numbytes,numpages;
	WORD numrelocs,headersize;
	WORD minpara,maxpara;
	WORD initialss,initialsp;
	WORD csum;
	DWORD csip;
	WORD relocoffs;
	WORD ovlnum;
};

struct neheader
{
	WORD sig;
	WORD linkerver;
	WORD entryoffs,entrylen;
	DWORD filecrc;
	WORD contentflags;
	WORD dsnum;
	WORD heapsize,stacksize;
	DWORD csip,sssp;
	WORD numsegs,nummodules;
	WORD nonresnamesize;
	WORD offs_segments,offs_resources,offs_resnames,offs_module,offs_imports;
	DWORD nonresnametable;
	WORD movableentries;
	WORD shiftcount;
	WORD numresources;
	BYTE targetos,os_info;
	WORD fastloadoffs,fastloadlen;
	WORD mincodeswapareasize,winver;
};

struct nesegtable
{
	WORD sectoroffs;
	WORD seglength;
	WORD segflags;
	WORD minalloc;
};

struct nesegtablereloc
{
	BYTE reloctype,relocsort;
	WORD segm_offs;
	WORD index,indexoffs;
};

struct PEHEADER
{
	DWORD sigbytes;
	WORD cputype,objects;
	DWORD timedatestamp;
	DWORD reserveda[2];
	WORD nt_hdr_size,flags;
	WORD reserved;
	BYTE lmajor,lminor;
	DWORD reserved1[3];
	DWORD entrypoint_rva;
	DWORD reserved2[2];
	DWORD image_base;
	DWORD objectalign;
	DWORD filealign;
	WORD osmajor,osminor;
	WORD usermajor,userminor;
	WORD subsysmajor,subsysminor;
	DWORD reserved3;
	DWORD imagesize;
	DWORD headersize;
	DWORD filechecksum;
	WORD subsystem,dllflags;
	DWORD stackreserve,stackcommit;
	DWORD heapreserve,heapcommit;
	DWORD reserved4;
	DWORD numintitems;
	DWORD exporttable_rva,export_datasize;
	DWORD importtable_rva,import_datasize;
	DWORD resourcetable_rva,resource_datasize;
	DWORD exceptiontable_rva,exception_datasize;
	DWORD securitytable_rva,security_datasize;
	DWORD fixuptable_rva,fixup_datasize;
	DWORD debugtable_rva,debug_directory;
	DWORD imagedesc_rva,imagedesc_datasize;
	DWORD machspecific_rva,machspecific_datasize;
	DWORD tls_rva,tls_datasize;
};

struct PEObjData
{
	char name[8];
	DWORD virt_size,rva;
	DWORD phys_size,phys_offset;
	DWORD reserved[3],obj_flags;
};

struct peimportdirentry
{
	DWORD originalthunkrva;
	DWORD timedatestamp;
	DWORD forwarder;
	DWORD namerva;
	DWORD firstthunkrva;
};

struct peexportdirentry
{
	DWORD characteristics;
	DWORD timedatestamp;
	WORD majver,minver;
	DWORD namerva;
	DWORD base;
	DWORD numfunctions;
	DWORD numnames;
	DWORD funcaddrrva,nameaddrrva,ordsaddrrva;
};

struct perestable
{
	DWORD flags;
	DWORD timedatestamp;
	WORD majver,minver;
	WORD numnames,numids;
};

struct peleafnode
{
	DWORD datarva;
	DWORD size;
	DWORD codepage;
	DWORD reserved;
};

struct perestableentry
{
	DWORD id;
	DWORD offset;
};

struct perelocheader
{
	DWORD rva;
	DWORD len;
};

BOOL FAR PASCAL savemessbox(HWND hdwnd,UINT message,WPARAM wParam,LPARAM lParam);

//loads file and sets up objects using data.cpp
class FileLoader
{
private:
	int exetype;
	SECURITY_ATTRIBUTES securityatt;
	HANDLE efile;
	PBYTE fbuff;
	BYTE *rawdata;
	// added build 14 bugfix
	DWORD pdatarva;
    PBYTE	image_buf;
    DWORD	image_len;

public:
    PBYTE	entry_buf;
    ea_t	entry_offset;
    void GetEntrance(PBYTE& _entry_buf, ea_t& _entry_offset)
    {
        _entry_buf = entry_buf;
        _entry_offset = entry_offset;
    }

	FileLoader(void);
	~FileLoader(void);
	bool load(PCSTR fname);
	int getexetype(void);
	void setexetype(int etype);
	void savedb(char *fname,char *exename);
	BOOL loaddb(char *fname,char *exename);

private:
	void get_exetype();
	void	LoadPE(DWORD offs);
	void readcomfile(DWORD fsize);
	void readsysfile(DWORD fsize);
	void readpefile(DWORD offs);
	void readmzfile(DWORD fsize);
	void readlefile(void);
	void readnefile(DWORD offs);
	void reados2file(void);
	void readbinfile(DWORD fsize);
	void subdirsummary(BYTE *data,char *impname,DWORD image_base);
	void leaf2summary(BYTE *data,char *name,DWORD image_base);
	void leafnodesummary(BYTE *data,char *resname,DWORD image_base);
};
extern	FileLoader* g_FileLoader;

// basic class for lptr's - pointers comprised of a segment and offset.
// the intention is that addresses are well defined within Borg. So comparison
// operators exist in a well defined way. Addresses are not converted to 32 bit
// equivalents or whatever for this.
class lptr				  //Pointer Struct 32-bit.
{public:
	WORD segm;				 //segment
	DWORD offs;				 //offset

public:
	lptr(){};
	lptr(WORD seg,DWORD off);
	~lptr(){};
	void assign(WORD seg,DWORD off);
	BOOL operator==(lptr loc2);
	BOOL operator<=(lptr loc2);
	BOOL operator>=(lptr loc2);
	BOOL operator<(lptr loc2);
	BOOL operator>(lptr loc2);
	BOOL operator!=(lptr loc2);
	lptr operator+(DWORD offs2);
	lptr operator++(int x);
	lptr operator+=(DWORD offs2);
	lptr operator-(DWORD offs2);
	DWORD operator-(lptr loc2);
};

// predefined null pointer.
extern const lptr nlptr;

BOOL	if_valid_ea(ea_t ea);

#define GNAME_MAXLEN 40

#endif	//	FileLoad_H
