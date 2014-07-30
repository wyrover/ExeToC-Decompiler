
#ifndef	_KS_COMMON_H_
#define _KS_COMMON_H_

class I_KSUNKNOWN
{
public:
	I_KSUNKNOWN(){}
	virtual	~I_KSUNKNOWN(){}

public:
	virtual	void __stdcall Release(){ delete this; }
	virtual	bool __stdcall BaseInit(){ return true; }
};

#define KS_DECLARE_COMPONENT(N1, N2) \
	\
	bool __stdcall N1##_Init();\
	void __stdcall N1##_Exit();\
	\
	I_##N2*	__stdcall NEW_##N2() \
	{\
		C##N1* pnew = new C##N1();\
		if (!pnew->BaseInit())\
		{\
			pnew->Release();\
			return NULL;\
		}\
		return pnew;\
	}\
	I_##N2*	__stdcall NEW_00_##N2() \
	{\
		static C##N1 m; \
		static bool f = false; \
		if (!f) \
			if (m.BaseInit()) \
				f=true; \
		if (!f) \
			return NULL; \
		return &m;\
	}

#ifdef _KSAPP_FRAME_CODE_
#define KS_DLLEXPORTS
#else
#define KS_DLLEXPORTS	__declspec(dllexport)
#endif
//如果是一个单独的模块，我希望它是一个DLL，这里输出

#define KS_DECLARE_INTERFACE(N1,N2)	\
		\
	extern "C" KS_DLLEXPORTS I_##N2*	__stdcall NEW_##N2(); \
	extern "C" KS_DLLEXPORTS I_##N2*	__stdcall NEW_00_##N2();


#define KICK_MFC()	AFX_MANAGE_STATE(AfxGetStaticModuleState())

#define SAFE_DELETE(p)\
	if (p != NULL)\
	{\
		delete p;\
		p = NULL;\
	}
#define SAFE_RELEASE(p)\
	if (p != NULL)\
	{\
		p->Release();\
		p = NULL;\
	}


#endif	//_KS_COMMON_H_
