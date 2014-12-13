#include "NEEventHandler.hpp"
#include "../NEDialog/NEDialog.hpp"
#include "../Editor/Editor.hpp"

namespace NE
{
	NE_DLL NEEventHandler::NEEventHandler()
		: NEModule()
	{

	}

	NE_DLL NEEventHandler::NEEventHandler(const NEEventHandler& source)
		: NEModule(source)
	{

	}

	NE_DLL NEEventHandler::~NEEventHandler()
	{

	}

	NEType::Type NE_DLL NEEventHandler::getType() const
	{
		return NEType::NEEVENT_HANDLER;
	}

	type_result NE_DLL NEEventHandler::saveScriptFile(NETString& path_without_extraction) const
	{
		//	pre:
		//		타겟팅:
		Kernal& kernal = Kernal::getInstance();
		if( ! &kernal)
		{
			ALERT_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}
		NEScriptManager& scripter = kernal.getScriptManager();
		if( ! &scripter)
		{
			ALERT_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}
		Editor& editor = Editor::getInstance();
		if( ! &editor)
		{
			ALERT_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}
		NEScriptEditor& synchronizer = editor.getScriptEditor();
		if( ! &synchronizer)
		{
			ALERT_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}		
		//		저장 타겟팅:
		//			확장자가 붙어있는지 검사:
		const NETString& ext = kernal.getSettings().getScriptExtractor();
		const NETString& scr_dir = kernal.getSettings().getScriptDirectory();
		NETString path_with_extraction = path_without_extraction;
		if(path_without_extraction.find(ext).getLength() <= 0)
			path_with_extraction += _T(".") + ext;
		//			앞에 스크립트 디렉토리가 이미 붙었는지 검사:
		if(path_with_extraction.find(scr_dir) == NE_INDEX_ERROR)
			path_with_extraction = scr_dir + path_with_extraction;
		
		NEBinaryFileSaver saver(path_with_extraction.toCharPointer());

		saver.open();
		if( ! saver.isFileOpenSuccess())
		{
			ALERT_ERROR(" : 파일 저장 시도 실패. 경로가 잘못된 건 아닐런지요?\n\t열려던 경로 : %s", path_with_extraction.toCharPointer());
			return RESULT_TYPE_ERROR;
		}



		//	main:
		//		자동으로 NEScriptHeader의 Revision을 상승시킨다:
		NEScriptHeader& header = synchronizer.getScriptHeader();
		header.setRevision(header.getRevision() + 1);
		//		동기화:
		type_result result = synchronizer.synchronizeTo(scripter);
		if(NEResult::hasError(result))
		{
			ALERT_ERROR(" : ScriptEditor -> ScriptManager로 동기화 중에 에러가 발생했습니다.\n\t에러코드: %d", result);
			return RESULT_TYPE_ERROR;
		}
		//		동기화된 내용과 뱅크를 저장:		
		saver << scripter << synchronizer.getBanks();



		//	post:
		saver.close();
		return RESULT_SUCCESS;
	}

