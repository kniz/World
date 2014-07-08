//	---------------------------------------------------------------------------------
//	클래스명:	NESequencialFileLoader
//	설명	:	순차모드로 파일을 읽어들인다.
//	관계	:	기반클래스.	NEFileSystem
//				외부포함.	fstream
//	특성	:	WINAPI와 CRT를 사용한다.
//	사용방법:	순차모드로 파일을 읽어들임
//				1.	setPath로 경로 설정한다.
//				2.	open로 파일을 연다.
//				3.	readByLine(LPTSTR pointer), readByTocken(LPTSTR pointer)등으로 내용
//					을 읽는다.
//				4.	close로 파일을 닫는다. (객체 소멸시 자동 호출)
//	메모	:	
//	히스토리:	2011-01-09	이태훈	작성
//				2011-05-29	이태훈	개발 완료
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
	typedef std::basic_ifstream<TCHAR, std::char_traits<TCHAR> > _tifstream;

	class NE_DLL NESequencialFileLoader : public NEFileSystem
	{
		//	생성자:
	public:
		NESequencialFileLoader(LPCTSTR filename);
		NESequencialFileLoader();

		//	복사생성자:
	private:
		NESequencialFileLoader(const NESequencialFileLoader& source){}		 

		//	소멸자:
	public:
		virtual ~NESequencialFileLoader();

		//	연산자 중첩:
	private:
		const NESequencialFileLoader& operator=(const NESequencialFileLoader& source){return *this;}

		//	접근자:
	public:
		type_success isFileOpenSuccess() const;
		bool isEndOfFile() const;

		//	인터페이스:
	public:
		void readByLine(NE_OUT TCHAR* string_buffer_not_null, int buffer_size);
		void readByToken(NE_OUT TCHAR* string_buffer_not_null, int buffer_size, TCHAR token);
		void open();
		void close();
		void release();

		//	멤버변수:
	private:
		_tifstream _sequencial_file_in_stream;

	};
}
