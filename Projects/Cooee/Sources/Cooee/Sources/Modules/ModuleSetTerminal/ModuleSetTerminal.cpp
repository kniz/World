#include "ModuleSetTerminal.hpp"
#include "../ModuleEncyclo/ModuleEncyclo.hpp"

class NameInputWindow : public ::LG::InputWindow
{
public:
	NameInputWindow(const NEString& default_string) : InputWindow("새로운 키의 이름을 입력해주시기 바랍니다.", BLACK, LIGHTCYAN, default_string) {}

	FUNC_TO_CALLER(ModuleSetTerminal)
	FUNC_CLONE(NameInputWindow)

	virtual void onInputed()
	{
		toCaller().real_key->getName() = input.text;
		delete_me = true;
	}
};

void ModuleSetTerminal::ModuleNameList::onKeyPressed(char inputed) 
{
	ListGliph::onKeyPressed(inputed);

	switch(inputed) {
	case CONFIRM:
		{
			const NEModuleSet& ms = Kernal::getInstance().getModuleManager().getModuleSet();
		
			if(choosed < 0 || choosed > ms.getLengthLastIndex())	return;

			int index = toOwner()->real_key ? choosed-1 : choosed;
			if(index == -1)
				toOwner()->call(NameInputWindow(toOwner()->real_key->getName()));
			else
				LG::Core::windows.pushFront(ModuleEncyclo(false, &toOwner()->castObject()[index]));
		}	
		break;
	case CANCEL:
		if(LG::Core::windows.getLength() == 1)
			Core::pushMessage("여기가 최상위 노드.\n우리에겐, 더 돌아갈 장소따윈 없어요.");
		else
			toOwner()->delete_me = true;
		break;
	case UP:
	case DOWN:
		onDraw();
	}	
}

