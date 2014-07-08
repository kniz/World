#include "commands.hpp"
#include <stdlib.h>
#include "../../Modules/Runnable/Runnable.hpp"

type_result clear::run( NETStringSet& parameter )
{
	if(	parameter.getLength() >= 1	&&
		parameter[0] == _T("-help")	)
	{
		cout << _T("화면을 전부 지운다\n\t옵션 없음\n");
		return RESULT_SUCCESS;
	}
	if(system("cls"))
	{
		Runnable::get().printError(_T("cls에서 에러 발생"));
		return RESULT_TYPE_ERROR;
	}

	return RESULT_SUCCESS;
}
CommandCommonMethod(clear);

type_result help::run( NETStringSet& parameter )
{
	if(	parameter.getLength() >= 1	&&
		parameter[0] == _T("-help")	)
	{
		cout << _T("help를 입력하면 콘솔 환경에서 입력 가능한 모든 명령어를 보여준다.\n각 명령어 앞에 -help를 붙이면 해당 명령어의 자세한 설명이 나온다\n\t옵션없음\n");
		return RESULT_SUCCESS;
	}
	
	Commander& commander = Runnable::get().getCommander();
	
	for(int n=0; n < commander.getLength() ;n++)
		cout << commander[n].getName() << "(" << commander[n].getNickName() << ")" << "\t";
	
	return RESULT_SUCCESS;

}
CommandCommonMethod(help);

type_result quit::run( NETStringSet& parameter )
{
	if(	parameter.getLength() >= 1	&&
		parameter[0] == _T("-help")	)
	{
		cout << _T("콘솔을 종료한다.\n\t옵션없음\n");
		return RESULT_SUCCESS;
	}
	
	Runnable::get().setRunning(false);

	return RESULT_SUCCESS;
}
CommandCommonMethod(quit);

type_result version::run( NETStringSet& parameter )
{
	if(	parameter.getLength() >= 1	&&
		parameter[0] == _T("-help")	)
	{
		cout << _T("콘솔의 버전을 확인 할 수 있다.\n\t옵션없음\n");
		return RESULT_SUCCESS;
	}
	
	NETString message = NETString("World Frameworks, ") + _NAME + " [version :" + _VERSION + "]\n" +
		"copyrights (c) 2009-2013 " + _DEVELOPER + ". All rights reserved.\n" +
		"\tcompiled by " + _DATE + ". " + _REVISION + " revision(build #" + _REVISION + ")\n" +
		"\twebsites : " + _WEBSITE + ". Any Feedback will be acceptable.\n\n" + 
		_NAME + " 에 처음이시라면 help -help 를 입력하세요.\n\n";

	cout << message;

	return RESULT_SUCCESS;

}
CommandCommonMethod(version);
//////////////////////////////////////////////////////////////////////////




