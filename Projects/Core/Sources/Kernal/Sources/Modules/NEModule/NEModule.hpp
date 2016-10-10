//	---------------------------------------------------------------------------------
//	클래스명:	NEModule
//	설명	:	하나의 기능을 제공하는 클래스. 모듈을 임의의 순서 / 배합을 통해서
//				지능적으로 반응하는 하나의 객체를 생성한다.
//	관계	:	기반클래스.	NENamedUnit
//				중첩클래스.	Header
//	특성	:	NEPackageManager에 friend 선언
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
//	히스토리:	2011-07-07	kniz	개발 완료	
//				2014-11-02	kniz	InterfaceBinding 추가
//	---------------------------------------------------------------------------------

//	관련 이슈 및 정책:
//		_assign(const This& rhs):
//			Argument, Module, ArugmentInterface 3가지를 아우르는 "모듈의 인자" 컴포넌트의 최중요 함수다.
//			모든 책임이 여기서 이루어지게 된다. 여기서 이루어져야 하는 것들은,
//				- 각각의 독립적으로 따로 노는 클래스들을 유기적으로 조립시킨다.
//				- 클래스들의 매개체 역할을 수행해야 한다.
//			가 된다.
//
//		Argument Binding Policy:
//			-	인스턴스 생성시 바인딩에 필요한 정보는 복사 되어야 한다.
//			-	바인딩 결과물은 절대로 객체간에 공유하지 않는다. 해당 객체가 다시 바인딩을 시도해야 한다.
//				왜냐하면, 같은 데이터를 가지고도 객체갸 어떤 소유자 밑에 있느냐에 따라서 바인딩 결과가 
//				달라지기 때문이다.
//			-	Interface를 통해 Argument 생성도 인스턴스 생성과 동시에 한번 이루어진다.
//			-	바인딩은 성공할 때까지 시도된다.
//				왜냐하면, 아직 Node에 포함되지 않는 Module도 있을 수 있기 때문이다.
//				현재까지로는 NEModule 자체가, 어떤 Node가 자신을 가지고 있는지 추적 할 수 없다.
//
//		_onArgumentFetched:
//			-	인스턴스 생성시 호출된다. (로드, 복사생성, 기본생성)
//			-	여기에는 바인딩 정보만 넣어두는 것을 권장한다.
//				매번 인스턴스 생성시 호출되므로, default_value 등을 여기서 정의하면 default_value는 
//				외부 객체로부터 복사가 안 일어나는 것처럼 보이게 된다.
//				(예, MyMod::_onArgumentFetched() { default_value = 58; } 
//				MyMod rhs.default_value=19 일때, MyMod me(rhs)를 수행하면, 복사과정에서
//					1/	me.default_value = rhs._default_value; 가 수행되어 19로 되었다가,
//					2/	MyMod::_onArgumentFetched()가 실행되어 다시 58로 된다)
//
//		bind를 localStack으로 구현하는 문제:
//			-	내가 bind를 수행하는 경우는 문제가 없으나, 반대로 외부에서 특정 모듈A의 bind를 수행한다면 문제가 된다.
//
//		Module은 ModuleCodeSet 외부에 정의될때 다음의 기능을 사용할 수 없다:
//			-	Module 외부에서는 bindArgument가 호출되지 않으므로, 내부 binding이 이루어지지 않게 된다.
//				따라서 ArumentInterface로부터 인스턴스가 생성되지 않기에, setKeyName을 사용할 수 없다.
//			-	반대로 말하면, ModuleCodeSet::insert에서, module을 clone() 한 뒤에, 여기서 bindArgument를 호출하게 된다.
//			
//		Module은 최소한 한번 execute되어야 외부바인딩이 이루어진다:
//			-	module.execute()에서 외부바인딩이 이루어지므로, 
//
//		State 개요:
//			-	Module::initialize()는 모듈 instance가 modulecodeset 안에서 생성되면 호출된다.
//				Module이 ModuleCodeSet 외부에서 생성되면 initialize는 호출되지 않는다.
//				기본적으로 initialize안에서는 내부바인딩을 실시한다.
//			-	onModuleFetched는 System에 모듈이 link되는 시점(ModuleManager로부터 모듈이 .dll 파일로부터 동적 바인딩 되는
//				시점)에서 호출된다.
//
//		State Flow:
//			-	첫 Module의 생성시(Module이 System에 fetch 될때):	(ModuleManager가 호출)
//				-	생성자				:	Argument의 기본값을 정의
//				-	onModuleFetched()	:	최초 1번만 실행
//			-	이후, Module이 ModuleCodeSet 내부에서 생성시:		(ModuleCodeSet이 호출)
//				-	복사생성자			:	원본의 ArgumentInterface가 복사생성됨(기본값도 복사됨)
//				-	initialize()		:	인스턴스가 생성시
//					-	onArgumentFetched()	:	ArgumentInterface를 System에 알려줌.
//			-	로드시:
//				-	없음
//			-	외부에서 생성시:
//				-	생성자
//
//			-	결론:
//				최초만 ArgumentInterface의 생성이 되고, 이후로는 복사생성만 수행된다.
//				따라서 도중에 기본값을 바꾸고, 이를 바탕으로 복사생성하는 경우 기본값이 제대로 반영되게 된다.
//				기본값이 주어지지 않을 경우, 모듈개발자가 의도한 기본값이 자동으로 세팅되는 점도 가능하게 되었다.
//				그러나 외부에서 모듈을 생성하면 Argument 조작은 가능하나, System에 반영되지 않는다.
//
//		인터페이스 바인딩:
//			정의:
//				사용자 모듈 레이어의 인터페이스객체와 커널단의 구체인스턴스를 연결해주는 작업을 말한다.
//				해당 바인딩 자체는 NEArgumentSet에서 처리를 하게 되며, NEArgumentSet은 보내어진 InterfaceList를 
//				하나씩 순회하면서,
//					- 이미 인터페이스에 대한 구체인스턴스가 추가 되어있는가?
//						- 예
//							- 바인딩이 되어 있는가?
//								- 작업 취소
//								- 바인딩만 실시
//						- 아니오
//							- 구체인스턴스 추가후, 바인딩 실시
//				처럼 동작하게 된다.
//	
//			왜 인터페이스 바인딩을 수행해야 하는가? 그냥 NETArgument 하나 자체를 인터페이스 & 구체인스턴스로		
//			모두 사용 할 수 있을 껀데:
//				왜냐하면, 인터페이스 바인딩과 인스턴스 복사에 대한 시간적 종속성을 없애기 위해서이다.
//				좀 더 풀어 설명하면, NEModule source로 부터 복사생성이 일어난다고 해보자.
//				이럴 경우 다음과 같은 딜레마가 발생한다.
//		
//					1. NETArgument을 인터페이스 대용으로 쓴다는 것은 UserModule 레이어의 멤버변수인 
//					NETArgument 인스턴스를 커널단에 aggregation 한다는 걸 의미한다. (커널단에 
//					NETArgument 기반으로 새로운 인스턴스를 생성하면 Argument 당 2개의 인스턴스가 생긴다는 
//					의미니까)
//		
//					2. NEArgument 복사가 일어날려면, 미리 NEArgumentSet이 인스턴스가 추가되고, source.argument로부터 
//					인스턴스를 대입해야 한다.
//		
//					3. 1처럼 NEArgumentSet은 NEArray<T*, false> 이므로, 콜백으로 인스턴스를 받아와야 할 것이다.
//					
//					4. 그런데 NEModule::NEModule()에서는 콜백을 호출 할 수 없다. 아직 v-table이 등록되지 않았다.
//					
//					*. 결론적으로 "콜백에서 인스턴스 받아옴 -> 인스턴스 복사" 가 이루어져야 하나, 그 콜백을 
//					만들려먼, 생성자가 끝나야 한다.
//	
//			다른 해결방법은 없는가?:
//				크게 3가지 방법이 있다.
//					1. NEModuleArray::insert에서만 복사가 이루어지게끔 한다. 여기서 "일단 생성 -> 나중 복사" 
//					식으로 처리해 버리면 된다. 그러나, insert 함수를 꼭 호출해야 한다는 제약이 생긴다.
//	
//					2. 처음에는 부모 생성자 리스트가 먼저 호출 될 것이다. 거기서 어떻게든 부모생성자에 인자로 
//					정보를 보낸다. 그러나, 문제는 어떻게 이다.
//	
//					3. 인스턴스를 받아오지 말고, 자체적으로 복사가 되게끔 한다. NEArgumentSet은 <T*, true>로 
//					하여, 자체적으로 인스턴스 관리가 되게 한다. 그러나 이렇게 하면 UserModule 레이어의 인터페이스 
//					와는 별개의 인스턴스가 되므로, 이 둘을 엮어주는 바인딩이 추가로 들어간다.
//	
//				여기서 채택한건 3번 방법이다.
#pragma once

