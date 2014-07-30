#ifdef _DEBUG

#define VERIFY_ISWRITEPOINTER(a)		{ if(::IsBadWritePtr(a, sizeof(LPDWORD))) \
			{ ::OutputDebugString(_T("Parameter ") _T(#a) _T(" is not a valid write pointer\r\n"));}}
#define VERIFY_ISREADPOINTER(a)		{ if(::IsBadReadPtr(a, sizeof(LPDWORD)))\
			{ ::OutputDebugString(_T("Parameter ") _T(#a) _T(" is not a valid read pointer\r\n"));}}

#define VERIFY_ISWRITEDATA(a, l)		{ if(::IsBadWritePtr(a, l)) \
			{ ::OutputDebugString(_T("Parameter ") _T(#a) _T(" is not a valid write area\r\n"));}}
#define VERIFY_ISREADDATA(a, l)		{ if(::IsBadReadPtr(a, l))  \
			{ ::OutputDebugString(_T("Parameter ") _T(#a) _T(" is not a valid read area\r\n"));}}

#define ASSERT_ISWRITEPOINTER(a)		{ if(::IsBadWritePtr(a, sizeof(LPDWORD))) \
			{ ::OutputDebugString(_T("Parameter ") _T(#a) _T(" is not a valid write pointer\r\n")); ASSERT(false);}}
#define ASSERT_ISREADPOINTER(a)		{ if(::IsBadReadPtr(a, sizeof(LPDWORD)))  \
			{ ::OutputDebugString(_T("Parameter ") _T(#a) _T(" is not a valid read pointer\r\n")); ASSERT(false);}}

#define ASSERT_ISWRITEDATA(a, l)		{ if(::IsBadWritePtr(a, l)) \
			{ ::OutputDebugString(_T("Parameter ") _T(#a) _T(" is not a valid write area\r\n")); ASSERT(false);}}
#define ASSERT_ISREADDATA(a, l)		{ if(::IsBadReadPtr(a, l))  \
			{ ::OutputDebugString(_T("Parameter ") _T(#a) _T(" is not a valid read area\r\n")); ASSERT(false);}}

#else

#define VERIFY_ISWRITEPOINTER(a)
#define VERIFY_ISREADPOINTER(a)	

#define VERIFY_ISWRITEDATA(a, l)
#define VERIFY_ISREADDATA(a, l)	

#define ASSERT_ISWRITEPOINTER(a)
#define ASSERT_ISREADPOINTER(a)

#define ASSERT_ISWRITEDATA(a, l)
#define ASSERT_ISREADDATA(a, l)

#endif