type_result list::run( NETStringSet& parameter )
{
	Runnable& runnable = Runnable::get();
	Kernal& kernal = Kernal::getInstance();
	Editor& editor = Editor::getInstance();
	if( !&editor)
	{
		runnable.printError(_T("Editor가 setInstance()되지 않았습니다."));
		return RESULT_TYPE_ERROR;
	}
	if( !&kernal)
	{
		runnable.printError(_T("커널이 setInstance()되지 않았습니다."));
		return RESULT_TYPE_ERROR;
	}	
	//	일반적은 목록 검색:
	if(parameter.getLength() <= 0)
	{
		runnable.printObject(runnable.getCurrentWorkPosition());
		return RESULT_SUCCESS;
	}		
	
	if(parameter[0] == _T("-help"))
	{
		cout	<< _T("플랫폼내의 구성요소를 목록의 형태로 출력한다.\n")
				<< _T("\t-module\t: 인식된, 사용가능한 모듈을 출력한다.\n")
				<< _T("\t-panel\t\t : 인식된, 사용가능한 패널을 출력한다.\n")
				<< _T("\t-dll\t\t: DLL파일의 헤더를 출력한다.\n")
				<< _T("\t없음\t\t: 기본값으로, 현재 작업위치에서의 노드 및 모듈 및 키 목록을 출력한다.\n")
				<< _T("\t-scriptfile\t: 읽을 수 있는 모든 스크립트 파일의 목록을 출력한다.\n")
				<< _T("\t-modulefile\t: 모듈 패키지 파일(DLL)을 모두 출력한다.\n");
				
		return RESULT_SUCCESS;
	}
	else if(parameter[0] == _T("-panelfile"))
	{
		const NEPanelManager::DLLHeaderList& headerset = editor.getPanelManager().getPanelHeaderList();

		cout << _T("n\tpath\n==================================================\n");

		for(int n=0; n < headerset.getLength() ;n++)
		{
			const NEPanelManager::DLLHeader& header = headerset[n];

			cout << n << _T("\t") << header.getPath() << endl;
		}
	}
	else if(parameter[0] == _T("-modulefile"))
	{
		const NEModuleManager::DLLHeaderList& headerset = kernal.getModuleManager().getDllHeaderSet();

		cout << _T("n\tpath\n==================================================\n");

		for(int n=0; n < headerset.getLength() ;n++)
		{
			const NEModuleManager::DLLHeader& header = headerset[n];

			cout << n << _T("\t") << header.getPath() << endl;
		}		
	}
	else if(parameter[0] == _T("-scriptfile"))
	{
		cout	<< _T("n\tfilename\n")
				<< _T("======================================================\n");

		NETString path = kernal.getSettings().getScriptDirectory() + _T("*.") + kernal.getSettings().getScriptExtractor(); 
		NEFileSystem fs(path.toCharPointer(), true);
		int n = 0;
		while(true)
		{
			fs.findFile();
			const NEFileSystem::TaskUnit& task = fs.getLastElement();
			if( ! &task)
				break;
			cout << n++ << _T("\t") << task.getFilePath() << endl;
		}
	}
	else if(	parameter[0] == _T("-module")	||
				parameter[0] == _T("-m")		)
	{
		const NEModuleSet& moduleset = kernal.getModuleManager().getModuleSet();
		
		//	모듈명으로만 검색:
		int count = 0;
		if(parameter.getLength() == 2)
		{
			NETString& module_name = parameter[1];
			
			for(int n=0; n < moduleset.getLength() ;n++)
			{
				const NEExportable::ModuleHeader& header = moduleset[n].getHeader();
				if(header.getName() == module_name)
				{
					runnable.printModule(moduleset[n]);
					cout << endl;
				}
			}		

			if(count >= 20)
			{
				cout << "아무키나 입력하면 계속 출력 : ";
				char dummy = 0;
				cin >> dummy;
				count = 0;
			}
		}
		else if(parameter.getLength() == 3)
		{
			if(parameter[1] == _T("-script"))
			{
				type_code module_scriptcode = parameter[2].toInt();
				const NEModule& module = moduleset[module_scriptcode];
				if( ! &module)
				{
					runnable.printError(_T("모듈을 찾지 못했습니다."));
					return RESULT_TYPE_ERROR;
				}
				
				runnable.printModule(module);
				cout << endl;
			}
		}
		//	Identifier를 전부 명시:
		else if(parameter.getLength() >= 4)
		{
			NEExportable::Identifier identifier(parameter[1], parameter[2], parameter[3].toInt());
			const NEModule& module = kernal.getModuleManager().getModule(identifier);
			if(&module)
				runnable.printModule(module);
		}
		else // 전체 목록 출력:
		{
			int count = 0;
			for(int n=0; n < moduleset.getLength() ;n++)
			{
				runnable.printModule(moduleset[n]);
				cout << endl;

				if(++count >= 20)
				{
					cout << "아무키나 입력하면 계속 출력 : ";
					char dummy = 0;
					cin >> dummy;
					count = 0;
				}
			}		
		}
	}
	else if(parameter[0] == _T("-panel"))
	{
		const NEPanelManager& paneler = editor.getPanelManager();
		if( ! &paneler)
		{
			runnable.printError(_T("NEPanelManager가 존재하지 않습니다."));			
			return RESULT_TYPE_ERROR;
		}
		const NEPanelSet& panelset = paneler.getPanelSet();




		//	모듈명으로만 검색:
		if(parameter.getLength() == 2)
		{
			NETString& module_name = parameter[1];

			for(int n=0; n < panelset.getLength() ;n++)
			{
				const NEExportable::ModuleHeader& header = panelset[n].getHeader();
				if(header.getName() == module_name)
				{
					runnable.printModuleHeader(panelset[n].getHeader());
					cout << endl;
				}
			}	
		}
		else if(parameter.getLength() == 3)
		{
			if(parameter[1] == _T("-script"))
			{
				type_code panel_scriptcode = parameter[2].toInt();
				const NEPanel& panel = panelset[panel_scriptcode];
				if( ! &panel)
				{
					runnable.printError(_T("모듈을 찾지 못했습니다."));
					return RESULT_TYPE_ERROR;
				}

				runnable.printModuleHeader(panel.getHeader());
				cout << endl;
			}
		}
		//	Identifier를 전부 명시:
		else if(parameter.getLength() >= 4)
		{
			NEExportable::Identifier identifier(parameter[1], parameter[2], parameter[3].toInt());
			const NEPanel& panel = paneler.getPanel(identifier);
			if(&panel)
				runnable.printModuleHeader(panel.getHeader());
		}
		else // 전체 목록 출력:
		{
			int count = 0;
			for(int n=0; n < panelset.getLength() ;n++)
			{
				runnable.printModuleHeader(panelset[n].getHeader());
				cout << endl;

				if(++count >= 20)
				{
					cout << "아무키나 입력하면 계속 출력 : ";
					char dummy = 0;
					cin >> dummy;
					count = 0;
				}
			}		
		}	
	}
	else if(parameter[0] == _T("-dll"))
	{
		cout	<< _T("ModuleDirectory : ") << kernal.getSettings().getModuleDirectory().toCharPointer() << endl;
		cout	<< _T("n\tfilename\n")
				<< _T("======================================================\n");

		NETString path = kernal.getSettings().getModuleDirectory() + _T("*.dll"); 
		NEFileSystem fs(path.toCharPointer(), true);
		int n = 0;
		while(true)
		{
			fs.findFile();
			const NEFileSystem::TaskUnit& task = fs.getLastElement();
			if( ! &task)
				break;
			cout << n++ << _T("\t") << task.getFilePath() << endl;
		}

		cout	<< _T("PanelDirectory : ") << editor.getSettings().getPanelDirectory().toCharPointer() << endl;
		cout	<< _T("n\tfilename\n")
				<< _T("======================================================\n");

		path = editor.getSettings().getPanelDirectory() + _T("*.dll"); 
		fs.setPath(path.toCharPointer());
		n = 0;
		while(true)
		{
			fs.findFile();
			const NEFileSystem::TaskUnit& task = fs.getLastElement();
			if( ! &task)
				break;
			cout << n++ << _T("\t") << task.getFilePath() << endl;
		}

	}
	else if(parameter[0] == _T("-scriptheader"))
	{
		NEScriptEditor& scripter = editor.getScriptEditor();
		if( ! &scripter)
		{
			runnable.printError(_T("스크립트 에디터가 없습니다"));
			return RESULT_TYPE_ERROR;
		}
		runnable.printScriptHeader(scripter);
	}
	else if(parameter[0] == _T("-inner"))
	{
		if(parameter[1] == _T("scripteditor"))
		{
			runnable.print(editor.getScriptEditor());
		}
		else if(parameter[1] == _T("scriptmanager"))
		{
			runnable.print(kernal.getScriptManager());
		}
		else if(parameter[1] == _T("nodemanager"))
		{
			runnable.print(kernal.getNodeManager());
		}
	}
	else
	{	//	경로를 입력한 경우:
		if(parameter.getLength() != 1)
		{
			runnable.printError(_T("잘못된 명령어"));
			return RESULT_TYPE_ERROR;	
		}
		
		
		parameter[0] = runnable.getCurrentWorkPosition() + parameter[0];
		if(parameter[0][parameter[0].getLengthLastIndex()-1] != _T('/'))
			parameter[0] = parameter[0] + _T("/");
					
		runnable.printObject(parameter[0]);
	}
	
	return RESULT_SUCCESS;

}
CommandCommonMethod(list);

