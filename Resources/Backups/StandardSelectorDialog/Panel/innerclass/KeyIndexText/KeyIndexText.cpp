#include "../../StandardSelectorDialog.hpp"

namespace NE
{

	NEObject NE_DLL &StandardSelectorDialog::KeyIndexText::clone() const
	{
		return *(new KeyIndexText(*this));
	}

	type_result StandardSelectorDialog::KeyIndexText::_onLoad(NEPanel& panel)
	{
		_caption = _T("키 인덱스");
		_comment = _T("선택된 모듈의 몇번째 키를 반환할까요?");

		return _onFocus(panel);
	}	

	type_result StandardSelectorDialog::KeyIndexText::_onFocus(NEPanel& panel)
	{
		StandardSelectorDialog& selector_dialog = static_cast<StandardSelectorDialog&>(panel);		
		NEKeySelectorInterface& selector = selector_dialog._changeKeyToKeySelectorInterface();
		if(! &selector)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR | THERE_IS_NO_SELECTOR;
		}



		_text = NETString(selector.getKeyIndex());

		return RESULT_SUCCESS;
	}

	type_result StandardSelectorDialog::KeyIndexText::_onUpdate(NEPanel& panel)
	{
		//	pre:
		StandardSelectorDialog& selector_dialog = static_cast<StandardSelectorDialog&>(panel);		
		NEKeySelectorInterface& selector = selector_dialog._changeKeyToKeySelectorInterface();
		if(! &selector)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR | THERE_IS_NO_SELECTOR;
		}
		type_index index = _text.toInt();
		if(index < 0)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR | KEY_INDEX_IS_LOWER_THAN_ZERO;
		}



		//	main:
		selector.setKeyIndex(index);
		return RESULT_SUCCESS;		
	}
}
