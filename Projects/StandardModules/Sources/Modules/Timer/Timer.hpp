#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL Timer : public NEModule
	{
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		Timer();
		Timer(const Timer& source);

	public:
		virtual ~Timer();

	public:
		virtual type_result initialize();

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	public:
		virtual type_result execute();	

	public:
		virtual NEObject& clone() const;

	private:
		type_uint _time_evaluated_before;
		static type_int _count_of_instance;
	};
}
