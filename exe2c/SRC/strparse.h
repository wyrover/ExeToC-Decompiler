// Copyright(C) 1999-2005 LiuTaoTao£¬bookaa@rorsoft.com


//	exe2c project
#ifndef	STRPARSE_H
#define	STRPARSE_H

void get_1part(OUT PSTR buf,PCSTR &p);
void skip_space(PCSTR &p);
void skip_eos(PCSTR &p);
BOOL if_split_char(char c);
DWORD Str2Num(PCSTR p);
signed int Str2Int(PCSTR p);


#endif	//STRPARSE_H
