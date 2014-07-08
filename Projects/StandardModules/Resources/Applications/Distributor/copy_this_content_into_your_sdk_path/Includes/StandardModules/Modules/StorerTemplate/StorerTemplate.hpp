#pragma once

#include "../../Includes/include.hpp"

namespace NE
{
	template 
	<
		typename KeyClass, 
		LPCTSTR _NAME, 
		LPCTSTR _DEVELOPER, 
		int _REVISION, 
		LPCTSTR _VERSION, 
		LPCTSTR _COMMENT,
		LPCTSTR _DATE,
		int _DEPENDENCIES_COUNT
	>
	class NE_DLL StorerTemplate : public NEModule // 표준 모듈에서만 사용하도록 NE_DLL 선언한다
	{
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"
#include "innerclass/Connector/Connector.hpp"

	public:
		StorerTemplate();
		StorerTemplate(const StorerTemplate& source);

	public:
		virtual ~StorerTemplate();

	public:
		virtual type_result initialize();

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	public:
		virtual type_result execute();	

	public:
		virtual NEObject& clone() const;

	public:
		Connector& getConnector();

	protected:
		Connector _connector;
	};
}

#include "StorerTemplate.inl"