type_result move::run( NETStringSet& parameter )
{
	Runnable& runnable = Runnable::get();
	if(parameter.getLength() <= 0)
	{
		runnable.printError(_T("경로가 없습니다."));
		return RESULT_TYPE_ERROR;
	}
	if(parameter[0] == _T("-help"))
	{
		cout	<< _T("개요\t:\t작업 위치를 지정한 위치로 변경한다.\n")
				<< _T("사용\t:\tmove [바꿀 경로]\n")				
				<< _T("옵션\t:\t없음\n")
				<< _T("경로에 대해서 :\t경로는 [/위치1/위치2/위치3]과 같이 복수개의 위치지정자가 존재할 수 있다.\n")
				<< _T("\t\t가장 왼쪽의 '/'는 루트(= NEScriptManager::ScriptSet)을 의미하며, \n")
				<< _T("'/3/' 은 루트안에 존재하는 3번째 인덱스의 객체를 의미한다.\n")
				<< _T("같은 의미로 '/node3' 처럼 사용하면 3번째 인덱스의 객체가 node라는 것을 의미한다.\n")
				<< _T("만약 node가 아닐경우에는 잘못된 경로가 된다.\n") 
				<< _T("'/3/', '/3', '/node3' 은 모두 동일한 경로를 나타내며, node3과 지정자로 module, key 등이 존재한다.\n")
				<< _T("각 위치 지정자를 복수개 붙여서 하나의 경로를 만들 수 있다.\n")
				<< _T("앞에 '/'를 붙일 경우 절대경로를 의미하며 없는 경우 상대경로를 의미한다.\n")
				<< _T("예제\t:\t/3/4/2/1/4/2/\n")
				<< _T("\t\t3/4/2/1/4/2/\n")
				<< _T("\t\t/node3/module4/key2/node1/module4/key2/\n");
		return RESULT_SUCCESS;
	}
	else if(parameter[0] == _T(".."))
	{
		NETStringSet splited;
		runnable.getCurrentWorkPosition().split(_T("/"), splited);
		splited.pop();
		
		NEString new_work(_T(""));
		for(int n=0; n < splited.getLength() ;n++)
			new_work += (NETString(_T("/")) + splited[n]);
			
		new_work += _T("/");
		runnable.getCurrentWorkPosition() = new_work;
		return RESULT_SUCCESS;
	}
	
	
	
	
	//	main:
	if(parameter[0][0] != _T('/'))
	{
		//	상대 경로
		parameter[0] = runnable.getCurrentWorkPosition() + parameter[0];
	}
	
	//	post:	
	if(parameter[0][parameter[0].getLengthLastIndex()-1] != _T('/'))
		parameter[0] = parameter[0] + _T("/");
	
	if( ! &runnable.getObjectFrom(parameter[0]))
	{
		runnable.printError(_T("잘못된 경로 입니다."));
		return RESULT_TYPE_ERROR;
	}
		
	runnable.getCurrentWorkPosition() = parameter[0];
	return RESULT_SUCCESS;
}
CommandCommonMethod(move);