	type_result NE_DLL NEEventHandler::loadScriptFile(NETString& path_without_extraction)
	{
		//	pre:
		//		테스트 중지:
		stopTest();
		//		타겟팅:
		Editor& editor = Editor::getInstance();
		if( ! &editor)
		{
			ALERT_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}
		NEScriptEditor& synchronizer = editor.getScriptEditor();
		if( ! &synchronizer)
		{
			ALERT_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}		
		Kernal& kernal = Kernal::getInstance();
		if( ! &kernal)
		{
			ALERT_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}
		NEScriptManager& scripter = kernal.getScriptManager();
		if( ! &scripter)
		{
			ALERT_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}
		NENodeManager& noder = kernal.getNodeManager();
		if( ! &noder)
		{
			ALERT_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}
		//		저장 타겟팅:
		const NETString& ext = kernal.getSettings().getScriptExtractor();
		NETString path_with_extraction = (path_without_extraction.find(ext).getLength() <= 0) ? 
			kernal.getSettings().getScriptDirectory() + path_without_extraction + _T(".") + ext
			:
		kernal.getSettings().getScriptDirectory() + path_without_extraction;
		NEBinaryFileLoader loader(path_with_extraction.toCharPointer());

		loader.open();
		if( ! loader.isFileOpenSuccess())
		{
			ALERT_ERROR(" : 주어진 경로에 파일이 없어서 열지 못했습니다.\n\t주어진 경로: %s", path_with_extraction.toCharPointer());
			return RESULT_TYPE_ERROR;
		}



		//	main:
		//		로드:	일단 헤더, 스크립트 내용까지만 읽는다.
		//			왜 중간에 동기화 과정을 넣는가:
		//				동기화 하게 되면, 읽어들인 헤더정보를 이용해서 banks의 한계치(boundary)
		//				를 정해주기 때문이다.
		//				나중에 synchronize를 하게되면 이미 읽은 banks가 resize되면서 값이 손
		//				실될 가능성이 크다.
		loader >> scripter;		
		//		이후 읽은 스크립트를 동기화:
		type_result result = synchronizer.synchronizeFrom(scripter);
		if(NEResult::hasError(result))
		{
			ALERT_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}
		//		뱅크를 로드:
		loader >> synchronizer.getBanks();



		//	post
		//		ScriptManager 해제:	
		//			이 함수에서 ScriptManager는 버퍼 역할 이므로, 해제해야 한다.
		//			NodeManager는 ScriptManager.serialize(loader) 에서 initialize가 호출된다.
		//			따라서 여기에서 해제를 시켜준다.
		noder.release();
		scripter.release();
		loader.close();
		return RESULT_SUCCESS;
	}	

	type_result NE_DLL NEEventHandler::onCallingDialog(NEPanel& caller_of_panel, type_index component_index_to_call, const NEExportable::Identifier& dialog_identifier)
	{
		//	pre:
		if( ! &caller_of_panel)
		{
			EDITOR_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}
		if(component_index_to_call < 0)
		{
			EDITOR_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}
		if(! &dialog_identifier)
		{
			EDITOR_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}
		Editor& editor = Editor::getInstance();
		if( ! &editor)
		{
			EDITOR_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}
		NEPanelManager& paneler = editor.getPanelManager();
		if( ! &paneler)
		{
			EDITOR_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}



		//	main:
		NEPanel& panel = paneler.getPanel(dialog_identifier);
		if( ! &panel)
		{
			EDITOR_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}
		if( ! panel.isSubClassOf(NEType::NEDIALOG))
		{
			EDITOR_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}



		//	post:
		NEDialog& dialog = static_cast<NEDialog&>(panel);
		return onCallingDialog(caller_of_panel, component_index_to_call, dialog);
	}

	type_result NE_DLL NEEventHandler::onCallingDialog(NEPanel& caller_of_panel, NEComponent& caller_of_component, const NEExportable::Identifier& dialog_identifier)
	{
		//	pre:
		//		타게팅:
		Editor& editor = Editor::getInstance();
		if( ! &editor)
		{
			ALERT_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}
		NEPanelManager& paneler = editor.getPanelManager();
		if( ! &paneler)
		{
			ALERT_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}		
		//			다이얼로그 fetch:
		NEPanel& dialog = paneler.getPanel(dialog_identifier);
		if( ! &dialog)
		{
			ALERT_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}



		//	main:
		//		다이얼로그 세팅:
		NEComponentSet& componentset = caller_of_panel.getComponentSet();
		for(int n=0; n < componentset.getLength() ;n++)
		{
			NEComponent& component = componentset[n];
			if(&component == &caller_of_component)
				return onCallingDialog(caller_of_panel, n, dialog_identifier);
		}



		//	post:		
		ALERT_ERROR(" : ")
		return RESULT_TYPE_ERROR;
	}


}
