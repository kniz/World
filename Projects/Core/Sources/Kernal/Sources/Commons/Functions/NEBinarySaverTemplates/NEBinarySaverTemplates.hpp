//	---------------------------------------------------------------------------------
//	파일명	:	NEBinarySaverTemplates.hpp
//	설명	:	NEBinaryFileSaver의 operator <<를 오버로딩해서, 데이터 저장을 호출한다.
//	메모	:	Kernal 프로젝트에서 사용된다.
//	히스토리:	2011-06-04	이태훈	개발 완료
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../../../Includes/Includes.hpp"
#include "../../Enums/NEType/NEType.hpp"

namespace NE
{
	//	객체와 Primitive데이터와 동일한 인터페이스로 처리하기 위해서 operator<<를 스트림 전용 연산자로 지정함
	//	전역함수(global 함수)
	template <typename T>
	NEBinaryFileSaver& operator<<(NEBinaryFileSaver& saver, const T& data)
	{
		data.serialize(saver);

		return saver;
	}
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const char& data);
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const wchar_t& data);
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const bool& data);
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const short int& data);
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const int& data);
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const long int& data);
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const __int64& data);
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const float& data);
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const double& data);
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const long double& data);
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const unsigned char& data);
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const unsigned short int& data);
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const unsigned int& data);
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const unsigned long int& data);
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const unsigned __int64& data);	
}
