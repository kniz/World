#pragma once

#include "../../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL CooeeHandler : public NEEventHandler
	{
	public:
		#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		CooeeHandler();
		CooeeHandler(const CooeeHandler& source);

	public:
		virtual ~CooeeHandler();
		
	public:
		const CooeeHandler& operator=(const CooeeHandler& source);
		bool operator==(const CooeeHandler& source) const;
		bool operator!=(const CooeeHandler& source) const;
		
	public:
		virtual type_result execute();
		
	public:
		virtual type_result initialize();
		
	public:
		virtual type_result runTest();
		virtual type_result initializeNewFile();
		virtual type_result onCallingDialog(NEPanel& caller_of_panel, type_index component_index_to_call, NEDialog& dialog)
		{
			return RESULT_SUCCESS;
		}
		virtual type_result onCallingPanel(NEPanel& panel, NEModule& module_to_be_modified)
		{
			return RESULT_SUCCESS;
		}
		virtual type_result onModifyingKey(NEKey& key)
		{
			return RESULT_SUCCESS;
		}
		
	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	public:
		virtual NEObject& clone() const;
		virtual type_result isValid() const;
		virtual void release();
				
	protected:		
		Kernal::Factory _getKernalFactory() const;

	protected:
		Kernal* _test_kernal;
	};
}
