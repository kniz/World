#include "../../StandardSelectorDialog.hpp"

namespace NE
{

	NEObject NE_DLL &StandardSelectorDialog::ModuleCodeSetModifiableList::clone() const
	{
		return *(new ModuleCodeSetModifiableList(*this));
	}

	type_result StandardSelectorDialog::ModuleCodeSetModifiableList::_onLoad(NEPanel& panel)
	{
		_caption = _T("모듈 코드셋 입력");
		_comment = _T("현재 노드타입에 원하는 코드를 입력하세요.");

		return _onFocus(panel);
	}

	type_result StandardSelectorDialog::ModuleCodeSetModifiableList::_onFocus(NEPanel& panel)
	{
		StandardSelectorDialog& selector_dialog = static_cast<StandardSelectorDialog&>(panel);		
		NEModuleSelectorInterface& selector = selector_dialog._changeKeyToModuleSelectorInterface();
		if(! &selector)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR | THERE_IS_NO_SELECTOR;
		}



		//	main:
		//		타게팅:
		const NECodeSet& codeset = selector.getModuleCodeSet();
		//		콘텐츠 초기화:
		//			크기 정의:
		_contents.create(codeset.getLength());
		//			콘텐츠 할당:
		for(int n=0; n < codeset.getLength() ;n++)
		{
			type_code code = codeset[n];
			_contents.push( NETString(code) );
		}

		return RESULT_SUCCESS;
	}

	type_result StandardSelectorDialog::ModuleCodeSetModifiableList::_onUpdate(NEPanel& panel)
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
		//		버퍼 초기화:
		NECodeSet codeset(_contents.getLength());
		//		버퍼 할당:
		for(int n=0; n < _contents.getLength() ;n++)
		{
			NETString& content = _contents[n];

			codeset.push(content.toInt());
		}



		//	post:
		//		셀렉터 적용:
		selector.setModuleCodeSet(codeset);
		return RESULT_SUCCESS;
	}
}
