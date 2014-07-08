//	---------------------------------------------------------------------------------
//	클래스명:	NENamedUnit
//	설명	:	이름을 가지고 있는 객체를 나타낸다.
//				이름은, ID와 Group과는 또 다른 개념이다.
//	관계	:	기반클래스.	NEExecutableUnit
//	특성	:	
//	알고리즘:	
//	사용방법:	
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../NEExecutableUnit/NEExecutableUnit.hpp"

namespace NE
{
	class NE_DLL NENamedUnit : public NEExecutableUnit
	{	
		friend class NENodeManager;
		//	생성자:
	public:
		NENamedUnit();
		NENamedUnit(type_code namecode);
		NENamedUnit(const NENamedUnit& source);

		//	소멸자:
	public:
		virtual ~NENamedUnit();

		//	연산자 중첩:
	public:
		bool operator==(const NENamedUnit& source) const;
		bool operator!=(const NENamedUnit& source) const;
		const NENamedUnit& operator=(const NENamedUnit& source);

		//	접근자:
	public:
		type_code getNameCode() const;
		type_code getScriptCode() const;

		//	인터페이스:
		//		상속:
		//			NENamedUnit:
	public:
		virtual type_result setNameCode(type_code new_namecode);
		//			NEObject:
	public:
		virtual void release();
		virtual type_result isValid() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

		//	내부함수:
	private:
		void _release();
		const NENamedUnit& _assign(const NENamedUnit& source);

		//	멤버변수:
	protected:
		type_code _namecode;
		type_code _scriptcode;
	};
}