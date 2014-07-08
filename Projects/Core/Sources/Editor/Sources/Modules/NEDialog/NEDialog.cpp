#include "NEDialog.hpp"
#include "../NEDebugManager/innerclass/EditDebugMacro/EditDebugMacro.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL NEDialog::NEDialog()
		: NEPanel()
	{
		_caller = NE_NULL;
		_disable_the_caller = _DEFAULT_OF_DISABLE_THE_CALLER;
		_component_index_to_call = _THERE_IS_NO_COMPONENT_INDEX;
	}

	NE_DLL NEDialog::NEDialog(const NEDialog& source)
		: NEPanel(source)
	{
		_assign(source);
	}

	NE_DLL NEDialog::~NEDialog()
	{

	}

	const NEDialog NE_DLL &NEDialog::operator=(const NEDialog& source)
	{
		NEPanel::operator=(source);

		return _assign(source);
	}

	bool NE_DLL NEDialog::operator==(const NEDialog& source) const
	{
		if(this == &source) return true;
		if(NEPanel::operator!=(source)) return false;
		if(_disable_the_caller != source._disable_the_caller) return false;
		if(_caller != source._caller) return false;
		if(_component_index_to_call != source._component_index_to_call) return false;

		return true;
	}

	bool NE_DLL NEDialog::operator!=(const NEDialog& source) const
	{
		return ! (operator==(source));
	}
	
	type_result NE_DLL NEDialog::setCaller(NEPanel& caller, type_index component_index_to_call)
	{
		if( ! &caller)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR;
		}
		if(component_index_to_call < 0 || component_index_to_call > caller.getComponentSet().getLengthLastIndex())
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR;
		}
		
		
		
		_caller = &caller;
		_component_index_to_call = component_index_to_call;
		
		return RESULT_SUCCESS;
	}
	
	NEPanel NE_DLL &NEDialog::getCaller()
	{
		return *_caller;
	}

	const NEPanel NE_DLL &NEDialog::getCaller() const
	{
		return *_caller;
	}

	type_index NE_DLL NEDialog::getComponentIndexToCall() const
	{
		return _component_index_to_call;
	}

	bool NE_DLL NEDialog::willDisableTheCaller() const
	{
		return _disable_the_caller;
	}

	NEType::Type NE_DLL NEDialog::getType() const
	{
		return NEType::NEDIALOG;
	}
	void NE_DLL NEDialog::release()
	{
		NEPanel::release();

		_component_index_to_call = _THERE_IS_NO_COMPONENT_INDEX;	
	}
	type_result NE_DLL NEDialog::onLoad()
	{
		//	pre:
		if(!_caller)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR | RESULT_WRONG_BOUNDARY | RESULT_INVALID_DATA | RESULT_ABORT_ACTION;
		}



		//	main:
		//		패널에 이벤트 전달:
		NEPanel::onLoad();
		if(_disable_the_caller)
			_caller->setEnable(false);
		
		return RESULT_SUCCESS;
	}
	type_result NE_DLL NEDialog::onUnload()
	{	
		if(!_caller)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR | RESULT_WRONG_BOUNDARY | RESULT_INVALID_DATA | RESULT_ABORT_ACTION;
		}



		//	main:
		//		패널을 회생:
		if(_disable_the_caller)
			_caller->setEnable(true);
		


		//	post:		
		//		자신을 삭제(Unload)하기 전에 Parent에게 자신을 전달해야 한다
		//		그래야만 Parent에서 자신의 변수를 참조ㅏ할 수 있으므로.
		//		컴포넌트를 지정하지 않았다면:
		if(_component_index_to_call <= _THERE_IS_NO_COMPONENT_INDEX)
			_caller->onDialogReturned(*this);
		else	//	컴포넌트를 지정했다면:
			_caller->onDialogReturned(_component_index_to_call, *this);
			
		
		//		Panel 호출:
		NEPanel::onUnload();		
		
		return RESULT_SUCCESS;
	}

	const NEDialog& NEDialog::_assign(const NEDialog& source)
	{
		if(this == &source) return *this;
		
		_disable_the_caller = source._disable_the_caller;
		_caller = source._caller;
		_component_index_to_call = source._component_index_to_call;		

		return *this;
	}

	void NE_DLL NEDialog::disconnectCaller()
	{
		_caller = NE_NULL;
		_component_index_to_call = _THERE_IS_NO_COMPONENT_INDEX;
	}
}