//	include:
#include "../../Commons/Interfaces/NEInitializable/NEInitializable.hpp"
#include "../NENamedUnit/NENamedUnit.hpp"
#include "../NEKeyCodeSet/NEKeyCodeSet.hpp"
#include "../NEArgumentSet/NEArgumentSet.hpp"
#include "../NEArgumentList/NEArgumentList.hpp"
#include "define/ModuleMacro.hpp"

namespace NE
{
	class NE_DLL NEModule : public NENamedUnit, public NEInitializable
	{
		NE_DECLARE_INTERFACE(NEModule, NENamedUnit)

	public:
		//	프렌드 선언:
		friend class NEModuleSet;
		friend class NEScriptSet;
		friend class NEModuleCodeSet;

		//	생성자:
	public:		
		NEModule();
		NEModule(const This& source);

		//	소멸자:
	public:
		virtual ~NEModule();

		//	연산자 중첩:
	public:
		const This& operator=(const This& rhs);
		type_bool operator==(const This& source) const;
		type_bool operator!=(const This& source) const;

	public:
		virtual type_result execute();
		virtual type_result initialize();
		//			NEObject:
	public:
		virtual void release();
		virtual type_result isValid() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	public:
		NEArgumentSet& getArguments();
		const NEArgumentSet& getArguments() const;
		NEModuleCodeSet& getOwner();
		const NEModuleCodeSet& getOwner() const;

	protected:
		virtual type_result _onFetchModule();
		virtual type_result _onFetchArguments(NEArgumentList& tray);
		virtual type_result _onInitialize();
		virtual type_result _onExecute();

	private:
		This& _assign(const This& rhs);
		void _release();
		type_result _bindInterfaces();

	private:
		NEArgumentSet _arguments;
		type_bool _is_argument_fetched;
		NEModuleCodeSet* _owner;
		type_index _index;
	};
}