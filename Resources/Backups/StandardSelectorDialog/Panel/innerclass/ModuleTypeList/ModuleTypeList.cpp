#include "../../StandardSelectorDialog.hpp"

namespace NE
{

	NEObject NE_DLL &StandardSelectorDialog::ModuleTypeList::clone() const
	{
		return *(new ModuleTypeList(*this));
	}

	type_result StandardSelectorDialog::ModuleTypeList::_onLoad(NEPanel& panel)
	{
		_caption = _T("모듈타입");
		_comment = _T("셀렉터의 모듈타입을 선택하세요");

		_contents.create(4);
		_contents.push( _T("RECENT") );
		_contents.push( _T("NAME") );
		_contents.push( _T("SCRIPT") );
		_contents.push( _T("ALL") );

		selectContent(0);

		return _onFocus(panel);
	}

	type_result StandardSelectorDialog::ModuleTypeList::_onFocus(NEPanel& panel)
	{
		StandardSelectorDialog& selector_dialog = static_cast<StandardSelectorDialog&>(panel);		
		NEModuleSelectorInterface& selector = selector_dialog._changeKeyToModuleSelectorInterface();
		if(! &selector)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR | THERE_IS_NO_SELECTOR;
		}


		NECodeType::CodeType type = selector.getModuleType();
		switch(type)
		{
		case NECodeType::RECENT:
			selectContent(0);
			break;
		case NECodeType::NAME:
			selectContent(1);
			break;
		case NECodeType::SCRIPT:
			selectContent(2);			
			break;
		case NECodeType::ALL:
			selectContent(3);
			break;
		default:
			EDITOR_WARNING(" : ")
			selectContent(NE_INDEX_ERROR);
			return RESULT_TYPE_WARNING;
		}

		return RESULT_SUCCESS;
	}

	type_result StandardSelectorDialog::ModuleTypeList::_onUpdate(NEPanel& panel)
	{
		//	pre:
		StandardSelectorDialog& selector_dialog = static_cast<StandardSelectorDialog&>(panel);		
		NEModuleSelectorInterface& selector = selector_dialog._changeKeyToModuleSelectorInterface();
		if(! &selector)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR | THERE_IS_NO_SELECTOR;
		}



		//	main:
		switch(getSelectedContentIndex())
		{
		case 0:
			selector.setNodeType(NECodeType::RECENT);
			break;
		case 1:
			selector.setNodeType(NECodeType::NAME);
			break;
		case 2:
			selector.setNodeType(NECodeType::SCRIPT);
			break;		
		case 3:
			selector.setNodeType(NECodeType::ALL);
			break;
		default:
			EDITOR_WARNING(" : ")
			return RESULT_TYPE_WARNING | FALSE_INDEX_FROM_MODULE_TYPE_LIST;
		}

		return RESULT_SUCCESS;		
	}
}
