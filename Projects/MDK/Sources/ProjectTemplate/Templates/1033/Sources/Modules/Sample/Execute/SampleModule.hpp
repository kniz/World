#pragma once

#include "../../../includes/include.hpp"

namespace NE
{
	class NE_DLL [!output module_name] : public NEModule
	{
	public:
		#include "innerclass/ErrorCode/ErrorCode.hpp"

		public:
			class NE_DLL Connector : public NEModule::BaseConnector
			{
			public:
				Connector();

			public:
				type_result connect(NEKeySet& keyset);
				
			public:
				NEStringKey& getHelloWorld();

			protected:
				NEStringKey* _helloworld;
			};

	public:
		[!output module_name]();
		[!output module_name](const [!output module_name]& source);

	public:
		virtual ~[!output module_name]();
		
	public:
		Connector& getConnector();
		const Connector& getConnector() const;

	public:
		virtual type_result initialize();

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	public:
		virtual type_result execute();	

	public:
		virtual NEObject& clone() const;

	protected: 
		Connector _connector;
	};
}
