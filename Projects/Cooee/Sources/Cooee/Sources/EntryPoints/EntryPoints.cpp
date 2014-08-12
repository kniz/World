#include "Headers.hpp"

Kernal* kernal = 0;
Editor* editor = 0;

NEString fetch_com_line()
{
	char buffer[_MAX_BUFFER];

	cin.getline(buffer, _MAX_BUFFER);

	return buffer;
}
void init_kern()
{
	cout	<< _VERSION_STRING
			<< "\tby " << _DEVELOPER << "\n"
			<< "\ton " << _DATE << "\n\n"
			<< "Initiate Bootting Sequences...\n"
			<< "\t- Create factory...";
	Kernal::Factory factory;
	
	cout	<< "SUCCESS\n"
			<< "\t- Configure settings of factory instance...";	
	Kernal::ModifiableSettings& settings = factory.getDefaultSettings();
	
	cout	<< "Set to default...";
	settings.getINIFullPath() = "./NodeCUI.ini";
	settings.setModuleDirectory("Modules");
	settings.setLogDirectory("Logs");
	settings.setScriptDirectory("Scripts");
	settings.setNodeDirectory("Nodes");

	cout	<< "SUCCESS\n"
			<< "\t- Assign settings Managers identifiers...NEStandardNodeManager && NEStandardScriptManager...";
	factory.getNodeManagerIdentifier() = NEExportable::Identifier("NEStandardNodeManager", "haku", 1);
	factory.getScriptManagerIdentifier() = NEExportable::Identifier("NEStandardScriptManager", "haku", 1);
	cout	<< "SUCCESS\n";

	cout	<< "\t- Check if Directories have been set properly or not...\n";

	NEString inputed;
// 	do {
// 		cout	<< "\t\t- INI-file : " << settings.getINIFullPath() << endl
// 				<< "\t\t- Modules  : " << settings.getModuleDirectory() << endl
// 				<< "\t\t- Logs     : " << settings.getLogDirectory() << endl
// 				<< "\t\t- Scripts  : " << settings.getScriptDirectory() << endl
// 				<< "\t\t- NodeData : " << settings.getNodeDirectory() << endl;
// 
// 		cout << "\t\t> are these correct?(y/n) > ";
// 		inputed = fetch_com_line();
// 		if(inputed == "N" || inputed == "n")
// 		{
// 			system("cls");
// 			cout << "- 새로운 INI 파일명과 경로(skip 입력시 통과): \n\t";
// 			NEString& new_inipath = fetch_com_line();
// 			if(new_inipath != "skip")
// 				settings.getINIFullPath() = new_inipath;
// 
// 			cout << "- 새로운 모듈 디렉토리(skip 입력시 통과) : \n\t";
// 			NEString& new_module = fetch_com_line();
// 			if(new_module != "skip")
// 				settings.setModuleDirectory(new_module);
// 
// 			cout << "- 새로운 로그 디렉토리(skip 입력시 통과) : \n\t";
// 			NEString& new_log = fetch_com_line();
// 			if(new_log != "skip")
// 				settings.setLogDirectory(new_log);
// 
// 			cout << "- 새로운 스크립트 디렉토리(skip 입력시 통과) : \n\t";
// 			NEString& new_script = fetch_com_line();
// 			if(new_script != "skip")
// 				settings.setScriptDirectory(new_script);
// 
// 			cout << "- 새로운 노드 디렉토리(skip 입력시 통과) : \n\t";
// 			NEString& new_node = fetch_com_line();
// 			if(new_node != "skip")
// 				settings.setNodeDirectory(new_node);
// 		}		
// 	} while(inputed == "n" || inputed == "N");

	cout << "\t - Create Kernel package...";
	kernal = new Kernal(factory.create());
	cout << "Registering...";
	Kernal::setInstance(*kernal);
	cout << "Initializing...";
	Kernal::getInstance().initialize();
	cout << "SUCCESS...Now, move to Editor booting part.";
	system("pause");
	
	
	cout	<< "\n\n"
			<< "\t- create editor factory...";
	Editor::Factory editor_factory;
	cout	<< "SUCCESS\n"
			<< "\t- Assign settings Managers identifiers...NEStandardPanelManager && NEStandardScriptEditer && CooeeHandler...";
	editor_factory.getPanelManagerIdentifier() = NEExportable::Identifier("NEStandardPanelManager", "haku", 1);
	editor_factory.getScriptEditorIdentifier() = NEExportable::Identifier("NEStandardScriptEditor", "haku", 1);
	editor_factory.getEventHandlerIdentifier() = NEExportable::Identifier("CooeeHandler", "kniz", 1);
	
	cout	<< "SUCCESS\n"
			<< "\t- Configure settings of factory instance...";
	editor_factory.getDefaultSettings().setPanelDirectory(".\\Panels");
	editor_factory.getDefaultSettings().setLoadFromINI(true);


	cout	<< "SUCCESS\n"
			<< "\t- Create Editor package...";
	editor = new Editor(editor_factory.create());
	cout	<< "Registering...";
	Editor::setInstance(*editor);
	cout	<< "Initializing...";
	Editor::getInstance().initialize();
	cout	<< "SUCCESS\n"
			<< "- ready a new script file...";
	if( &Editor::getInstance()	&&
		&Editor::getInstance().getScriptEditor()) 
	{
		NEScriptManager::ScriptHeader& header = Editor::getInstance().getScriptEditor().getScriptHeader();
		header.getName() = "unnamed";
		header.getDeveloper() = "anonymous";
		header.setRevision(1);
		cout	<< "SUCCESS\n"
			<< "Whole boot sequences have been finished!";
	}
	system("pause");
}

