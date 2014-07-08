//	---------------------------------------------------------------------------------
//	클래스명:	NESequencialFileSaver
//	설명	:	순차모드로 파일을 저장한다.
//	관계	:	기반클래스.	NEFileSystem
//				외부포함.	<fstream>
//	특성	:	
//	알고리즘:	
//	사용방법:	1.	setPath로 경로 설정
//				2.	open로 접속
//				3.	writeString으로 파일에 데이터 저장
//				4.	close로 파일닫기
//	메모	:	1	MSVC 2008의 컴파일러 경고 4251을 diable 했다.
//				2	MBCS환경에서 일어로 파일을 작성할경우 파일명이 깨지는 현상이 발생한다.
//					파일내용을 작성할때는 문제가 없으나 호환성을 위해서 파일명은 영문으로
//					작성하는 것을 권장한다.
//	히스토리:	2011-01-09	이태훈	작성
//				2011-06-04	이태훈	개발 완료
//	---------------------------------------------------------------------------------
#pragma once
#pragma warning(disable : 4251) // crt의 basic_ifstream이 dllexport로 선언되지 않아서 문제가 생기는 건데, ifstream은 private로 외부에서 접근이 불가하고, export된 접근자 함수로만 사용되기 때문에 문제가 없을 것으로 판단.

//	include:
#include <fstream>
#include "../../Commons/CommonType.hpp"
#include "../../Includes/Includes.hpp"

namespace NE
{
	//	typedef:
	typedef std::basic_ofstream<TCHAR, std::char_traits<TCHAR> > _tofstream;

	class NE_DLL NESequencialFileSaver : public NEFileSystem
	{
		//	생성자:
	public:
		NESequencialFileSaver(LPCTSTR filename, NEFileSaverFlag flag = NEFileSaverFlag(NE_DEFAULT));
		NESequencialFileSaver(NEFileSaverFlag flag = NEFileSaverFlag(NE_DEFAULT));
		NESequencialFileSaver(const NESequencialFileSaver& source){}

		//	소멸자:
	public:
		virtual ~NESequencialFileSaver();

		//	연산자 중첩:
	public:
		const NESequencialFileSaver& operator=(const NESequencialFileSaver& source){return *this;}

		//	접근자:
	public:
		type_success isFileOpenSuccess() const; 

		//	인터페이스:
	public:
		void writeString(const TCHAR* const string);
		void open();
		void close();
		void release();

		//	멤버변수:
	public:
		NEFileSaverFlag flag;

	private:
		_tofstream _sequencial_file_out_stream;		
	};
}
