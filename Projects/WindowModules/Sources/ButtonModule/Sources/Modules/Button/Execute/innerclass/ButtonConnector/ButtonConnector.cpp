#include "../../Button.hpp"
#include "../../../define/define.hpp"

namespace NE
{
	NE_DLL Button::ButtonConnector::ButtonConnector()
		: WND::WNDConnector()
	{
		_release();
	}

	NE_DLL Button::ButtonConnector::~ButtonConnector()
	{

	}

	type_result NE_DLL Button::ButtonConnector::connect(NEKeyCodeSet& keyset)
	{
		//	pre:
		WND::WNDConnector::connect(keyset);
		if( ! &keyset)
		{
			//ALERT_ERROR(" : 주어진 키셋이 널입니다.")

			return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		}
		if(keyset.getLength() < 8)
		{
			//ALERT_ERROR(" : 주어진 키셋에 키가 하나도 없습니다. 연결이 불가능합니다.")

			return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		}



		//	main:
		_window_selector = static_cast<NEModuleSelector*>( &(keyset[5]) );
		_caption = static_cast<NETStringKey*>( &(keyset[6]) );
		_menu_id = static_cast<NEIntKey*>( &(keyset[7]) );

		return RESULT_SUCCESS;
	}

	NEModuleSelector NE_DLL &Button::ButtonConnector::getWindowSelector()
	{
		return *_window_selector;
	}

	const NEModuleSelector NE_DLL &Button::ButtonConnector::getWindowSelector() const
	{
		return *_window_selector;
	}

	NETStringKey NE_DLL &Button::ButtonConnector::getCaption() 
	{
		return *_caption;
	}

	const NETStringKey NE_DLL &Button::ButtonConnector::getCaption() const
	{
		return *_caption;
	}

	NEIntKey NE_DLL &Button::ButtonConnector::getMenuId()
	{
		return *_menu_id;
	}

	const NEIntKey NE_DLL &Button::ButtonConnector::getMenuId() const
	{
		return *_menu_id;
	}

	void Button::ButtonConnector::_release()
	{
		_x = NE_NULL;
		_y = NE_NULL;
		_width = NE_NULL;
		_height = NE_NULL;
		_command_show = NE_NULL;
		_window_selector = NE_NULL;
		_caption = NE_NULL;
		_menu_id = NE_NULL;
	}
}