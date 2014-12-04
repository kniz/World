#include "ObservePopUpMenu.hpp"
#include "../Core/Core.hpp"

ObservePopUpMenu::ObservePopUpMenu()
: LG::ListWindow("���� > ", 30, 8, 19, 5, BLACK, WHITE, WHITE, LIGHTGREEN)
{

}

void ObservePopUpMenu::onUpdateData()
{
	list.items.create(2);
	list.items.push("�ö��Ÿ����");
	NEEventHandler& handler = Editor::getInstance().getEventHandler();
	if(	handler.getHeader().getName() == "CooeeHandler"	&&
		handler.getHeader().getDeveloper() == "kniz"	)
		if( ::Core::isObservingDebug() )
			list.items.push("��ũ��Ʈ ���� ����");
		else
			list.items.push("�׽�Ʈ ���� ����");			
}

void ObservePopUpMenu::onItemChoosed(type_index item_index, const NEString& chosen_content)
{
	NEEventHandler& handler = Editor::getInstance().getEventHandler();

	switch(item_index)
	{
	case 0:	//	�ö��Ÿ����
		::Core::commander.command("planetarium");
		toCaller().delete_me = delete_me = true;
		break;

	case 1:	//	����
		::Core::commander.command("observe");
		toCaller().delete_me = delete_me = true;
		break;
	}
}