type_result add::run( NETStringSet& parameter )
{
	Runnable& runnable = Runnable::get();
	Editor& editor = Editor::getInstance();
	if( ! &editor)
	{
		runnable.printError(_T("에디터가 없습니다"));
		return RESULT_TYPE_ERROR;
	}
	NEScriptEditor& scripted = editor.getScriptEditor();
	if( ! &scripted)
	{
		runnable.printError(_T("스크립트 에디터가 없습니다"));
		return RESULT_TYPE_ERROR;
	}
	if(parameter.getLength() < 1)
	{
		runnable.printError(_T("잘못된 용법입니다."));
		return RESULT_TYPE_ERROR;
	}
	if(parameter[0] == _T("-help"))
	{
		cout	<< _T("개요\t:\t현재 위치에 초기화된 상태의 객체를 추가한다.\n")
				<< _T("사용\t:\tadd [타입지정] [인덱스]\n")
				<< _T("\t\t타입지정에는 추가하려는 객체가 node인지, 모듈일 경우 어느 모듈인지를 표시한다.\n")
				<< _T("\t\t인덱스에는 삽입될 인덱스를 지정한다. 없는 경우 가장 끝에 추가된다.(push)\n")
				<< _T("옵션\t:\n")
				<< _T("\t[타입지정]\n")
				<< _T("\t\t-node\t노드를 추가한다.\n")
				<< _T("\t\t-module:모듈번호\t모듈번호에 해당하는 모듈을 추가한다.\n");
		return RESULT_SUCCESS;
	}
	//	현재 위치 획득:
	NEObject& object = runnable.getObjectFrom(runnable.getCurrentWorkPosition());
	if( !&object)
	{
		runnable.printError(_T("현재 위치로부터 객체를 가져올 수 없습니다 - 잘못된 경로"));
		return RESULT_TYPE_ERROR;
	}
		
	
	
	//	main:
	if(	parameter[0] == _T("-node")	||
		parameter[0] == _T("-n")	)
	{
		//	타겟팅:
		NENodeCodeSet* collector = NE_NULL;
		//	타입 확인:
		if(	object.isSubClassOf(NEType::NENODE_CODESET))
		{
			collector = static_cast<NENodeCodeSet*>(&object);
		}
		else if(object.isSubClassOf(NEType::NENODE_CODESET_KEY))
		{
			NENodeCodeSetKey& key = static_cast<NENodeCodeSetKey&>(object);
			collector = &(key.getValue());
		}
		else
		{
			runnable.printError(NETString("현재 위치에 존재하는 객체는 노드를 생성할 수 없는 객체입니다. 현재 위치의 객체타입 : ") + object.getTypeName());
			return RESULT_TYPE_ERROR;
		}		
		
		//	인덱스 구하기:
		type_index index = NE_INDEX_ERROR;		
		if(parameter.getLength() >= 2) // parameter[1]이 존재한다면
		{
			index = parameter[1].toInt();
			if(index < 0 || index > collector->getLength()) // > getLength()로 했기 때문에 index는 getLengthLastIndex() + 1 까지도 된다는 것에 주의하라.
			{
				runnable.printError(NETString("현재 위치에 존재하는 객체의 범위를 벗어난 인덱스입니다. 현재 위치의 객체 범위 : 0 ~ ") + collector->getLengthLastIndex());
				return RESULT_TYPE_ERROR;
			}
		}
		else
			index = collector->getLengthLastIndex() + 1; // push가 될 것이다.
		//	수행:
		if(collector->isSubClassOf(NEType::NENODE_CODESET))
		{
			NENodeCodeSet& nodeset = static_cast<NENodeCodeSet&>(*collector);
			if(nodeset.getLength() == nodeset.getSize())
				nodeset.resize(nodeset.getLength() + 1);
		}
		


		//	노드의 삽입시, 동기화를 어떻게 처리하는가:
		//		노드의 스크립트(= scriptcode)는 다른 코드값과는 틀리다.
		//		왜냐하면 노드의 삽입은 코드의 증가를 의미하기 때문이다.
		//		그런데 어떤 인덱스의 코드가 insert 됬는가는 synchronize를
		//		하고 나서야 알 수 있다.
		//		다만 insertCode에서는 노드 자체의 scriptcode를 ++하는 효과가 있기 때문에
		//		이미 synchronized된 scriptcode가 ++ 되버리면 순서가 틀려지게 된다.
		//		그래서 insertCode에서 bank를 동기화 하는 부분만 따로 밑에서 적는다.
		//		삽입:
		collector->insert(index, NENode());
		/*
			//		삽입한 인덱스를 가져옴.
			NENode& inserted_node = collector->getElement(index);
			//		아이디 동기화:
			scripted.getManagedScriptList().synchronizeId();
			//		뱅크 동기화:
			//			삽입한 노드의 동기화된 아이디가 "추가된 코드 인덱스" 가 된다.
			//			그 정보를 이용해서 뱅크를 동기화한다.
			NETStringSet& scriptbank = scripted.getManagedScriptList().getBanks().getScriptBank();
			scriptbank.resize(scriptbank.getSize() + 1);
			scriptbank.insert(inserted_node.getId(), NETString(_T("")));
		*/
		

		cout << endl;
	}
	else if(	(parameter[0].getLength() > 9	&&				// '-module:' 까지만 입력했을때 길이가 9이 된다.
				parameter[0].extract(0, 7) == _T("-module:"))	
				||
				(parameter[0].getLength() > 4	&&
				parameter[0].extract(0,2) == _T("-m:"))			)
	{
		//	타겟팅:
		const NEModule* fetched_module = 0;
		Kernal& kernal = Kernal::getInstance();
		const NEModuleSet& moduleset = kernal.getModuleManager().getModuleSet();
		NEModuleCodeSet* collector = NE_NULL;
		if( ! &kernal)
		{
			runnable.printError(_T("커널이 존재하지 않습니다."));
			return RESULT_TYPE_ERROR;
		}		
		//	타입 확인:
		//		현재위치가 노드를 가리킨다면, 모듈셋으로 캐스팅한다:	노드와 모듈셋은 하나다
		//		현재위치가 모듈을 가리킨다면, 키셋으로 캐스팅한다:		모듈과 키셋은 하나다.
		if(object.isSubClassOf(NEType::NENODE))
		{
			NENode& node = static_cast<NENode&>(object);
			collector = &(node.getModuleSet());
		}
		else if(object.isSubClassOf(NEType::NEMODULE_CODESET))
		{
			collector = static_cast<NEModuleCodeSet*>(&object);
		}
		else if(object.isSubClassOf(NEType::NEMODULE_CODESET_KEY))
		{
			NEModuleCodeSetKey& key = static_cast<NEModuleCodeSetKey&>(object);
			collector = static_cast<NEModuleCodeSet*>( &(key.getValue()) );
		}
		else
		{
			runnable.printError(NETString("현재 위치에 존재하는 객체는 모듈을 생성할 수 없는 객체입니다. 현재 위치의 객체타입 : ") + object.getTypeName());
			return RESULT_TYPE_ERROR;
		}

		NETString extracted1;
		if(parameter[0].getLength() > 9	&&	parameter[0].extract(0, 7) == _T("-module:"))
			extracted1 = parameter[0].extract(8, parameter[0].getLengthLastIndex());
		else if(parameter[0].getLength() > 4 && parameter[0].extract(0,2) == _T("-m:"))
			extracted1 = parameter[0].extract(3, parameter[0].getLengthLastIndex() - 1);

		type_code module_scriptcode = extracted1.toInt();
		if(	module_scriptcode < 0								|| 
			module_scriptcode > moduleset.getLengthLastIndex()	||
			extracted1[0] < _T('0')								||
			_T('9') < extracted1[0]								)
		{
			for(int n=0; n < moduleset.getLength() ;n++)
				if(extracted1 == moduleset[n].getHeader().getName())
				{
					fetched_module = &moduleset[n];
					goto SEC1;
				}
			runnable.printError(NETString("입력한 모듈번호는 존재하지 않는 scriptcode입니다. 모듈매니져의 붙여진 모듈의 scriptcode 범위 : 0 ~ ") + moduleset.getLengthLastIndex());
			return RESULT_TYPE_ERROR;
		}
		else
			fetched_module = &moduleset[module_scriptcode];

SEC1:
		//	인덱스 구하기:
		type_index index = NE_INDEX_ERROR;
		if(parameter.getLength() >= 2) // parameter[1]이 존재한다면
		{
			index = parameter[1].toInt();
			if(index < 0 || index > collector->getLength()) // > getLength()로 했기 때문에 index는 getLengthLastIndex() + 1 까지도 된다는 것에 주의하라.
			{
				runnable.printError(NETString("현재 위치에 존재하는 객체의 범위를 벗어난 인덱스입니다. 현재 위치의 객체 범위 : 0 ~ ") + collector->getLengthLastIndex());
				return RESULT_TYPE_ERROR;
			}
		}
		else
			index = collector->getLengthLastIndex() + 1; // push가 될 것이다.
		//	수행:
		//		모듈 fetch:
		if(collector->getLength() == collector->getSize())
			collector->resize(collector->getLength() + 1);
		
		collector->insert(index, *fetched_module);
		
		cout << endl;
	}
	else
	{
		runnable.printError(_T("잘못된 옵션 사용입니다."));
		return RESULT_TYPE_ERROR;
	}
	
	return RESULT_SUCCESS;
}
CommandCommonMethod(add);



