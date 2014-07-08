//	---------------------------------------------------------------------------------
//	클래스명:	NEBinaryFileSaver
//	설명	:	바이너리모드로 파일에 데이터를 저장한다.
//	관계	:	기반클래스.	NEBinaryFileAccessor
//				외부포함.	<fstream>
//	특성	:	
//	알고리즘:	
//	사용방법:	1.	setPath()로 경로를 지정한다.
//				2.	open()으로 파일을 연다.//				
//				3.	execute(LPTSTR data, int size)로 데이터가 저장된 LPTSTR 배열의 
//					포인터를 넣는다.
//				4.	파일끝에 다다르면 isEndOfFile()이 true가 된다.
//	메모	:	MSVC 2008의 컴파일러 경고 4251을 diable 했다.
//	히스토리:	2011-01-09	이태훈	작성
//				2011-05-29	이태훈	개발 완료
//				2011-07-10	이태훈	추가
//					:	바이너리 open시 무조건 ios_base::ate Flag를 추가했다.
//						그리고, 파일포인터의 위치를 가져오는 getPosition과 setPosition을
//						추가 했다. 모든 환경에서 테스트는 실시 하지 못했다.
//				2011-07-16	이태훈	추가
//					:	NEBinaryAccessor로부터 상속. 상속받은 가상함수는 virtual 선언
//	---------------------------------------------------------------------------------
#pragma once
#pragma warning(disable : 4251)	//	crt의 basic_ifstream이 dllexport로 선언되지 않아서 문제가 생기는 건데, 
//	ifstream은 private로 외부에서 접근이 불가하고, export된 접근자 함수로만
//	사용되기 때문에 문제가 없을 것으로 판단했다

//	include:
#include <iostream>
#include <fstream>
#include "../NEBinaryFileAccessor/NEBinaryFileAccessor.hpp"

namespace NE
{
	class NE_DLL NEBinaryFileSaver : public NEBinaryFileAccessor
	{
		//	생성자:
	public:
		NEBinaryFileSaver(LPCTSTR filename, NEFileSaverFlag flag = NEFileSaverFlag(NE_DEFAULT));
		NEBinaryFileSaver(NEFileSaverFlag flag = NEFileSaverFlag(NE_DEFAULT));

		//	소멸자:
	public:
		virtual ~NEBinaryFileSaver();

		//	접근자:
	public:		
		void setFlag(NEFileSaverFlag flag);
		NEFileSaverFlag getFlag() const;

		//	인터페이스:
		//		상속 인터페이스:	
		//			NEBinaryAccessor:
	public:
		virtual bool isSaver();
		virtual type_success isFileOpenSuccess() const;
		virtual void release();
		virtual void open();
		virtual void close();
		virtual long int getPosition();
		virtual void setPosition(long int position);

		//		고유 인터페이스:
	public:
		void execute(NE_IN const char* const data, int size);

		//	멤버변수:
	private:
		std::ofstream _binary_file_out_stream;
		NEFileSaverFlag _flag;

		//	더미:
	private:
		const NEBinaryFileSaver& operator=(const NEBinaryFileSaver& source){return *this;}
		NEBinaryFileSaver(const NEBinaryFileSaver& source){}
	};
}
