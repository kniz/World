//	---------------------------------------------------------------------------------
//	클래스명:	NEModule
//	설명	:	하나의 기능을 제공하는 클래스. 모듈을 임의의 순서 / 배합을 통해서
//				지능적으로 반응하는 하나의 객체를 생성한다.
//	관계	:	기반클래스.	NENamedUnit
//				중첩클래스.	Header
//	특성	:	NEModuleManager에 friend 선언
//	알고리즘:	
//	사용방법:	execute()	:	담당하는 하나의 기능을 수행한다.
//				키를 다루는 방법은 2가지가 존재한다.
//					방법 1.	NEKeySet을 통해서 다룸.
//						:	이 경우 각 키의 타입을 읽어온 뒤에 캐스팅을 실시해야하고,
//							각 키가 "무슨 타입"이라는 건 알 수 있어도 "무슨 역할"을 
//							수행하는 가는 알 수 없다.
//					방법 2.	해당 모듈의 헤더를 통해서 모듈자체를 캐스팅한다.
//						:	이 경우 모듈의 BaseConnector를 이용하면 캐스팅 없이 사용이 
//							가능 하다.
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../../Commons/Interfaces/NEExportable/NEExportable.hpp"
#include "../NENamedUnit/NENamedUnit.hpp"
#include "../NEKeyCodeSet/NEKeyCodeSet.hpp"
#include "../NEArgumentSet/NEArgumentSet.hpp"
#include "../../Commons/Interfaces/NEArgumentInterfaceBase/NEArgumentInterfaceBase.hpp"

namespace NE
{
	class NE_DLL NEModule : public NENamedUnit, public NEExportable
	{
	public:
		typedef NENamedUnit SuperClass;
		typedef NEModule ThisClass;		

	public:
		//	프렌드 선언:
		friend class NEModuleManager;
		friend class NEScriptSet;
		friend class NEModuleCodeSet;
		friend NEBinaryFileLoader& NEArgumentSet::serialize(NEBinaryFileLoader& loader);

		//	생성자:
	public:		
		NEModule();
		NEModule(NEArgumentInterfaceList& argument_interfaces);
		NEModule(const NEModule& source);

		//	소멸자:
	public:
		virtual ~NEModule();

		//	연산자 중첩:
	public:
		const ThisClass& operator=(const ThisClass& rhs);
		bool operator==(const NEModule& source) const;
		bool operator!=(const NEModule& source) const;

		//	인터페이스:
	public:
		NEArgumentSet& getArguments() { return _arguments; }
		const NEArgumentSet getArguments() const { return _arguments; }

		//		상속:
	public:
		virtual type_result initialize();
		//			NEObject:
	public:
		virtual void release();
		virtual type_result isValid() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEType::Type getType() const;

	protected:
		virtual type_result _onModuleFetched();
		virtual type_result _onArgumentsFetched(NEArgumentInterfaceList& tray);

	protected:
		type_result _bindArguments();
		type_result _bindArguments(NEArgumentInterfaceList& args);

	private:
		ThisClass& _assign(const ThisClass& rhs);
		void _release();

	private:
		NEArgumentSet _arguments;
	};
}
