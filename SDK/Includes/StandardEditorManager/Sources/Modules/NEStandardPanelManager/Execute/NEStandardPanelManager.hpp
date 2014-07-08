#pragma once

#include "../../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL NEStandardPanelManager : public NEPanelManager
	{
	public:
		#include "innerclass/ErrorCode/ErrorCode.hpp"
		#include "innerclass/StandardPanelDLLHeader/StandardPanelDLLHeader.hpp"

	public:
		NEStandardPanelManager();
		NEStandardPanelManager(const NEStandardPanelManager& source);

	public:
		virtual ~NEStandardPanelManager();
		
	public:
		const NEStandardPanelManager& operator=(const NEStandardPanelManager& source);
		bool operator==(const NEStandardPanelManager& source);
		bool operator!=(const NEStandardPanelManager& source);
		
	public:
		virtual NEPanel& getPanel(const NEExportable::Identifier& identifier);
		virtual const NEPanel& getPanel(const NEExportable::Identifier& identifier) const;
		virtual const NEPanelManager::DLLHeaderList& getPanelHeaderList() const;
		virtual NEPanelSet& getPanelSet();
		virtual const NEPanelSet& getPanelSet() const;
		
	public:
		virtual type_result initialize();

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	private:
		virtual type_result execute();

	public:
		virtual void release();
		virtual type_result isValid() const;
		virtual NEObject& clone() const;
		
	protected:
		const NEStandardPanelManager& _assign(const NEStandardPanelManager& source);
		void _release();
		void _linkPanel();
		void _pushPanelSet(NEPanelList& buffer);		
		void _filterNestedName(NEPanelList& source);
		void _linkDLL();
		void _pushDLLHeader(LPCTSTR dllpath);
		type_result _onModuleFetched();

	protected:
		NEPanelManager::DLLHeaderList _dllheaderset;
		NEPanelSet _panelset;
	};
}