type_result remove::run( NETStringSet& parameter )
{
	Runnable& runnable = Runnable::get();
	Editor& editor = Editor::getInstance();
	if( ! &editor)
	{
		runnable.printError(_T("에디터가 없습니다"));
		return RESULT_TYPE_ERROR;
	}
	NEScriptEditor& scripted = editor.getScriptEditor();
	if( ! &scripted)
	{
		runnable.printError(_T("스크립트 에디터가 없습니다"));
		return RESULT_TYPE_ERROR;
	}
	if(parameter.getLength() >= 1 && parameter[0] == _T("-help"))
	{
		cout	<< _T("개요\t:\t현재 위치에서 지정한 인덱스에 해당하는 하위 객체를 삭제한다.\n")
				<< _T("\t\t아무런 인덱스를 넣지 않았을 경우 가장 뒤 인덱스를 삭제한다. (= pop)\n")
				<< _T("\t\t키는 삭제할 수 없으나, 키가 가지고 있는 노드 및 모듈은 삭제가 가능하다.\n")
				<< _T("사용\t:\tremove [삭제할 객체의 인덱스]\n")
				<< _T("옵션\t:\n")
				<< _T("\t없음\n");
		return RESULT_SUCCESS;
	}
	//	현재 위치 획득:
	NEObject& object = runnable.getObjectFrom(runnable.getCurrentWorkPosition());
		
	if( !&object)
	{
		runnable.printError(_T("현재 위치로부터 객체를 가져올 수 없습니다 - 잘못된 경로"));
		return RESULT_TYPE_ERROR;
	}



	//	main
	//		object 형변환:
	if(	object.isSubClassOf(NEType::NENODE_CODESET)		||
		object.isSubClassOf(NEType::NENODE_CODESET_KEY)	)
	{
		NENodeCodeSet* collector = NE_NULL;
		if(	object.isSubClassOf(NEType::NENODE_CODESET))
		{
			collector = static_cast<NENodeCodeSet*>(&object);
		}
		else if(object.isSubClassOf(NEType::NENODE_CODESET_KEY))
		{
			NENodeCodeSetKey& key = static_cast<NENodeCodeSetKey&>(object);
			collector = &(key.getValue());
		}
		else
		{
			runnable.printError(_T("알수없는 타입"));
			return RESULT_TYPE_ERROR;
		}
		//	인덱스 가져오기:
		type_index index = NE_INDEX_ERROR;
		if( ! parameter.getLength())
			index = collector->getLengthLastIndex();
		else
		{
			index = parameter[0].toInt();
			if(index < 0 || index > collector->getLength()) // > getLength()로 했기 때문에 index는 getLengthLastIndex() + 1 까지도 된다는 것에 주의하라.
			{
				runnable.printError(NETString("현재 위치의 범위를 넘어선 접근입니다. 현재 위치의 객체 범위 : 0 ~ ") + collector->getLengthLastIndex());
				return RESULT_TYPE_ERROR;
			}
		}
		//	수행:
		collector->remove(index);
		if(collector->isSubClassOf(NEType::NENODE_CODESET))
		{
			NENodeCodeSet& nodeset = static_cast<NENodeCodeSet&>(*collector);
			nodeset.resize(nodeset.getLength());
		}			

		

	} 
	else if(	object.isSubClassOf(NEType::NENODE)					||
				object.isSubClassOf(NEType::NEMODULE_CODESET)		||
				object.isSubClassOf(NEType::NEMODULE_CODESET_KEY)	)
	{
		NEModuleCodeSet* moduleset = NE_NULL;
		if(object.isSubClassOf(NEType::NENODE))
		{
			NENode& node = static_cast<NENode&>(object);
			moduleset = &(node.getModuleSet());
		}
		else if(object.isSubClassOf(NEType::NEMODULE_CODESET))
		{
			moduleset = static_cast<NEModuleCodeSet*>(&object);
		}
		else if(object.isSubClassOf(NEType::NEMODULE_CODESET_KEY))
		{
			NEModuleCodeSetKey& key = static_cast<NEModuleCodeSetKey&>(object);
			moduleset = &(key.getValue());
		}
		else
		{
			runnable.printError(_T("알수없는 타입"));
			return RESULT_TYPE_ERROR;
		}
		
		//	인덱스 가져오기:
		type_index index = NE_INDEX_ERROR;
		if( ! parameter.getLength())
			index = moduleset->getLengthLastIndex();
		else
		{
			index = parameter[0].toInt();
			if(index < 0 || index > moduleset->getLength()) // > getLength()로 했기 때문에 index는 getLengthLastIndex() + 1 까지도 된다는 것에 주의하라.
			{
				runnable.printError(NETString("현재 위치의 범위를 넘어선 접근입니다. 현재 위치의 객체 범위 : 0 ~ ") + moduleset->getLengthLastIndex());
				return RESULT_TYPE_ERROR;
			}
		}
		//	수행:
		moduleset->remove(index);
		moduleset->resize(moduleset->getLength());
		
	}
	else
	{
		runnable.printError(_T("현재 위치로부터 remove 불가능한 객체를 가져왔습니다. 키는 remove가 안됩니다."));
		return RESULT_TYPE_ERROR;
	}	

	return RESULT_SUCCESS;
}
CommandCommonMethod(remove)


