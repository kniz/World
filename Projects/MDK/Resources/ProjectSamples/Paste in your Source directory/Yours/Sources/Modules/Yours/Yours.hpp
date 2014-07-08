#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{

	class Window;

	class NE_DLL WNDShowManipulator : public NEModule
	{
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		WNDShowManipulator();
		WNDShowManipulator(const WNDShowManipulator& source);

	public:
		virtual ~WNDShowManipulator();

	public:
		const WNDShowManipulator& operator=(const WNDShowManipulator& source);

	public:
		virtual type_result initialize();

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	public:
		virtual type_result execute();

	public:
		virtual NEObject& clone() const;
	};
}