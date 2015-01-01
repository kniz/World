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
#include "../NECodeSet/NECodeSet.hpp"

namespace NE
{
	class NE_DLL NENamedUnit : public NEExecutableUnit
	{	
		friend class NENodeManager;
		//	생성자:
	public:
		NENamedUnit(const NECodeType& script_type, const NECodeType& name_type);
		NENamedUnit(const NENamedUnit& source);

		//	소멸자:
	public:
		virtual ~NENamedUnit();

		//	연산자 중첩:
	public:
		bool operator==(const NENamedUnit& source) const;
		bool operator!=(const NENamedUnit& source) const;
		const NENamedUnit& operator=(const NENamedUnit& source);

	public:
		type_code getNameCode() const;
		type_result setNameCode(type_code new_code);
		type_code getScriptCode() const;

		//	인터페이스:
		//		상속:
		//			NENamedUnit:
	public:
		virtual type_result setCodes(const NECodeSet& source);
		virtual const NECodeSet& getCodes(const NECodeType& type) const;
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

	protected:
		NECodeSet& _getScriptCodes();
		NECodeSet& _getNameCodes();

	private:
		NECodeSet _scriptcodes;
		NECodeSet _namecodes;		
	};
}