#include "../../StorerTemplate.hpp"
#include "../../define/define.hpp"

namespace NE
{
	template <TEMPLATE_SIGNATURE>
	NE_DLL StorerTemplate<TEMPLATE_PARAMETERS>::Connector::Connector()
		: _storage(NE_NULL)
	{
		
	}

	template <TEMPLATE_SIGNATURE>
	NE_DLL StorerTemplate<TEMPLATE_PARAMETERS>::Connector::~Connector()
	{
		
	}

	template <TEMPLATE_SIGNATURE>
	type_result NE_DLL StorerTemplate<TEMPLATE_PARAMETERS>::Connector::connect(NEKeyCodeSet& keyset)
	{
		//	pre:
		if( ! &keyset)
		{
			//ALERT_ERROR(" : 주어진 키셋이 널입니다.")

			return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		}
		if(keyset.getLength() <= 0)
		{
			//ALERT_ERROR(" : 주어진 키셋에 키가 하나도 없습니다. 연결이 불가능합니다.")

			return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		}



		//	main:
		_storage = static_cast<KeyClass*>( &(keyset[0]) );

		return RESULT_SUCCESS;
	}

	template <TEMPLATE_SIGNATURE>
	KeyClass NE_DLL &StorerTemplate<TEMPLATE_PARAMETERS>::Connector::getStorage()
	{
		return *_storage;
	}

	template <TEMPLATE_SIGNATURE>
	const KeyClass NE_DLL &StorerTemplate<TEMPLATE_PARAMETERS>::Connector::getStorage() const 
	{
		return *_storage;
	}
}