type_result modify::run(NETStringSet& parameter)
{
	Runnable& runnable = Runnable::get();
	Editor& editor = Editor::getInstance();
	if( ! &editor)
	{
		runnable.printError(_T("에디터가 없습니다"));
		return RESULT_TYPE_ERROR;
	}
	NEEventHandler& handler = editor.getEventHandler();
	if( ! &handler)
	{
		runnable.printError(_T("핸들러가 없습니다"));
		return RESULT_TYPE_ERROR;
	}
	if(parameter.getLength() == 0)
	{
		//	현재위치의 객체의 타입을 가져옴:
		NEObject& object = runnable.getObjectFrom( runnable.getCurrentWorkPosition() );
		if(object.isSubClassOf(NEType::NENODE))
		{
			NENode& node = static_cast<NENode&>(object);
			runnable.modifyNode(node);
		}
		else if(object.isSubClassOf(NEType::NEMODULE))
		{
			NEModule& module = static_cast<NEModule&>(object);
			runnable.modifyModule(module);
		}
		else if(object.isSubClassOf(NEType::NEKEY))
		{			
			NEKey& key = static_cast<NEKey&>(object);
			NEType::Type type = key.getType();
			return handler.onModifyingKey(key);
		}
		else
		{
			runnable.printError(_T("변경 불가능한 현재위치 입니다"));
			return RESULT_TYPE_ERROR;
		}
	}
	else if(parameter[0] == _T("-help"))
	{
		cout	<< _T("개요\t:\t현재 위치의 객체와 스크립트 파일의 헤더를 수정하는 모드로 들어갑니다.\n")
				<< _T("\t\t현재 위치가 노드, 모듈인 경우에만 변경이 가능하며, 스크립트 파일 헤더는 어느 위치에서도 수정이 가능합니다.\n")
				<< _T("사용\t:\tmodify\n")
				<< _T("옵션\t:\n")
				<< _T("\t-header\t:\t스크립트 파일헤더를 수정하는 모드\n");
		return RESULT_SUCCESS;
	}
	else if(parameter[0] == _T("-header"))
	{
		Kernal& kernal = Kernal::getInstance();		
		if( ! &kernal)
		{
			runnable.printError(_T("커널이 없습니다"));
			return RESULT_TYPE_ERROR;
		}
		NEScriptManager& scripter = kernal.getScriptManager();
		if( ! &scripter)
		{
			runnable.printError(_T("스크립트 매니져가 없습니다"));
			return RESULT_TYPE_ERROR;			
		}
		Editor& editor = Editor::getInstance();
		if( ! &editor)
		{
			runnable.printError(_T("에디터가 없습니다."));
			return RESULT_TYPE_ERROR;
		}
		NEScriptEditor& scripted = editor.getScriptEditor();
		if( ! &scripted)
		{
			runnable.printError(_T("스크립트 에디터가 없습니다."));
			return RESULT_TYPE_ERROR;
		}
		NEEventHandler& handler = editor.getEventHandler();
		if( ! &handler)
		{
			runnable.printError(_T("핸들러가 없습니다"));
			return RESULT_TYPE_ERROR;
		}
		
		const NEScriptManager::ScriptHeader& header = scripter.getScriptHeader();
		
		bool main_running = true;
		while(main_running)
		{
			runnable.printScriptHeader(scripted);
			cout	<< _T("===========================================\n")
					<< _T("1. modify max namecode\n")
					<< _T("2. modify max scriptcode\n")
					<< _T("3. modify max groupcode\n")
					<< _T("4. modify max prioritycode\n")
					<< _T("5. modify comment\n")
					<< _T("6. modify contact\n")
					<< _T("7. modify release date\n")
					<< _T("8. modify version\n")
					<< _T("9. modify name\n")
					<< _T("10. modify developer\n")
					<< _T("11. modify revision\n")					
					<< _T("12. quit\n")
					<< _T("==========================================\n")
					<< _T(" > ");
			
			int command = -1;
			TIN >> command;
			if(command < 1 || command > 13)
			{
				cout << _T("숫자를 다시 입력하세요.\n");
				continue;
			}
			
			runnable.flushStdIo();
						
			cout << endl;
			
			switch(command)
			{
			case 1:
				runnable.modifyCode(NECodeType::NAME, scripted.getScriptHeader().getMaxNameCodeIndex(), &NEScriptEditor::insertNameCode, &NEScriptEditor::removeNameCode, scripted.getBanks().getNameBank());
				break;
			case 2:
				runnable.modifyCode(NECodeType::SCRIPT, scripted.getScriptHeader().getMaxScriptCodeIndex(), NE_NULL, NE_NULL, scripted.getBanks().getScriptBank());
				break;
			case 3:
				runnable.modifyCode(NECodeType::GROUP, scripted.getScriptHeader().getMaxGroupCodeIndex(), &NEScriptEditor::insertGroupCode, &NEScriptEditor::removeGroupCode, scripted.getBanks().getGroupBank());
				break;
			case 4:
				runnable.modifyCode(NECodeType::PRIORITY, scripted.getScriptHeader().getMaxPriorityCodeIndex(), &NEScriptEditor::insertPriorityCode, &NEScriptEditor::removePriorityCode, scripted.getBanks().getPriorityBank());
				break;
			case 5:
				{
					cout << _T("새로운 comment : ");
					TCHAR buffer[256] = {0, };
					TIN.getline(buffer, 256);
					
					scripted.getScriptHeader().getComment() = buffer;
				}
				break;
			case 6:
				{
					cout << _T("새로운 contact : ");
					TCHAR buffer[256] = {0, };
					TIN.getline(buffer, 256);

					scripted.getScriptHeader().getContact() = buffer;
				}
				break;
			case 7:
				{
					cout << _T("새로운 release date : ");
					TCHAR buffer[256] = {0, };
					TIN.getline(buffer, 256);

					scripted.getScriptHeader().getReleaseDate() = buffer;
				}
				break;
			case 8:
				{
					cout << _T("새로운 version : ");
					TCHAR buffer[256] = {0, };
					TIN.getline(buffer, 256);

					scripted.getScriptHeader().getVersion() = buffer;
				}
				break;
			case 9:
				{
					cout << _T("새로운 스크립트 name: ");
					TCHAR buffer[256] = {0, };
					TIN.getline(buffer, 256);

					scripted.getScriptHeader().getName() = buffer;
				}
				break;
			case 10:
				{
					cout << _T("새로운 developer : ");
					TCHAR buffer[256] = {0, };
					TIN.getline(buffer, 256);

					scripted.getScriptHeader().getDeveloper() = buffer;
				}
				break;
			case 11:
				{
					cout << _T("새로운 revision : ");
					int new_revision = 0;
					TIN >> new_revision;
					runnable.flushStdIo();
					
					scripted.getScriptHeader().setRevision(new_revision);
				}
				break;
			case 12:
				main_running = false;
				break;				
			default:
				runnable.printError(_T("잘못된 명령어"));
				break;
			}
		}		
	}
	else
	{
		runnable.printError(_T("알 수 없는 명령어 입니다"));
		return RESULT_TYPE_ERROR;
	}
	
	return RESULT_SUCCESS;
}
CommandCommonMethod(modify)