void init_wins() {
	system("cls");
	using namespace LG;

	LG::Core::windows.pushFront(NodeSetTerminal());
	LG::Core::windows.pushFront(MessageWindow(NEString(_VERSION_STRING) + "\n\tby " + _DEVELOPER + "\n\ton " + _DATE, WHITE, LIGHTRED));

	NEKeyCodeSet& ks = Editor::getInstance().getScriptEditor().getScriptNodes()[0].getKeySet();
	ks.create(3);
	
	//LG::Core::open(KeySetTerminal("/0/k"));

	NENodeCodeSet& ns = Editor::getInstance().getScriptEditor().getScriptNodes();
	NENode& n1 = ns[0];
	{
		NEKeyCodeSet& ks = n1.getKeySet();
		n1.getKeySet().create(3);
		ks.push(NEBooleanKey());
		NEStringSet temp(2);
		temp.push("hate");
		temp.push("mi!");
		ks.push(NEStringSetKey(temp, "characters"));
		NEModuleCodeSet& temp2 = ((NEModuleCodeSetKey&) ks[ks.push(NEModuleCodeSetKey(NEModuleCodeSet(), "do this!"))]).getValue();
		NEModuleManager& mm = Kernal::getInstance().getModuleManager();	
		temp2.create(2);
		temp2.push(mm.getModule(NEExportable::Identifier("CooeeHandler", "kniz", 1)));
		temp2.push(mm.getModule(NEExportable::Identifier("CooeeHandler", "kniz", 1)));
	}
// 	NENode& n2 = ns[ns.push(NENode())];
// 	{
// 		n2.getKeySet().create(1);
// 		NENodeCodeSetKey& nsk = (NENodeCodeSetKey&) n2.getKeySet()[n2.getKeySet().push(NENodeCodeSetKey(NENodeCodeSet(), "추가퀘스트"))];
// 		nsk.getValue().create(1);
// 		nsk.getValue().push(n1);
// 	}
// 	NENode& n3 = ns[ns.push(n1)];
	
//	LG::Core::open(Modifier<NEModuleSelector>(*(new NEModuleSelector())))
	LG::Core::open(Modifier<NEModuleSelector>(*(new NEModuleSelector())));

}

bool chk_managers() {
	cout << "\n\n"
			"\t- Check if Manager Instances have been docked properly or not...";
	Kernal* kernel = &Kernal::getInstance();
	if( ! kernal) {	cout << "\n\t\t# Error, Kernal이 없다.\n";			return false;	}
	NENodeManager* noder = &kernal->getNodeManager();
	NEScriptManager* scr = &kernal->getScriptManager();
	if( ! noder) {	cout << "\n\t\t# Error, NodeManager가 없다.";		return false;	}
	if( ! scr) {	cout << "\n\t\t# Error, ScriptMAnager가 없다.";		return false;	}
	Editor* edit = &Editor::getInstance();
	if( ! edit) {	cout << "\n\t\t# Error, Editor가 없다.";			return false;	}
	NEScriptEditor* sced = &edit->getScriptEditor();
	NEPanelManager* pan = &edit->getPanelManager();
	NEEventHandler* hand = &edit->getEventHandler();	
	if( ! sced)	{	cout << "\n\t\t# Error, ScriptEditor가 없다.";		return false;	}
	if( ! pan)	{	cout << "\n\t\t# Error, NEPanelManager가 없다.";	return false;	}
	if( ! hand)	{	cout << "\n\t\t# Error, NEEventHandler가 없다.";	return false;	}
	
	cout << "SUCCESS\n";
	return true;
}

void end_kern()
{
	delete &Editor::getInstance();
	delete &Kernal::getInstance();
}

int main()
{
	#ifdef _UNICODE
		std::wcin.imbue( std::locale("korean") );
		std::wcout.imbue( std::locale("korean") );
	#endif

	NE_MEMORYLEAK

	init_kern();
	if( ! chk_managers()) {
		cout << "Emergency System Block...";
		system("pause");
		return 1;
	}

	NENodeCodeSet& ns = Editor::getInstance().getScriptEditor().getScriptNodes();
	NEModuleCodeSet& ms = ns[0].getModuleSet();
	const NEModuleSet& mms = Kernal::getInstance().getModuleManager().getModuleSet();
	ms.create(3);
	ms.push(mms[3]);
	ms.push(mms[4]);
	ms.push(mms[5]);

	init_wins();

	while(LG::Core::windows.getLength() > 0) {
		LG::Core::sendKeyPipe();
	}

	end_kern();

	return 0;
}