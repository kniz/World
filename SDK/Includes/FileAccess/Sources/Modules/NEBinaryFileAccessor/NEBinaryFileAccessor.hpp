//	---------------------------------------------------------------------------------
//	클래스명:	NEBinaryFileAccessor
//	설명	:	바이너리모드로 접근한다.
//	관계	:	기반클래스.	NEFileSystem
//	특성	:	
//	알고리즘:	
//	사용방법:	1.	setPath()로 경로를 지정한다.
//				2.	open()으로 파일을 연다.				
//				3.	execute(LPTSTR data, int size)로 데이터가 저장된 LPTSTR 배열의 
//					포인터를 넣는다.
//				4.	파일끝에 다다르면 isEndOfFile()이 true가 된다.
//	메모	:	MSVC 2008의 컴파일러 경고 4251을 diable 했다.
//	히스토리:	2011-01-09	이태훈	작성
//				2011-05-29	이태훈	개발 완료
//				2011-07-16	이태훈	추가
//					:	Saver와 Loader의 공통함수를 집약했다.
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../../Includes/Includes.hpp"
#include "../../Commons/CommonType.hpp"

namespace NE
{
	class NE_DLL NEBinaryFileAccessor : public NEFileSystem
	{
		//	생성자:
	public:
		NEBinaryFileAccessor();
		NEBinaryFileAccessor(LPCTSTR filename);

		//	소멸자:
	public:
		virtual ~NEBinaryFileAccessor();

		//	인터페이스:
		//		순수 가상 인터페이스:	
	public:
		virtual bool isSaver() = 0;
		virtual type_success isFileOpenSuccess() const = 0;		
		virtual void release() = 0;
		virtual void open() = 0;
		virtual void close() = 0;
		virtual long int getPosition() = 0;
		virtual void setPosition(long int position) = 0;

		//	더미:
	private:
		const NEBinaryFileAccessor& operator=(const NEBinaryFileAccessor& source){return *this;}
		NEBinaryFileAccessor(const NEBinaryFileAccessor& source){}
	};
}
