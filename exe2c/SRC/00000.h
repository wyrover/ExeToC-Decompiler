// Copyright(C) 1999-2005 LiuTaoTao£¬bookaa@rorsoft.com

typedef DWORD ea_t;
typedef	DWORD	SIZEOF;
typedef DWORD	VarTypeID;
#include "mylist.h"

PSTR	new_str(PCSTR p);

int		alert_prtf(PCSTR fmt, ...);
#define log_prtf
#define alert
#define log_prtt
#define log_prtl
void nop();

#define	SIZE_unknown 0xfffffffe
#define BIT32_is_4 4