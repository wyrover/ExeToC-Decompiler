// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com


//	exe2c project

#include "stdafx.h"
#include "00000.h"
#include "FileLoad.h"

#define	SEG0	0x1000
#define	Load_Resources	0
#define	Load_Debug	0
#define	Load_Data	1

enum_EXEType g_EXEType = (enum_EXEType)0;

FileLoader* g_FileLoader = NULL;

FileLoader::FileLoader(void)
{
	securityatt.nLength=sizeof(SECURITY_ATTRIBUTES);
	securityatt.lpSecurityDescriptor=NULL;
	securityatt.bInheritHandle=FALSE;
	efile=INVALID_HANDLE_VALUE;
	exetype=0;
	fbuff=NULL;
}

FileLoader::~FileLoader(void)
{
	if ( fbuff!=NULL )
		delete fbuff;
	CloseHandle(efile);

	VirtualFree(image_buf,image_len,0);
}

BOOL	if_valid_ea(ea_t ea)
{
	switch (g_EXEType)
	{
	case enum_PE_sys:
		return TRUE;
	case enum_PE_exe:
		if (ea < 0x400000)
			return FALSE;
		return TRUE;
	}
	return TRUE;
}
void FileLoader::get_exetype()
{
	char mzhead[2],exthead[2];
	DWORD num;
	DWORD pe_offset;

	exetype = 0;
	if ( !ReadFile(efile,mzhead,2,&num,NULL) )
		return;
	
	if (num != 2)
		return;
	if (((mzhead[0]=='M')&&(mzhead[1]=='Z'))
		||((mzhead[0]=='Z')&&(mzhead[1]=='M')))
	{
		exetype = BIN_EXE;

		SetFilePointer(efile,0x3c,NULL,FILE_BEGIN);
		if ( ReadFile(efile,&pe_offset,4,&num,NULL) )
			SetFilePointer(efile,pe_offset,NULL,FILE_BEGIN);
		if ( ReadFile(efile,exthead,2,&num,NULL) )
		{
			if ( ((short int *)exthead)[0]==0x4550 )exetype=PE_EXE;
			else if ( ((short int *)exthead)[0]==0x454e )exetype=NE_EXE;
			else if ( ((short int *)exthead)[0]==0x454c )exetype=LE_EXE;
			else if ( ((short int *)exthead)[0]==0x584c )exetype=OS2_EXE;
			else exetype=MZ_EXE;
		}
	}
}
//checks header info, puts up initial loading dialog box and
//selects info routine for file.
bool FileLoader::load(PCSTR fname)
{
	DWORD pe_offset;
	DWORD num;
	DWORD fsize;
	if ( efile!=INVALID_HANDLE_VALUE )return FALSE;

	efile=CreateFile(fname,GENERIC_READ,1,&securityatt,OPEN_EXISTING,0,NULL);
	if ( efile==INVALID_HANDLE_VALUE )
		return FALSE;

	if ( GetFileType(efile)!=FILE_TYPE_DISK )return FALSE;

	get_exetype();

    if (exetype != PE_EXE)	//only support PE now
    	return FALSE;

	fsize=GetFileSize(efile,NULL);
	fbuff=new BYTE[fsize];
	SetFilePointer(efile,0x00,NULL,FILE_BEGIN);
	ReadFile(efile,fbuff,fsize,&num,NULL);

	pe_offset = *(DWORD *)(fbuff+0x3c);
	//DialogBox(hInst,MAKEINTRESOURCE(D_checktype),mainwindow,(DLGPROC)checktypebox);
	//if(!SEG0)
	//{
	//SEG0=0x1000;
	// MessageBox(mainwindow,"Sorry - Can't use a zero segment base.\nSegment Base has been set to 0x1000"
	//  ,"Borg Message",MB_OK);
	//}
	//dsm.dissettable();
	switch ( exetype )
	{
	case BIN_EXE:
		readbinfile(fsize);
		break;
	case PE_EXE:
		//readpefile(pe_offset);
		LoadPE(pe_offset);
		break;
	case MZ_EXE:
		readmzfile(fsize);
		break;
	case OS2_EXE:
		reados2file();
		CloseHandle(efile);
		efile=INVALID_HANDLE_VALUE;
		exetype=0;
		return FALSE; // at the moment;
	case COM_EXE:
		readcomfile(fsize);
		break;
	case SYS_EXE:
		readsysfile(fsize);
		break;
	case LE_EXE:
		readlefile();
		CloseHandle(efile);
		efile=INVALID_HANDLE_VALUE;
		exetype=0;
		return FALSE; // at the moment;
	case NE_EXE:
		readnefile(pe_offset);
		break;
	default:
		CloseHandle(efile);
		efile=INVALID_HANDLE_VALUE;
		exetype=0;
		return FALSE;
	}
	return TRUE;
}
void FileLoader::readcomfile(DWORD fsize)
{
}
void FileLoader::readsysfile(DWORD fsize)
{
}
void FileLoader::readmzfile(DWORD fsize)
{
}
void FileLoader::readlefile(void)
{
}
void FileLoader::readnefile(DWORD offs)
{
}
void FileLoader::reados2file(void)
{
}
void FileLoader::readbinfile(DWORD fsize)
{
}


