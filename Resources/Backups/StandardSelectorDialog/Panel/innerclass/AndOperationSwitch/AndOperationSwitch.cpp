#include "../../StandardSelectorDialog.hpp"

namespace NE
{

	NEObject NE_DLL &StandardSelectorDialog::AndOperationSwitch::clone() const
	{
		return *(new AndOperationSwitch(*this));
	}

	type_result StandardSelectorDialog::AndOperationSwitch::_onLoad(NEPanel& panel)
	{
		_caption = _T("And 필터링 사용");
		_comment = _T("Group코드로 검색시 코드셋에 대해 AND 필터링을 적용합니다. 그룹코드시에만 유효합니다.");

		return _onFocus(panel);
	}
	
	type_result StandardSelectorDialog::AndOperationSwitch::_onFocus(NEPanel& panel)
	{
		StandardSelectorDialog& selector_dialog = static_cast<StandardSelectorDialog&>(panel);		
		NENodeSelectorInterface& selector = selector_dialog._changeKeyToNodeSelectorInterface();
		if(! &selector)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR | THERE_IS_NO_SELECTOR;
		}

		setSwitch(selector.isUsingAndOperation());

		return RESULT_SUCCESS;
	}

	type_result StandardSelectorDialog::AndOperationSwitch::_onUpdate(NEPanel& panel)
	{
		//	pre:
		StandardSelectorDialog& selector_dialog = static_cast<StandardSelectorDialog&>(panel);		
		NENodeSelectorInterface& selector = selector_dialog._changeKeyToNodeSelectorInterface();
		if(! &selector)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR | THERE_IS_NO_SELECTOR;
		}



		//	main:
		selector.setUsingAndOperation(isSwitchOn());
		return RESULT_SUCCESS;		
	}
}
