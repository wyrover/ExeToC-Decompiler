// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com


//	exe2c project

#ifndef SVarType_H
#define SVarType_H

typedef DWORD	VarTypeID;
typedef	DWORD	SIZEOF;

#include	"CClassManage.h"
#include	"CEnumMng.h"


enum
{
	id_void = 1,
	id_BYTE = 2,
	id_WORD = 3,
	id_DWORD= 4,
	id_double	= 5,
	id_int64	= 6,
	id_char,
	id_short,
	id_int,

	id_long,
	id_punknownfunc,

//	id_PVOID,
//	id_STRUC,
};
enum VarTT
{
    vtt_unknown = 0,
	vtt_base	= 1,	//	是基类型，不依赖于其它类型
	vtt_signed,			//	缺省为unsigned
	vtt_typedef,
	vtt_array,			//	数组
	vtt_point,
	vtt_class,          // 结构,或类
	vtt_funcpoint,
	vtt_const,			//	const
	vtt_enum,
    vtt_simple,         // 如果不知道是什么类型，就用这个
                        //简单类型 对每一个size都会有一个简单类型，实际上未知类型。名叫bit8之类
};

struct SVarType
{
	VarTypeID	id;			//	如果谁需要这个结构，只要记下这个id就行了
							//	通过这个id与 SVar 联系
	VarTT	type;

	//VarTypeID	id_pointto;	//	if this is a pointer
	union
	{
		struct
		{
			CFuncType*		pFuncType;		//	for vtt_funcpoint, if this is a func pointer
		} m_funcpoint;						//	= 1 means unknown funcpoint
		struct
		{
			char	classname[80];		//!!! only for unknown struc !
			Class_st*		pClass;			//	if this is a class
		} m_class;
		struct
		{
			VarTypeID	id_pointto;	//	if this is a pointer
		} m_point;
		struct
		{
			SIZEOF	arraynum;		// 	if this is a array, this is item count
			VarTypeID	id_arrayitem;	//	if this is a array, this is item id
		} m_array;
		struct
		{
			VarTypeID	id_base;	//	这个数据类型的基类
			PSTR	name;
		} m_typedef;
		struct
		{
			VarTypeID	id_base;	//	这个数据类型的基类
		} m_const;
		struct
		{
			VarTypeID	id_base;	//	这个数据类型的基类
			PSTR	name;
		} m_signed;
		struct
		{
			SIZEOF	opsize;
			PSTR	name;
		} m_base;					//	基类型
        struct
        {
            SIZEOF  opsize;
        } m_simple;
		struct
		{
			char	enumname[80];
			enum_st*	m_penum;
		} m_enum;
	};
};

typedef CList<SVarType*,SVarType*> VarTypeList;

class CVarTypeMng
{
private:
	VarTypeList*	list;
	VarTypeID		nextfreeid;
public:
	CVarTypeMng();
	~CVarTypeMng();
	
	VarTypeID	NewBaseVarType(SIZEOF opsize, PSTR name);
	VarTypeID	NewSimpleVarType(SIZEOF opsize);
	VarTypeID	NewSignedVarType(VarTypeID id, PSTR name);
	VarTypeID	NewTypeDef(VarTypeID id0, PCSTR name);
	VarTypeID	New_p(VarTypeID id0);

	void	VarType_ID2Name(VarTypeID id, PSTR namebuf);
	SIZEOF VarType_ID2Size(VarTypeID id);
	VarTypeID GetBaseID(BOOL fsign, SIZEOF size);
	BOOL	is_funcptr(VarTypeID id);
	Class_st*	is_classpoint(VarTypeID id);
	Class_st*	is_class(VarTypeID id);
    bool    is_simple(VarTypeID id);
	CFuncType* get_funcptr(VarTypeID id);
	
	VarTypeID GetAddressOfID(VarTypeID id);
	VarTypeID GetConstOfID(VarTypeID id);
	VarTypeID GetArrayItemID(VarTypeID id);
	VarTypeID NewUnknownStruc(PCSTR strucname);

	BOOL	If_Based_on(VarTypeID id, PSTR basename);
	BOOL	If_Based_on_idid(VarTypeID id, VarTypeID id0);
	
	VarTypeID FirstDataType(PCSTR &p);
	VarTypeID VarType_Name2ID(PCSTR name);
	VarTypeID NewArray(PSTR item_name,SIZEOF n);
	VarTypeID NewArray_id_id(VarTypeID id, SIZEOF n);
	VarTypeID Class2VarID(Class_st* pclass);
	VarTypeID Enum2VarID(enum_st* pnew);
	VarTypeID Get_unsigned_id(VarTypeID id);
	VarTypeID Get_signed_id(VarTypeID id);
	VarTypeID FuncType2VarID(CFuncType* ft);

	SVarType*	id2_VarType(VarTypeID id);
	VarTypeID GetPointTo(VarTypeID id);
	VarTypeID NoConst(VarTypeID id);
	Class_st*	id2_Class(VarTypeID id);
	enum_st*	id2_enum(VarTypeID id);
};


extern CVarTypeMng* g_VarTypeManage;

VarTypeID get_DataType_bare(PCSTR &p);	//	with "unsigned char *", only parse "unsigned char"
VarTypeID get_DataType(PCSTR &p);
VarTypeID Get_Additional_id(VarTypeID baseid, PCSTR &p);


SVarType* GG_id2_VarType(VarTypeID id);
CString	GG_VarType_ID2Name(VarTypeID id);
SIZEOF	GG_VarType_ID2Size(VarTypeID id);
BOOL	GG_is_funcpoint(VarTypeID id);
CFuncType* GG_get_funcpoint(VarTypeID id);
Class_st*	GG_id2_Class(VarTypeID id);

#endif	//	SVarType_H
