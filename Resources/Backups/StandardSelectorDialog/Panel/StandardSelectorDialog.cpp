#include "StandardSelectorDialog.hpp"
#include "../define/define.hpp"

#include <iostream>

namespace NE
{
	NE_DLL StandardSelectorDialog::StandardSelectorDialog()
		: NEDialog(), _selector(NE_NULL)
	{
		
	}

	NE_DLL StandardSelectorDialog::StandardSelectorDialog(const StandardSelectorDialog& source)
		: NEDialog(source)
	{
		_selector = source._selector;
	}

	NE_DLL StandardSelectorDialog::~StandardSelectorDialog()
	{

	}
	
	type_result NE_DLL StandardSelectorDialog::initialize()
	{
		//	pre:
		if( !_selector)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR | THERE_IS_NO_SELECTOR;
		}		
		
			
			
		//	main:
		//		타입 확인:
		int type = 0;
		if(_selector->isSubClassOf(NEType::NEKEY_SELECTOR_INTERFACE))
		{
			_componentset.create(7);
			type = 3;
		}
		else if(_selector->isSubClassOf(NEType::NEMODULE_SELECTOR_INTERFACE))
		{
			_componentset.create(6);
			type = 2;
		}
		else if(_selector->isSubClassOf(NEType::NENODE_SELECTOR_INTERFACE))
		{
			_componentset.create(4);
			type = 1;
		}
		//		타입에 따른 초기화:
		/*
					break를 쓰지 않는다는 점에 주목하라.
		*/
		switch(type)
		{
		case 3:
			_componentset.push( KeyIndexText() );
		case 2:
			_componentset.push( ModuleCodeSetModifiableList() );
			_componentset.push( ModuleTypeList() );
		case 1:
			_componentset.push( AndOperationSwitch() );
			_componentset.push( NodeCodeSetModifiableList() );
			_componentset.push( CountLimitText() );
			_componentset.push( NodeTypeList() );
			break;
		default:
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR | SELECTOR_IS_NOT_SUB_CLASS_OF_NODE_SELECTOR_INTERFACE;
		}
		
		
		return RESULT_SUCCESS;
	}


	NEObject NE_DLL &StandardSelectorDialog::clone() const
	{
		return *(new StandardSelectorDialog(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &StandardSelectorDialog::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T( _NAME );
			_header.getDeveloper() = _T( _DEVELOPER );
			_header.setRevision(_REVISION);
			_header.getComment()  = _T( _COMMENT );
			_header.getVersion()  = _T( _VERSION );
			_header.getReleaseDate() = _T( _DATE );
			_header.getModuleDependencies().create(_DEPENDENCIES_COUNT);
			_header.setMaxErrorCodeCount(StandardSelectorDialog::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL StandardSelectorDialog::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case PANEL_IS_NOT_VALID:
			return _T("잘못된 Module");

		case THERE_IS_NO_SELECTOR:
			return _T("셀렉터가 없음. 혹은 연결되지 않았음.");

		case KEY_INDEX_IS_LOWER_THAN_ZERO:
			return _T("키의 인덱스가 0보다 작다.");

		case COUNT_LIMIT_IS_LOWER_THAN_ZERO:
			return _T("Count Limit가 0보다 작다.");

		case FALSE_INDEX_FROM_NODE_TYPE_LIST:
			return _T("노드타입리스트 컴포넌트에서 잘못된 인덱스가 선택되었다.");

		case FALSE_INDEX_FROM_MODULE_TYPE_LIST:
			return _T("모듈타입리스트 텀포넌트에서 잘못된 인덱스가 선택되었다.");

		case SELECTOR_IS_NOT_SUB_CLASS_OF_NODE_SELECTOR_INTERFACE:
			return _T("셀렉터가 존재하지만, 노드셀렉터 인터페이스가 아니다.");

		default:
			return _T("알수 없는 에러");
		}
	}

	type_result NE_DLL StandardSelectorDialog::setSelector(NEKey& selector)
	{
		//	pre:
		if( ! &selector)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR | THERE_IS_NO_SELECTOR;
		}
		if( ! selector.isSubClassOf(NEType::NENODE_SELECTOR_INTERFACE))
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR | SELECTOR_IS_NOT_SUB_CLASS_OF_NODE_SELECTOR_INTERFACE;
		}
		
		
		
		//	main:
		_selector = &selector;
		
		
		
		//	post:
		return initialize();
	}

	const NEKey NE_DLL &StandardSelectorDialog::getSelector() const
	{
		return *_selector;
	}

	NEKey NE_DLL &StandardSelectorDialog::getSelector()
	{
		return *_selector;
	}

	NENodeSelectorInterface& StandardSelectorDialog::_changeKeyToNodeSelectorInterface()
	{
		NENodeSelectorInterface* null_pointer = NE_NULL;
		if( ! _selector)
		{
			EDITOR_ERROR(" : ")
			return *null_pointer;
		}
		if( ! _selector->isSubClassOf(NEType::NENODE_SELECTOR_INTERFACE))
		{
			EDITOR_ERROR(" : ")
			return *null_pointer;
		}
		
		
		return static_cast<NENodeSelectorInterface&>(*_selector);		
	}

	NEModuleSelectorInterface& StandardSelectorDialog::_changeKeyToModuleSelectorInterface()
	{
		NEModuleSelectorInterface* null_pointer = NE_NULL;
		if( ! _selector)
		{
			EDITOR_ERROR(" : ")
				return *null_pointer;
		}
		if( ! _selector->isSubClassOf(NEType::NEMODULE_SELECTOR_INTERFACE))
		{
			EDITOR_ERROR(" : ")
				return *null_pointer;
		}


		return static_cast<NEModuleSelectorInterface&>(*_selector);
	}

	NEKeySelectorInterface& StandardSelectorDialog::_changeKeyToKeySelectorInterface()
	{
		NEKeySelectorInterface* null_pointer = NE_NULL;
		if( ! _selector)
		{
			EDITOR_ERROR(" : ")
				return *null_pointer;
		}
		if( ! _selector->isSubClassOf(NEType::NEKEY_SELECTOR_INTERFACE))
		{
			EDITOR_ERROR(" : ")
				return *null_pointer;
		}


		return static_cast<NEKeySelectorInterface&>(*_selector);
	}
}
