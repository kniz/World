#include "CooeeHandler.hpp"
#include "../define/define.hpp"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

namespace NE
{
	NE_DLL CooeeHandler::CooeeHandler()
		: NEEventHandler(), _test_kernal(NE_NULL)
	{
		
	}

	NE_DLL CooeeHandler::CooeeHandler(const CooeeHandler& source)
		: NEEventHandler(source), _test_kernal(0)
	{
		
	}

	NE_DLL CooeeHandler::~CooeeHandler()
	{
		if(_test_kernal)	
			delete _test_kernal;
	}

	const CooeeHandler NE_DLL &CooeeHandler::operator=(const CooeeHandler& source)
	{
		if(this == &source) return *this;
		NEEventHandler::operator=(source);

		_test_kernal = source._test_kernal;

		return *this;
	}

	bool NE_DLL CooeeHandler::operator==(const CooeeHandler& source) const
	{
		if(this == &source) return true;
		if(NEEventHandler::operator!=(source)) return false;
		if(_test_kernal != source._test_kernal) return false;

		return true;
	}

	bool NE_DLL CooeeHandler::operator!=(const CooeeHandler& source) const
	{
		return !(operator==(source));
	}

	NEObject NE_DLL &CooeeHandler::clone() const
	{
		return *(new CooeeHandler(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &CooeeHandler::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T( _NAME );
			_header.getDeveloper() = _T( _DEVELOPER );
			_header.setRevision(_REVISION);
			_header.getComment() = _T( _COMMENT );
			_header.getVersion()  = _T( _VERSION );
			_header.getReleaseDate() = _T( _DATE );
			_header.getModuleDependencies().create(_DEPENDENCIES_COUNT);
			_header.setMaxErrorCodeCount(CooeeHandler::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL CooeeHandler::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		default:
			return _T("알수 없는 에러");
		}
	}
	
	type_result NE_DLL CooeeHandler::execute()
	{
		return RESULT_SUCCESS;
	}

	type_result NE_DLL CooeeHandler::runTest()
	{
		//	pre:
		/*		테스트 커널을 사용한 커널스위칭:
					initialize시, _getKernalFactory를 통해서 가져온 Factory로 kernal을 만들어서 _test_kernal에 할당한다.
					그리고 _test_kernal.initialize()를 실시한다.
					이제부터 우리가 수정하게될 실제 스크립트의 내용은 이 _test_kernal에 최종적으로 존재하게 된다.
					Kernal::ScriptManager는 에디터에 필요한 스크립트가 존재한다. (이건 건들면 안된다)
		*/
		Editor& editor = Editor::getInstance();
		if( ! &editor)
		{
			ALERT_ERROR(" : ")
			return RESULT_TYPE_ERROR;
		}
		NEScriptEditor& scripted = editor.getScriptEditor();
		if( ! &scripted)
		{
			ALERT_ERROR(" : ")
			return RESULT_TYPE_ERROR;
		}
		if(!_test_kernal)
		{
			ALERT_ERROR("  : ")
				return RESULT_TYPE_ERROR;
		}
		NEScriptManager& test_scripter = _test_kernal->getScriptManager();
		if( ! &test_scripter)
		{
			ALERT_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}
		NENodeManager& noder = _test_kernal->getNodeManager();
		if( ! &noder)
		{
			ALERT_ERROR(" : ")
			return RESULT_TYPE_ERROR;
		}
		//		스크립트를 일단 동기화:
		scripted.synchronizeTo(test_scripter);
		//		커널 할당:
		Kernal& original = Kernal::getInstance(); // 원본 보관
		Kernal::setInstance(*_test_kernal); // 포인터 자체의 할당(얇은 복사)
		Kernal& kernal = Kernal::getInstance();
		//		테스트 커널의 노드매니져 초기화:	
		noder.initialize();
		
		
		
		//	main:
		//		프레임 묻기:
		cout << "테스트를 몇 프레임 실행할까요? -> ";
		type_count count = 0;
		cin >> count;
		//		실행:		
		for(int n=0; n < count ;n++)
		{
			noder.execute();

			if( ! (n % 100))
				cout << count << "번 중에서 " << n << "번 실행했습니다.\n";
		}
			
			

		//	post:
		//		테스트 커널 정리:
		_test_kernal->getNodeManager().getRootNodes().release();
		//		원본 복구:
		Kernal::setInstance(original);

		return RESULT_SUCCESS;
	}

	type_result NE_DLL CooeeHandler::initialize()
	{
		//	main:
		//		커널스위칭:
		//			원본 보관:		
		Kernal& original = Kernal::getInstance();
		//			테스트 커널 생성:
		_test_kernal = new Kernal(_getKernalFactory().create());
		//			스위칭:
		Kernal::setInstance(*_test_kernal); // 포인터로 할당하면 얇은 복사가 된다
		//		테스트 커널 초기화:
		type_result result = Kernal::getInstance().initialize();
		if(NEResult::hasError(result))
			ALERT_ERROR(" : 커널을 초기화 하는 중 에러가 발생했습니다.");



		//	post:
		//		원본 복구:
		return Kernal::setInstance(original);
	}

	void CooeeHandler::release()
	{
		NEModule::release();

		_test_kernal->release();
	}

	type_result CooeeHandler::isValid() const
	{
		type_result result = NEModule::isValid();
		if(NEResult::hasError(result)) return result;
		if(!_test_kernal) return RESULT_TYPE_ERROR;
		result = _test_kernal->isValid();
		if(NEResult::hasError(result)) return result;

		return RESULT_SUCCESS;
	}

	Kernal::Factory CooeeHandler::_getKernalFactory() const
	{
		//	pre:
		//		타겟팅:
		Kernal& kernal = Kernal::getInstance();		
		if(! &kernal)
		{
			return Kernal::Factory();
		}
		NEINIManager& ini = kernal.getINIManager();
		//		디폴트 입력:
		Kernal::Factory factory;
		Kernal::ModifiableSettings settings(kernal.getSettings());
		settings.getTitle() = _T(_DEFAULT_TEST_KERNAL_TITLE);
		settings.getINIFullPath() = _T(_DEFAULT_TEST_KERNAL_INI_FULL_PATH);
		settings.getINIForms() = _T(_DEFAULT_TEST_KERNAL_INI_FORMS);
		settings.setModuleDirectory(_T(_DEFAULT_TEST_KERNAL_MODULE_DIRECTORY));
		settings.getNodeExtractor() = _T(_DEFAULT_TEST_KERNAL_NODE_EXTRACTOR);
		settings.setLoadFromINI(true);
		settings.setLogDirectory(_T(_DEFAULT_TEST_KERNAL_LOG_DIRECTORY));
		settings.setScriptDirectory(_T(_DEFAULT_TEST_KERNAL_SCRIPT_DIRECTORY));
		settings.setNodeDirectory(_T(_DEFAULT_TEST_KERNAL_NODE_DIRECTORY));

		cout	<< "테스트 커널의 모듈디렉토리를 정해주세요\n"
				<< "\t0. 커널 모듈 디렉토리를 공유 : " << Kernal::getInstance().getSettings().getModuleDirectory().toCharPointer() << endl
				<< "\t1. 테스트 커널용 모듈 디렉토리 : " << settings.getModuleDirectory().toCharPointer() << endl;

		cout << " 어느걸로? -> ";
		type_index index = 0;
		cin >> index;
		if(! index)
			settings.setModuleDirectory(Kernal::getInstance().getSettings().getModuleDirectory());
		
		
		
		//	main:
		factory.getDefaultSettings() = settings;
		//		identifier:
#ifdef DEVELOPER
#	ifdef _DEBUG
		factory.getNodeManagerIdentifier() = NEExportable::Identifier(_T("NEStandardNodeManager"), _T("haku"), 1);
		factory.getScriptManagerIdentifier() = NEExportable::Identifier(_T("NEStandardScriptManager"), _T("haku"), 1);
#	else
		factory.getNodeManagerIdentifier() = NEExportable::Identifier(_T("NEStandardNodeManager"), _T("haku"), 1);
		factory.getScriptManagerIdentifier() = NEExportable::Identifier(_T("NEStandardScriptManager"), _T("haku"), 1);
#	endif
#endif

		return factory;
	}

	type_result NE_DLL CooeeHandler::initializeNewFile()
	{
		//	pre:
		//		타겟팅:
		if(!_test_kernal)
		{
			ALERT_ERROR("  : ")
			return RESULT_TYPE_ERROR;
		}
		NEScriptManager& test_scripter = _test_kernal->getScriptManager();
		if( ! &test_scripter)
		{
			ALERT_ERROR(" : ")
				return RESULT_TYPE_ERROR;
		}
		NENodeManager& test_noder = _test_kernal->getNodeManager();
		if( ! &test_noder)
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



		//	main:
		//		TestKernal 초기화:
		test_scripter.release();
		test_noder.release();
		//		ScriptEditor 초기화:
		synchronizer.initialize();



		return RESULT_SUCCESS;
	}
}
