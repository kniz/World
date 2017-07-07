//	---------------------------------------------------------------------------------
//	파일명	:	commonTypedef.hpp
//	설명	:	노드엔진에서 사용하는 타입 정의
//	메모	:	type_index를 short int로 정의하면, 엔진 전체의 부하가 줄어드는 방식으
//				로 개발되는 것을 목표로 한다.
//	히스토리:	2011-05-29	이태훈	개발 완료
//	---------------------------------------------------------------------------------
#pragma once

#include "Includes.hpp"

namespace NE
{
	typedef char					type_byte;
	typedef char					type_char;
	typedef unsigned char			type_uchar;
	typedef wchar_t					type_wchar;
#ifdef _UNICODE
	typedef type_wchar				type_tchar;
#else
	typedef type_char				type_tchar;
#endif
	typedef unsigned char			type_ubyte;
	typedef short int				type_short;
	typedef unsigned short int		type_ushort;
	typedef int						type_int;
	typedef unsigned int			type_uint;
	typedef float					type_float;
	typedef double					type_double;
	typedef __int64					type_int64;
	typedef unsigned __int64		type_uint64;
	typedef bool					type_error;
	typedef bool					type_success;
	typedef bool					type_bool;
	typedef int						type_index;
	typedef type_int				type_code;
	typedef type_uint64				type_id;
	typedef int						type_count;
}