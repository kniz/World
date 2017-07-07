//	---------------------------------------------------------------------------------
//	클래스명:	NENEFileSystem
//	설명	:	윈도우환경에서 파일검색, 폴더생성, 폴더삭제, 파일삭제
//				기능을 지원한다.
//	관계	:	FileAccess 패키지의 기반클래스
//	특성	:	파일 검색, 삭제, 폴더 생성, 삭제에 모두 WINAPI를 사용한다.
//				C String을 다루는 과정은 CRT를 사용한다.
//	알고리즘:	Task라는 개념을 만든다.
//				하나의 Task는 검색하는 경로, 현재 어디까지 검색이 진행되었는지 등을 
//				갖는다.
//				처음 NENEFileSystem에 파일경로가 주어지면 해당 경로를 검색할 Task를 하나
//				생성한다.
//				그 Task가 검색 도중 하위폴더를 검색하면 하위폴더를 검색하게될 Task를
//				하나 더 생성한다.
//	사용방법:	1.	검색 전, 검색방법( 하위폴더도 검색할 것인가 )을 지정한다
//					멤버변수인 is_search_lower_diectory_too를 외부에서 직접 조작
//				1.	setPath로 검색할 경로를 지정(와일드 카드포함)
//				2.	findfile 메소드로 파일검색
//				3.	만약 더이상 조건에 맞는 파일이 없을 경우, isThereAnyTask()이 false반환
//	메모	:	TaskUnit이 길면 길수록, 먼저 실행되는 작업을 의미한다.
//				TaskUnit의 LastIndex는 현재 실행중인 작업(TaskUnit)이다.
//	용어	:	1	절대경로	
//						:	어느 폴더, 위치에서 입력해도 인지가 가능한 경로를 말한다.
//							<--> 상대 경로
//							예)	c:/windows/system32
//				2	검색경로
//						:	WildCard와 작업디렉토리를 포함하는 경로를 말한다.
//							예) c:\windows\system32\*.dll
//				3	WildCard
//						:	어떤 형태로 검색을 실행할것인지 부여하는 조건식의 일종.
//							도스 명령어를 떠올리면 된다.
//							예)	*.*			모든 파일 검색
//								*.exe		확장자가 exe인 파일 검색
//								a???.dat	a로 시작되는 4글자 파일명을 가지고 확장자는 
//											dat인 파일
//				4	작업디렉토리
//						:	검색을 실시하는 디렉토리
//				5	파일경로
//						:	작업디렉토리와 검색한 파일명을 붙인 절대경로.
//							예) 검색경로를 c:\windows\system32\*.dll이라고 부여했을 경우,
//								파일명은 다음과 같을때,	
//												winmine.dll
//								해당 파일의 파일경로는 다음과 같다.
//											c:\windows\system32\winmine.dll						
//	히스토리:	2011-01-08	이태훈	작성
//				2011-01-12	이태훈	WorkDirectory라는 개념을 만듬, 접근자 함수 작성
//									setPath에 작업폴더를 지정하지 않은경우, 현재 폴더
//									자동으로 작업폴더로 지정하는 기능 추가
//				2011-05-29	이태훈	개발 완료
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "IncludeMacro.hpp"

namespace NE
{
	class NE_DLL NEFileSystem
	{
		//	내부클래스:
	public:
#include "TaskUnit.hpp"

		//	생성자:
	public:
		NEFileSystem();
		NEFileSystem(bool is_search_lower_directory_too);
		NEFileSystem(LPCTSTR path);
		NEFileSystem(LPCTSTR path, bool is_search_lower_directory_too);

		//	소멸자:
	public:
		~NEFileSystem();

	public:
		const TaskUnit& operator[](type_index index) const;

		//	접근자:
	public:
		type_index getLength() const;
		type_index getLastIndex() const;
		const TaskUnit& getLastElement() const;
		const TaskUnit& getElement(type_index index) const;

		//	인터페이스:
	public:		
		void findFile();
		void setPath(LPCTSTR path);
		type_error createDirectory(LPCTSTR path) const;
		type_error removeEmptyDirectory(LPCTSTR path) const;
		type_error removeFile(LPCTSTR path) const;
		void release();
		bool isSearchLowerDirectory() const;
		void setSearchLowerDirectory(bool search_lower_directory);

		//	내부함수:
	private:
		const TaskUnit& _getElement(type_index index) const;
		TaskUnit& _getElement(type_index index);
		void _findSubDirectoryFile();
		void _releaseTasks();
		void _releaseFlag();
		void _findFirstFile();
		void _findNextFile();
		void _backtrackTask();
		void _filterDottedDirectory(TaskUnit& target);
		LPTSTR _mergeNewPath(const TaskUnit& target) const;
		LPTSTR _mergePathForFindingSubDirectory();
		void _whetherIsNewTaskOrNot(TaskUnit& target);
		void _push(LPCTSTR new_path);
		void _pushFront(LPCTSTR new_path);
		void _pop();

		//	멤버변수:
	protected:
		type_index _length;
		TaskUnit* _header;	
		//		Flag:
		bool _is_search_lower_directory_too;

		//	더미함수:
	protected:		
		NEFileSystem(const NEFileSystem& source){}
		const NEFileSystem& operator=(const NEFileSystem& source){return *this;}
	};
}