type_result save::run( NETStringSet& parameter )
{
	Runnable& runnable = Runnable::get();
	Editor& editor = Editor::getInstance();
	if( ! &editor)
	{
		runnable.printError(_T("에디터가 없습니다"));
		return RESULT_SUCCESS;
	}
	NEEventHandler& handler = editor.getEventHandler();
	if( ! &handler)
	{
		runnable.printError(_T("이벤트 핸들러가 없습니다"));
		return RESULT_TYPE_ERROR;
	}
	if(	parameter.getLength() >= 1	&&
		parameter[0] == _T("-help")	)
	{
		cout	<< _T("개요\t:\t현재의 편집한 스크립트를 커널이 읽을 수 있는 형태로 저장합니다.\n")
				<< _T("사용\t:\tsave <저장할경로 + 파일명>\n")
				<< _T("옵션\t:없음\n");
				
		return RESULT_SUCCESS;
	}
	if(parameter.getLength() <= 0)
	{
		runnable.printError(_T("경로를 입력하세요"));
		return RESULT_TYPE_ERROR;
	}	
	
	
	
	return handler.saveScriptFile(parameter[0]);
}
CommandCommonMethod(save);

type_result load::run( NETStringSet& parameter ){
	Runnable& runnable = Runnable::get();
	Editor& editor = Editor::getInstance();
	if( ! &editor)
	{
		runnable.printError(_T("에디터가 없습니다"));
		return RESULT_SUCCESS;
	}
	NEEventHandler& handler = editor.getEventHandler();
	if( ! &handler)
	{
		runnable.printError(_T("이벤트 핸들러가 없습니다"));
		return RESULT_TYPE_ERROR;
	}
	if(	parameter.getLength() >= 1	&&
		parameter[0] == _T("-help")	)
	{
		cout	<< _T("개요\t:\t편집했던 스크립트 파일을 읽어옵니다.\n")
				<< _T("사용\t:\tload <저장할경로 + 파일명>\n")
				<< _T("옵션\t:없음\n");
				
		return RESULT_SUCCESS;
	}
	if(parameter.getLength() <= 0)
	{
		runnable.printError(_T("경로를 입력하세요"));
		return RESULT_TYPE_ERROR;
	}	



	return handler.loadScriptFile(parameter[0]);
}
CommandCommonMethod(load);

type_result runtest::run( NETStringSet& parameter )
{
	//	pre:
	//		타겟팅:
	Runnable& runnable = Runnable::get();
	Editor& editor = Editor::getInstance();
	if( ! &editor)
	{
		runnable.printError(_T("에디터가 없습니다"));
		return RESULT_TYPE_ERROR;
	}
	NEEventHandler& handler = editor.getEventHandler();
	if( ! &handler)
	{
		runnable.printError(_T("핸들러가 없습니다"));
		return RESULT_TYPE_ERROR;
	}
	//		파라메터:
	if(	parameter.getLength() >= 1	&&
		parameter[0] == _T("-help")	)
	{
		cout	<< _T("개요\t:\t현재 편집한 스크립트를 이용해서 테스트를 실시합니다.\n")
				<< _T("사용\t:\truntest\n")
				<< _T("옵션\t:없음\n");
		return RESULT_SUCCESS;
	}


	
	return handler.runTest();
}
CommandCommonMethod(runtest);



