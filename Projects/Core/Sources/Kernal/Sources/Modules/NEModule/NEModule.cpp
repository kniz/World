#include "NEModule.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	//	--------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEModule::NEModule()
#pragma warning(push)
#pragma warning(disable: 4355)	//	Warning C4355:	this 포인터를 생성자에서 사용하였다
		: NENamedUnit(), _arguments(this)
	{
		_release();
	}		



	//	--------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	--------------------------------------------------------------------------------
	NE_DLL NEModule::NEModule(const NEModule& source)
		: NENamedUnit(source), _arguments(this, source._arguments)
	{
		_assign(source);
	}

	NEModule::NEModule(NEArgumentInterfaceList& argument_interfaces)
		: NENamedUnit(), _arguments(this)
#pragma warning(pop)
	{
		_bindArguments(argument_interfaces);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEModule::~NEModule()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEModule::operator==(const NEModule& source) const
	{
		if(this == &source) return true;
		if(NENamedUnit::operator==(source) == false) return false;
		if(_arguments != source._arguments) return false;
		
		return true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEModule::operator!=(const NEModule& source) const
	{
		return !(operator==(source));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NEModule::serialize(NEBinaryFileLoader& loader)
	{
		NENamedUnit::serialize(loader);

		/*
			모듈의 scriptcode는 그대로 저장/로드 되어서는 안된다.
			시스템에 따라서 변경될 수 있기 때문이다.
		*/
		_scriptcode = Kernal::getInstance().getModuleManager().getModule(getHeader()).getScriptCode();

		return _arguments.serialize(loader);
	}

	NEBinaryFileSaver& NEModule::serialize(NEBinaryFileSaver& saver) const
	{
		NENamedUnit::serialize(saver);

		/*
			Argument의 저장:
				ArgumentBase에만 serialize가 오버라이딩 되어있으므로, KeyNameBinder만 저장이된다.
				이는 의도적인 행동으로, NEKey*는 저장할 수 없기 때문에 매 로드시마다 바인딩을
				시도 하게 된다.

				*) 키의 이름이 도중에 바뀐 경우, 올바른 동작을 보장 할 수 없다.
		*/
		return _arguments.serialize(saver);	//	private 접근자이므로 friend가 효력을 발휘하기 위해 직접 호출한다
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEType::Type NE_DLL NEModule::getType() const
	{
		return NEType::NEMODULE;
	}


	type_result NE_DLL NEModule::_onModuleFetched()
	{
		return RESULT_SUCCESS | RESULT_ABORT_ACTION;
	}

	void NEModule::release()
	{
		SuperClass::release();

		_release();
	}

	type_result NEModule::isValid() const
	{
		type_result result = SuperClass::isValid();
		if(NEResult::hasError(result)) return result;
		result = _arguments.isValid();
		if(NEResult::hasError(result)) return result;

		return RESULT_SUCCESS;
	}

	const NEModule& NEModule::operator=(const ThisClass& rhs)
	{
		if(this == &rhs) return *this;

		SuperClass::operator=(rhs);

		return *this;
	}

	void NEModule::_release()
	{
		_arguments.release();
	}

	/*
		Argument Fetch Policy:
			Overview:
				여기서 말하는 정책의 대상은 "인자정보를 바탕으로 인자를 생성하는 것"
				즉, 언제 _bindArguments가 호출되는지를 명시하는 것을 말한다.
			
			Conclusion:
				_bindArgument호출은 NEModuleCodeSet에 NEModule이 인스턴스가 생성되는 순간
				만드는 것으로 한다.
			
			Why:
				Arguments는 NENode의 어떤 키와 연결이 되는지를 보관하고 있다는 게 포인트.
			
			Worst Scenario:
				1/	밖에서 NEModule 만들어서 인자정보를 넣고, 이를 NEModuleCodeSet에 넣는 작업을 수행할 때	
					-> NENode가 정해지지 않았으므로 Argument가 수행되지 않는 것이 옳다.			
	*/
	type_result NEModule::_bindArguments()
	{
		NEArgumentInterfaceList tray;
		_onArgumentsFetched(tray);

		return _bindArguments(tray);
	}

	type_result NEModule::_bindArguments(NEArgumentInterfaceList& args)
	{
		_arguments.create(args.getLength());

		type_result r = 0;

		for(int n=0; n < args.getLength() ;n++)
			r |= _arguments.push(args[n]);

		return r;
	}

	type_result NEModule::_onArgumentsFetched(NEArgumentInterfaceList& tray)
	{
		return RESULT_SUCCESS;
	}

	type_result NEModule::initialize()
	{
		_arguments.release();
		
		return _bindArguments();
	}

	NEModule& NEModule::_assign(const ThisClass& rhs)
	{
		if(this == &rhs) return *this;

		_arguments = rhs._arguments;

		return *this;
	}
}
