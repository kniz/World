#include "../../StandardSelectorDialog.hpp"

namespace NE
{

	NEObject NE_DLL &StandardSelectorDialog::NodeTypeList::clone() const
	{
		return *(new NodeTypeList(*this));
	}
	
	type_result StandardSelectorDialog::NodeTypeList::_onLoad(NEPanel& panel)
	{
		_caption = _T("노드타입");
		_comment = _T("셀렉터의 노드타입을 선택하세요");
	
		_contents.create(6);
		_contents.push( _T("RECENT") );
		_contents.push( _T("NAME") );
		_contents.push( _T("SCRIPT") );
		_contents.push( _T("GROUP") );
		_contents.push( _T("PRIORITY") );
		_contents.push( _T("ALL") );
		
		selectContent(0);
		
		return _onFocus(panel);
	}
	
	type_result StandardSelectorDialog::NodeTypeList::_onFocus(NEPanel& panel)
	{
		StandardSelectorDialog& selector_dialog = static_cast<StandardSelectorDialog&>(panel);		
		NENodeSelectorInterface& selector = selector_dialog._changeKeyToNodeSelectorInterface();
		if(! &selector)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR | THERE_IS_NO_SELECTOR;
		}
		
		
		NECodeType::CodeType type = selector.getNodeType();
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
		case NECodeType::GROUP:
			selectContent(3);
			break;
		case NECodeType::PRIORITY:
			selectContent(4);
			break;
		case NECodeType::ALL:
			selectContent(5);
			break;
		default:
			EDITOR_WARNING(" : ")
			selectContent(NE_INDEX_ERROR);
			return RESULT_TYPE_WARNING | FALSE_INDEX_FROM_NODE_TYPE_LIST;
		}
		
		return RESULT_SUCCESS;
	}

	type_result StandardSelectorDialog::NodeTypeList::_onUpdate(NEPanel& panel)
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
			selector.setNodeType(NECodeType::GROUP);
			break;
		case 4:
			selector.setNodeType(NECodeType::PRIORITY);
			break;
		case 5:
			selector.setNodeType(NECodeType::ALL);
			break;
		default:
			EDITOR_WARNING(" : ")
			return RESULT_TYPE_WARNING | FALSE_INDEX_FROM_NODE_TYPE_LIST;
		}
		
		return RESULT_SUCCESS;		
	}
}
