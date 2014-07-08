#pragma once

#include "../../../include/include.hpp"

namespace NE
{
	class NE_DLL StandardSelectorDialog : public NEDialog
	{
	public:
		#include "innerclass/ErrorCode/ErrorCode.hpp"
		#include "innerclass/NodeTypeList/NodeTypeList.hpp"
		#include "innerclass/CountLimitText/CountLimitText.hpp"
		#include "innerclass/NodeCodeSetModifiableList/NodeCodeSetModifiableList.hpp"
		#include "innerclass/AndOperationSwitch/AndOperationSwitch.hpp"
		#include "innerclass/ModuleTypeList/ModuleTypeList.hpp"
		#include "innerclass/ModuleCodeSetModifiableList/ModuleCodeSetModifiableList.hpp"
		#include "innerclass/KeyIndexText/KeyIndexText.hpp"
	public:
		friend class NodeTypeList;
		friend class CountLimitText;
		friend class NodeCodeSetModifiableList;
		friend class AndOperationSwitch;
		friend class MoudleTypeList;
		friend class ModuleCodeSetModifiableList;
		friend class KeyIndexText;
	
	public:
		StandardSelectorDialog();
		StandardSelectorDialog(const StandardSelectorDialog& source);
		
	public:
		virtual ~StandardSelectorDialog();
		
	public:
		type_result initialize();

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	public:
		virtual NEObject& clone() const;
		
	public:
		NEKey& getSelector();
		const NEKey& getSelector() const;
		type_result setSelector(NEKey& selector);
		
	protected:
		NENodeSelectorInterface& _changeKeyToNodeSelectorInterface();
		NEModuleSelectorInterface& _changeKeyToModuleSelectorInterface();
		NEKeySelectorInterface& _changeKeyToKeySelectorInterface();
				
	protected:
		NEKey* _selector;
	};
}
