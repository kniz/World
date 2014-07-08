#include "../../StandardSelectorDialog.hpp"

namespace NE
{

	NEObject NE_DLL &StandardSelectorDialog::CountLimitText::clone() const
	{
		return *(new CountLimitText(*this));
	}

	type_result StandardSelectorDialog::CountLimitText::_onLoad(NEPanel& panel)
	{
		_caption = _T("검색 횟수 입력");
		_comment = _T("한번 검색시, 몇개를 검색할지 입력하세요.\n0을 입력하면 모든 노드를 검색하게되고, 정수형태로 양수를 입력하면 그 횟수만큼 노드를 검색합니다.");

		return _onFocus(panel);
	}	

	type_result StandardSelectorDialog::CountLimitText::_onFocus(NEPanel& panel)
	{
		StandardSelectorDialog& selector_dialog = static_cast<StandardSelectorDialog&>(panel);		
		NENodeSelectorInterface& selector = selector_dialog._changeKeyToNodeSelectorInterface();
		if(! &selector)
		{
			EDITOR_ERROR(" : ")
				return RESULT_TYPE_ERROR | THERE_IS_NO_SELECTOR;
		}
		
		
		
		_text = NETString(selector.getCountLimit());
		
		return RESULT_SUCCESS;
	}

	type_result StandardSelectorDialog::CountLimitText::_onUpdate(NEPanel& panel)
	{
		//	pre:
		StandardSelectorDialog& selector_dialog = static_cast<StandardSelectorDialog&>(panel);		
		NENodeSelectorInterface& selector = selector_dialog._changeKeyToNodeSelectorInterface();
		if(! &selector)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR | THERE_IS_NO_SELECTOR;
		}
		type_count count = _text.toInt();
		if(count < 0)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR | COUNT_LIMIT_IS_LOWER_THAN_ZERO;
		}



		//	main:		
		selector.setCountLimit(count);
		
		
		
		//	post:
		_text = NETString(count);
		return RESULT_SUCCESS;		
	}
}
