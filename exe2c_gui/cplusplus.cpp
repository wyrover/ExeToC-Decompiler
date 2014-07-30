#include "stdafx.h"
#include "SampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	C++ keywords (MSVC5.0 + POET5.0)
static LPTSTR s_apszCppKeywordList[] =
{
	_T("CALL"),
	_T("MOV"),
	_T("__asm"),
	_T("enum"),
	_T("__multiple_inheritance"),
	_T("template"),
	_T("auto"),
	_T("__except"),
	_T("__single_inheritance"),
	_T("this"),
	_T("__based"),
	_T("explicit"),
	_T("__virtual_inheritance"),
	_T("thread"),
	_T("bool"),
	_T("extern"),
	_T("mutable"),
	_T("throw"),
	_T("break"),
	_T("false"),
	_T("naked"),
	_T("true"),
	_T("case"),
	_T("__fastcall"),
	_T("namespace"),
	_T("try"),
	_T("catch"),
	_T("__finally"),
	_T("new"),
	_T("__try"),
	_T("__cdecl"),
	_T("float"),
	_T("operator"),
	_T("typedef"),
	_T("char"),
	_T("for"),
	_T("private"),
	_T("typeid"),
	_T("class"),
	_T("friend"),
	_T("protected"),
	_T("typename"),
	_T("const"),
	_T("goto"),
	_T("public"),
	_T("union"),
	_T("const_cast"),
	_T("if"),
	_T("register"),
	_T("unsigned"),
	_T("continue"),
	_T("inline"),
	_T("reinterpret_cast"),
	_T("using"),
	_T("__declspec"),
	_T("__inline"),
	_T("return"),
	_T("uuid"),
	_T("default"),
	_T("int"),
	_T("short"),
	_T("__uuidof"),
	_T("delete"),
	_T("__int8"),
	_T("signed"),
	_T("virtual"),
	_T("dllexport"),
	_T("__int16"),
	_T("sizeof"),
	_T("void"),
	_T("dllimport"),
	_T("__int32"),
	_T("static"),
	_T("volatile"),
	_T("do"),
	_T("__int64"),
	_T("static_cast"),
	_T("wmain"),
	_T("double"),
	_T("__leave"),
	_T("__stdcall"),
	_T("while"),
	_T("dynamic_cast"),
	_T("long"),
	_T("struct"),
	_T("xalloc"),
	_T("else"),
	_T("main"),
	_T("switch"),
	_T("interface"),
	//	Added by a.s.
	_T("persistent"),
	_T("_persistent"),
	_T("transient"),
	_T("depend"),
	_T("ondemand"),
	_T("transient"),
	_T("cset"),
	_T("useindex"),
	_T("indexdef"),
	NULL
};

static BOOL IsCppKeyword(LPCTSTR pszChars, int nLength)
{
	for (int L = 0; s_apszCppKeywordList[L] != NULL; L ++)
	{
		if (strncmp(s_apszCppKeywordList[L], pszChars, nLength) == 0
				&& s_apszCppKeywordList[L][nLength] == 0)
			return TRUE;
	}
	return FALSE;
}

static BOOL IsCppNumber(LPCTSTR pszChars, int nLength)
{
	if (nLength > 2 && pszChars[0] == '0' && pszChars[1] == 'x')
	{
		for (int I = 2; I < nLength; I++)
		{
			if (isdigit(pszChars[I]) || (pszChars[I] >= 'A' && pszChars[I] <= 'F') ||
										(pszChars[I] >= 'a' && pszChars[I] <= 'f'))
				continue;
			return FALSE;
		}
		return TRUE;
	}
	if (! isdigit(pszChars[0]))
		return FALSE;
	for (int I = 1; I < nLength; I++)
	{
		if (! isdigit(pszChars[I]) && pszChars[I] != '+' &&
			pszChars[I] != '-' && pszChars[I] != '.' && pszChars[I] != 'e' &&
			pszChars[I] != 'E')
			return FALSE;
	}
	return TRUE;
}

#define DEFINE_BLOCK(pos, colorindex)	\
	ASSERT((pos) >= 0 && (pos) <= nLength);\
	if (pBuf != NULL)\
	{\
		if (nActualItems == 0 || pBuf[nActualItems - 1].m_nCharPos <= (pos)){\
		pBuf[nActualItems].m_nCharPos = (pos);\
		pBuf[nActualItems].m_nColorIndex = (colorindex);\
		nActualItems ++;}\
	}

#define COOKIE_COMMENT			0x0001
#define COOKIE_PREPROCESSOR		0x0002
#define COOKIE_EXT_COMMENT		0x0004
#define COOKIE_STRING			0x0008
#define COOKIE_CHAR				0x0010