void pushObject(NETString& parameter0, NETString& parameter1, type_index index = -1)
{
	Runnable& runnable = Runnable::get();
	NEObject&	trg = runnable.getObjectFrom(parameter0),
			&	src = runnable.getObjectFrom(parameter1);		
	if( ! &src)
	{
		runnable.printError(NETString("주어진 src(") + parameter1 + ")가 잘못된 경로 입니다.");
		return;
	}

	if( ! &trg)
	{
		runnable.printError(NETString("주어진 trg(") + parameter0 + ")가 잘못된 경로 입니다.");
		return;
	}
	
	if(src.isSubClassOf(NEType::NENODE_CODESET))
	{
		if( ! trg.isSubClassOf(NEType::NENODE))
			goto ERRORS;

		NENodeCodeSet& set = (NENodeCodeSet&) src;
		
		if(set.getLength() == set.getSize())
			set.resize(set.getLength() + 1);

		NENode& node = (NENode&) runnable.getObjectFrom(parameter0);

		if(index != NE_INDEX_ERROR)
			set.insert(index, node);
		else
			set.push(node);		
	}
	else if(src.isSubClassOf(NEType::NENODE_CODESET_KEY))
	{
		if( ! trg.isSubClassOf(NEType::NENODE))
			goto ERRORS;

		NENodeCodeSet& set = ((NENodeCodeSetKey&) src).getValue();
		
		if(set.getLength() == set.getSize())
			set.resize(set.getLength() + 1);

		NENode& node = (NENode&) runnable.getObjectFrom(parameter0);

		if(index != NE_INDEX_ERROR)
			set.insert(index, node);
		else
			set.push(node);	

	}
	else if(src.isSubClassOf(NEType::NENODE))
	{
		if( ! trg.isSubClassOf(NEType::NEMODULE))
			goto ERRORS;

		NEModuleCodeSet& set = ((NENode&) src).getModuleSet();
		
		if(set.getLength() == set.getSize())
			set.resize(set.getLength() + 1);

		NEModule& module = (NEModule&) runnable.getObjectFrom(parameter0);

		if(index != NE_INDEX_ERROR)
			set.insert(index, module);
		else
			set.push(module);	
	}
	else if(src.isSubClassOf(NEType::NEMODULE_CODESET_KEY))
	{
		if( ! trg.isSubClassOf(NEType::NEMODULE))
			goto ERRORS;

		NEModuleCodeSet& set = ((NEModuleCodeSetKey&) src).getValue();
		
		if(set.getLength() == set.getSize())
			set.resize(set.getLength() + 1);

		NEModule& module = (NEModule&) runnable.getObjectFrom(parameter0);

		if(index != NE_INDEX_ERROR)
			set.insert(index, module);
		else
			set.push(module);	
	}
	else if(src.isSubClassOf(NEType::NEMODULE))
	{
		if( ! trg.isSubClassOf(NEType::NEKEY))
			goto ERRORS;

		NEKeyCodeSet& set = ((NEModule&) src).getKeySet();

		if(set.getLength() == set.getSize())
			set.resize(set.getLength() + 1);

		NEKey& key = (NEKey&) runnable.getObjectFrom(parameter0);

		if(index != NE_INDEX_ERROR)
			set.insert(index, key);
		else
			set.push(key);	
	}
	else
		goto ERRORS;

	return;


ERRORS:
	runnable.printError(NETString("주어진 src의 타입(") + src.getTypeName() + ")과 trg의 타입(" + trg.getTypeName() + ")이 적절하지 않습니다.");	
}

type_result copy::run( NETStringSet& parameter )
{
	if(	parameter.getLength() >= 1	&&
		parameter[0] == _T("-help")	)
	{
		cout << _T("개요 : [0ㄹ] 위치에 있는 객체를 [1] 위치 밑으로 복사한다. [2]에 추가할 index를 줄 수 있다.\n\t단 [0] 객체가 [1]에 들어갈 수 있는 타입이어야 한다.\n[2]를 입력하지 않으면 [1] 안에 가장 뒤에 삽입된다.\n\t사용법 : copy [0] [1] [2]\n\t예제 : copy 3 /1\n\t\tcopy 3 /1 3\n");
		return RESULT_SUCCESS;
	}
	if(parameter.getLength() < 2)
	{
		cout << "잘못된 인자\n";
		return RESULT_TYPE_ERROR;
	}
	
	Runnable& runnable = Runnable::get();
	//	main:
	
	for(int n=0; n < 2 ;n++)
		if(parameter[n][0] != _T('/'))
		{
			//	상대 경로
			parameter[n] = runnable.getCurrentWorkPosition() + parameter[n];
			if(parameter[n][parameter[n].getLengthLastIndex()-1] != _T('/'))
				parameter[n] = parameter[n] + _T("/");
		}

	type_index n = parameter.getLengthLastIndex() >= 2 ? parameter[2].toInt() : -1;
	pushObject(parameter[0], parameter[1], n);

	return RESULT_SUCCESS;

}
CommandCommonMethod(copy);





type_result cut::run( NETStringSet& parameter )
{
	if(	parameter.getLength() >= 1	&&
		parameter[0] == _T("-help")	)
	{
		cout << _T("개요 : [0] 위치에 있는 객체를 [1] 위치 밑으로 잘라내어 붙여넣기한다. \n\t단 [0] 객체가 [1]에 들어갈 수 있는 타입이어야 한다.\n\t사용법 : cut [0] [1] \n\t예제 : cut 3 /1\n");
		return RESULT_SUCCESS;
	}
	if(parameter.getLength() < 2)
	{
		cout << "잘못된 인자\n";
		return RESULT_TYPE_ERROR;
	}

	Runnable& runnable = Runnable::get();
	//	main:
	for(int n=0; n < 2 ;n++)
		if(parameter[n][0] != _T('/'))
		{
			//	상대 경로ik
			parameter[n] = runnable.getCurrentWorkPosition() + parameter[n];
			if(parameter[n][parameter[n].getLengthLastIndex()-1] != _T('/'))
				parameter[n] = parameter[n] + _T("/");
		}

	pushObject(parameter[0], parameter[1]);
	NETStringSet set(1);

	NETString backup = runnable.getCurrentWorkPosition(), new_work_path;
	NETStringSet splited, new_workposition;
	parameter[0].split("/", splited);
	set.push(splited[splited.getLengthLastIndex()]);
	splited.pop();
	new_workposition = splited;
	if(new_workposition.getSize() != new_workposition.getLength())
		new_workposition.resize(new_workposition.getLength());
	for(int n=0 ; n < new_workposition.getLength(); n++)
		new_work_path += new_workposition[n] + "/";
	
	runnable.getCurrentWorkPosition() = new_work_path;
	runnable.getCommander().getInterface("remove").run(set);
	runnable.getCurrentWorkPosition() = backup;

	return RESULT_SUCCESS;

}
CommandCommonMethod(cut);