bool	IfInWorkSpace(ea_t off)
{	//	check if off lye in our work space
	if (off > 0x400000 && off < 0x600000)	//	暂且这样简单处理一下吧
		return TRUE;
	return FALSE;
}
/*
void FileLoader::readpefile(DWORD peoffs)
{
    char impbuff[100],inum[10];
	lptr sseg,t;
    int k;



	//options.dseg=SEG0;
	sseg.segm= SEG0;
	sseg.offs=0;
	
	PBYTE pestart = &fbuff[peoffs];
	PEHEADER* peh = (PEHEADER *)pestart;
	
	//options.loadaddr.offs=peh->image_base; // bugfix build 14
	

	PEObjData *pdata = (PEObjData *)(pestart+sizeof(PEHEADER)+(peh->numintitems-0x0a)*8);
	for ( int i=0;i<peh->objects;i++ )
	{
		BOOL peobjdone = FALSE;
		if ( (pdata[i].rva == peh->exporttable_rva)  ||// export info
			 ((peh->exporttable_rva > pdata[i].rva) &&
              (peh->exporttable_rva < pdata[i].rva+pdata[i].phys_size)) )
		{
			BYTE* expname;
			WORD *onaddr;
			DWORD *fnaddr,*nnaddr;
			peexportdirentry *expdir =
				(peexportdirentry *)&fbuff[pdata[i].phys_offset+peh->exporttable_rva-pdata[i].rva];
			t.assign(SEG0, peh->image_base+peh->exporttable_rva);
			//scheduler.addtask(dis_datadword,priority_data,t,NULL);
			//scheduler.addtask(dis_datadword,priority_data,t+4,NULL);
			//scheduler.addtask(dis_dataword,priority_data,t+8,NULL);
			//scheduler.addtask(dis_dataword,priority_data,t+10,NULL);
			//scheduler.addtask(dis_datadword,priority_data,t+12,NULL);
			//scheduler.addtask(dis_datadword,priority_data,t+16,NULL);
			//scheduler.addtask(dis_datadword,priority_data,t+20,NULL);
			//scheduler.addtask(dis_datadword,priority_data,t+24,NULL);
			//scheduler.addtask(dis_datadword,priority_data,t+28,NULL);
			for ( int k1=0;k1<peh->objects;k1++ )
			{
				if ( (expdir->namerva>=pdata[k1].rva)&&(expdir->namerva<pdata[k1].rva+pdata[k1].phys_size) )
				{
					expname=&fbuff[expdir->namerva-pdata[k1].rva+pdata[k1].phys_offset];
					break;
				}
			}
			t.offs=expdir->namerva+peh->image_base;
			//scheduler.addtask(dis_datastring,priority_data,t,NULL);
			DWORD numsymbols=expdir->numfunctions;
			BYTE* chktable=new BYTE [numsymbols];
			for ( DWORD j=0;j<numsymbols;j++ )
				chktable[j]=0;
			if ( expdir->numnames<numsymbols )numsymbols=expdir->numnames;
			for ( k=0;k<peh->objects;k++ )
			{
				if ( (expdir->nameaddrrva>=pdata[k].rva)&&(expdir->nameaddrrva<pdata[k].rva+pdata[k].phys_size) )
				{
					nnaddr=(DWORD *)&fbuff[expdir->nameaddrrva-pdata[k].rva+pdata[k].phys_offset];
					break;
				}
			}
			for ( k=0;k<peh->objects;k++ )
			{
				if ( (expdir->funcaddrrva>=pdata[k].rva)&&(expdir->funcaddrrva<pdata[k].rva+pdata[k].phys_size) )
				{
					fnaddr=(DWORD *)&fbuff[expdir->funcaddrrva-pdata[k].rva+pdata[k].phys_offset];
					break;
				}
			}
			for ( k=0;k<peh->objects;k++ )
			{
				if ( (expdir->ordsaddrrva>=pdata[k].rva)&&(expdir->ordsaddrrva<pdata[k].rva+pdata[k].phys_size) )
				{
					onaddr=(WORD *)&fbuff[expdir->ordsaddrrva-pdata[k].rva+pdata[k].phys_offset];
					break;
				}
			}
			lptr lef,leo,len;
			lef.assign(SEG0,expdir->funcaddrrva+peh->image_base);
			leo.assign(SEG0,expdir->ordsaddrrva+peh->image_base);
			len.assign(SEG0,expdir->nameaddrrva+peh->image_base);
			while ( numsymbols )
			{
				//scheduler.addtask(dis_datadword,priority_data,lef,NULL);
				//scheduler.addtask(dis_dataword,priority_data,leo,NULL);
				//scheduler.addtask(dis_datadword,priority_data,len,NULL);
				chktable[onaddr[0]]=1;
				t.assign(SEG0,peh->image_base+fnaddr[onaddr[0]]);
				//scheduler.addtask(dis_export,priority_export,t,(char *)&fbuff[(*nnaddr)+pdata[k].phys_offset-pdata[k].rva]);
				t.assign(SEG0,(*nnaddr)+peh->image_base);
				//scheduler.addtask(dis_datastring,priority_data,t,NULL);
				t.assign(SEG0,peh->image_base+fnaddr[onaddr[0]]);
				//scheduler.addtask(dis_code,priority_definitecode,t,NULL);
				numsymbols--;
				onaddr++;
				nnaddr++;
				lef+=4;
				leo+=2;
				len+=4;
			}
			if ( expdir->numfunctions>expdir->numnames )
			{
				for ( j=0;j<expdir->numfunctions;j++ )
				{
					if ( !chktable[j] )
					{
						DWORD numtmp=j+expdir->base;
						wsprintf(inum,"%02d",numtmp);
						lstrcpyn(impbuff,(char *)expname,GNAME_MAXLEN-8);
						k=0;
						while ( (impbuff[k])&&(k<GNAME_MAXLEN-8) )
						{
							if ( impbuff[k]=='.' )break;
							k++;
						}
						strcpy(&impbuff[k],"::ord_");
						strcat(impbuff,inum);
						char* newimpname=new char[strlen(impbuff)+1];
						strcpy(newimpname,impbuff);
						if ( fnaddr[j] )
						{
							t.assign(SEG0,fnaddr[j]+peh->image_base);
							//scheduler.addtask(dis_ordexport,priority_export,t,newimpname);
							//scheduler.addtask(dis_code,priority_definitecode,t,NULL);
						}
					}
				}
			}
			delete chktable;
		}
		if ( (pdata[i].rva==peh->importtable_rva) // import info
			 ||((peh->importtable_rva>pdata[i].rva)&&(peh->importtable_rva<pdata[i].rva+pdata[i].phys_size)) )
		{
			DWORD *imphint,impaddr,impaddr2;
			BYTE* impname;
			peimportdirentry *impdir;
			impdir=(peimportdirentry *)&fbuff[pdata[i].phys_offset+peh->importtable_rva-pdata[i].rva];
			DWORD j=0;
			while ( impdir[j].firstthunkrva )
			{
				t.assign(SEG0,
						 peh->image_base+peh->importtable_rva+j*sizeof(struct peimportdirentry));
				//scheduler.addtask(dis_datadword,priority_data,t,NULL);
				//scheduler.addtask(dis_datadword,priority_data,t+4,NULL);
				//scheduler.addtask(dis_datadword,priority_data,t+8,NULL);
				//scheduler.addtask(dis_datadword,priority_data,t+12,NULL);
				//scheduler.addtask(dis_datadword,priority_data,t+16,NULL);
				for ( int k1=0;k1<peh->objects;k1++ )
				{
					if ( (impdir[j].namerva>=pdata[k1].rva)&&(impdir[j].namerva<pdata[k1].rva+pdata[k1].phys_size) )
					{
						impname=&fbuff[impdir[j].namerva-pdata[k1].rva+pdata[k1].phys_offset];
						break;
					}
				}
				t.assign(SEG0,impdir[j].namerva+peh->image_base);
				//scheduler.addtask(dis_datastring,priority_data,t,NULL);

				DWORD thunkrva;
				if ( !impdir[j].originalthunkrva )
					thunkrva=impdir[j].firstthunkrva;
				else
					thunkrva=impdir[j].originalthunkrva;
				for ( k=0;k<peh->objects;k++ )
				{
					if ( (thunkrva>=pdata[k].rva)&&(thunkrva<pdata[k].rva+pdata[k].phys_size) )
					{
						imphint=(DWORD *)&fbuff[thunkrva-pdata[k].rva+pdata[k].phys_offset];
						break;
					}
				}
				impaddr=impdir[j].firstthunkrva+peh->image_base;
				impaddr2=impdir[j].originalthunkrva+peh->image_base;
				while ( *imphint )
				{
					if ( (*imphint)&0x80000000 )
					{
						DWORD numtmp=(*imphint)&0x7fffffff;
						wsprintf(inum,"%02d",numtmp);
						strcpy(impbuff,(char *)impname);
						k=0;
						while ( impbuff[k] )
						{
							if ( impbuff[k]=='.' )break;
							k++;
						}
						strcpy(&impbuff[k],"::ord_");
						strcat(impbuff,inum);
						char* newimpname=new char[strlen(impbuff)+1];
						strcpy(newimpname,impbuff);
						t.assign(SEG0,impaddr);
						//scheduler.addtask(dis_ordimport,priority_import,t,newimpname);
					}
					else
					{
						t.assign(SEG0,impaddr);
						//scheduler.addtask(dis_import,priority_import,t,(char *)&fbuff[(*imphint)+2+pdata[k1].phys_offset-pdata[k1].rva]);
					}
					t.assign(SEG0,peh->image_base+(*imphint));
					//scheduler.addtask(dis_dataword,priority_data,t,NULL);
					//scheduler.addtask(dis_datastring,priority_data,t+2,NULL);
					t.assign(SEG0,impaddr);
					//scheduler.addtask(dis_datadword,priority_data,t,NULL);
					t.assign(SEG0,impaddr2);
					//scheduler.addtask(dis_datadword,priority_data,t,NULL);
					imphint++;
					impaddr+=4;
					impaddr2+=4;
				}
				t.assign(SEG0,impaddr);
				//scheduler.addtask(dis_datadword,priority_data,t,NULL);
				t.assign(SEG0,impaddr2);
				//scheduler.addtask(dis_datadword,priority_data,t,NULL);
				j++;
			}
			t.assign(SEG0,
					 peh->image_base+peh->importtable_rva+j*sizeof(struct peimportdirentry));
			//scheduler.addtask(dis_datadword,priority_data,t,NULL);
			//scheduler.addtask(dis_datadword,priority_data,t+4,NULL);
			//scheduler.addtask(dis_datadword,priority_data,t+8,NULL);
			//scheduler.addtask(dis_datadword,priority_data,t+12,NULL);
			//scheduler.addtask(dis_datadword,priority_data,t+16,NULL);
		}
		if ( pdata[i].rva==peh->tls_rva )
			peobjdone=TRUE; // tls info
		if ( (pdata[i].rva == peh->resourcetable_rva)	||// resource info
			 ((peh->resourcetable_rva > pdata[i].rva) &&
			  (peh->resourcetable_rva < pdata[i].rva+pdata[i].phys_size)) )
		{ // RESOURCE_DATA;
			if ( (pdata[i].phys_size)&& Load_Resources )
			{
				perestable *resdir;
				resdir=(perestable *)&fbuff[pdata[i].phys_offset+peh->resourcetable_rva-pdata[i].rva];
				pdatarva=peh->resourcetable_rva;  // bugfix  build 14
				rawdata=(BYTE *)resdir;
				DWORD numitems=resdir->numnames+resdir->numids;
				perestableentry *rentry = (struct perestableentry *)(resdir+1);
				while ( numitems )
				{
					if ( (rentry->id)&0x80000000 )
					{
						BYTE* impname=rawdata+((rentry->id)&0x7fffffff);
						int clen=((WORD *)impname)[0];
						WideCharToMultiByte(CP_ACP,0,(const wchar_t *)(impname+2),clen,impbuff,100,NULL,NULL);
						impbuff[clen]=0;
					}
					else
					{
						switch ( rentry->id )
						{
						case 1:                  strcpy(impbuff,"Cursor");
							break;
						case 2:                  strcpy(impbuff,"Bitmap");
							break;
						case 3:                  strcpy(impbuff,"Icon");
							break;
						case 4:                  strcpy(impbuff,"Menu");
							break;
						case 5:                  strcpy(impbuff,"Dialog");
							break;
						case 6:                  strcpy(impbuff,"String Table");
							break;
						case 7:                  strcpy(impbuff,"Font Directory");
							break;
						case 8:                  strcpy(impbuff,"Font");
							break;
						case 9:                  strcpy(impbuff,"Accelerators");
							break;
						case 10:                  strcpy(impbuff,"Unformatted Resource Data");
							break;
						case 11:                  strcpy(impbuff,"Message Table");
							break;
						case 12:                  strcpy(impbuff,"Group Cursor");
							break;
						case 14:                  strcpy(impbuff,"Group Icon");
							break;
						case 16:                  strcpy(impbuff,"Version Information");
							break;
						case 0x2002:                  strcpy(impbuff,"New Bitmap");
							break;
						case 0x2004:                  strcpy(impbuff,"New Menu");
							break;
						case 0x2005:                  strcpy(impbuff,"New Dialog");
							break;
						default:
							strcpy(impbuff,"User Defined Id:");
							DWORD numtmp=rentry->id&0x7fffffff;
							wsprintf(inum,"%02lx",numtmp);
							strcat(impbuff,inum);
							break;
						}
					}
					if ( rentry->offset&0x80000000 )
					{
						//subdirsummary(rawdata+((rentry->offset)&0x7fffffff),impbuff,peh->image_base);
					}
					else
					{
						//leafnodesummary(rawdata+((rentry->offset)&0x7fffffff),impbuff,peh->image_base);
					}
					rentry++;
					numitems--;
				}
			}
			if ( pdata[i].rva==peh->resourcetable_rva )peobjdone=TRUE;
		}
		if ( pdata[i].rva==peh->fixuptable_rva ) // fixup info
		{
			perelocheader *per=(perelocheader *)&fbuff[pdata[i].phys_offset];
			while ( per->rva )
			{
				WORD* rdata=(WORD *)per+sizeof(perelocheader)/2;
				DWORD numrelocs=(per->len-sizeof(perelocheader))/2;
				while ( (numrelocs)&&(rdata[0]) )
				{
					t.assign(SEG0,((DWORD)(rdata[0])&0x0fff)+per->rva+peh->image_base);
					//reloc.addreloc(t,RELOC_NONE);
					rdata++;
					numrelocs--;
				}
				per=(perelocheader *)((BYTE *)(per)+per->len);
			}
			peobjdone=TRUE;
		}
		if ( pdata[i].rva==peh->debugtable_rva ) // debug info
		{
			// DEBUG_DATA;
			if ( (pdata[i].phys_size)&& Load_Debug )
			{
				sseg.offs=pdata[i].rva+peh->image_base;
				//dta.addseg(sseg,pdata[i].phys_size,&fbuff[pdata[i].phys_offset],debugdata,NULL);
			}
			peobjdone=TRUE;
		}
		if ( (pdata[i].obj_flags&0x40)&&(!(pdata[i].obj_flags&0x20))&&(!peobjdone) )
		{ // INIT_DATA;
			if ( (pdata[i].phys_size)&& Load_Data )
			{
				sseg.offs=pdata[i].rva+peh->image_base;
				//dta.addseg(sseg,pdata[i].phys_size,&fbuff[pdata[i].phys_offset],data32,NULL);
			}
			if ( (pdata[i].virt_size>pdata[i].phys_size)&& Load_Data )
			{
				sseg.offs=pdata[i].rva+peh->image_base+pdata[i].phys_size;
				BYTE* uinit=new BYTE[pdata[i].virt_size-pdata[i].phys_size];
				for ( DWORD j=0;j<pdata[i].virt_size-pdata[i].phys_size;j++ )	
					uinit[j]=0;
				//dta.addseg(sseg,pdata[i].virt_size-pdata[i].phys_size,uinit,uninitdata,NULL);
			}
		}
		else if ( (pdata[i].obj_flags&0x80)&&(!peobjdone) )
		{ // UNINIT_DATA;
			if ( Load_Data )
			{
				sseg.offs=pdata[i].rva+peh->image_base;
				BYTE* uinit=new BYTE[pdata[i].virt_size];
				for ( DWORD j=0;j<pdata[i].virt_size;j++ )
					uinit[j]=0;
				//dta.addseg(sseg,pdata[i].virt_size,uinit,uninitdata,NULL);
			}
		}
		else if ( !peobjdone )
		{ // CODE_DATA;
			if ( pdata[i].phys_size )
			{
				sseg.offs=pdata[i].rva+peh->image_base;
				//dta.addseg(sseg,pdata[i].phys_size,&fbuff[pdata[i].phys_offset],code32,NULL);
				//dta.possibleentrycode(sseg);
			}
		}
	}
	t.assign(SEG0,peh->entrypoint_rva+peh->image_base);

	for ( i=0;i<peh->objects;i++ )
	{
		if (pdata[i].rva <= peh->entrypoint_rva &&
			pdata[i].rva + pdata[i].virt_size > peh->entrypoint_rva)
		{
			proc2(&fbuff[pdata[i].phys_offset + peh->entrypoint_rva - pdata[i].rva],
				  //0x401000);
				  peh->entrypoint_rva+peh->image_base);
			break;
		}
	}
	//dsm.setcuraddr(t);
	//scheduler.addtask(dis_code,priority_definitecode,t,NULL);
	//scheduler.addtask(nameloc,priority_nameloc,t,"start");
	//scheduler.addtask(windowupdate,priority_window,nlptr,NULL);
}
*/
