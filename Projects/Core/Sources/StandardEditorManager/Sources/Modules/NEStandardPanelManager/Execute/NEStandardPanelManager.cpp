#include "NEStandardPanelManager.hpp"
#include "../define/define.hpp"

namespace NE
{
	NE_DLL NEStandardPanelManager::NEStandardPanelManager()
		: NEPanelManager()
	{
		_release();
	}

	NE_DLL NEStandardPanelManager::NEStandardPanelManager(const NEStandardPanelManager& source)
			: NEPanelManager(source)
	{
		
	}

	NE_DLL NEStandardPanelManager::~NEStandardPanelManager()
	{

	}
	
	const NEStandardPanelManager NE_DLL &NEStandardPanelManager::operator=(const NEStandardPanelManager& source)
	{
		NEPanelManager::operator=(source);
		
		return _assign(source);
	}

	bool NE_DLL NEStandardPanelManager::operator==(const NEStandardPanelManager& source)
	{
		if(this == &source) return true;		
		if(NEPanelManager::operator!=(source)) return false;
		if(_dllheaderset != source._dllheaderset) return false;
		if(_panelset != source._panelset) return false;
		
		return true;
	}

	bool NE_DLL NEStandardPanelManager::operator!=(const NEStandardPanelManager& source)
	{
		return !(operator==(source));
	}
	
	
	
	//	---------------------------------------------------------------------------------
	//	설명	:	주어진 패널식별자로 패널을 검색한다.
	//	알고리즘:	최선책과 차선책에 대해서
	//					:	최선책이란 패널이름, 제작자와 개정횟수까지 일치하는 걸 말하며,
	//						완벽하게 같은 패널임을 입증하는 것을 말한다. 
	//						검색 우선순위 1 순위다.
	//						차선책은 검색 우선순위 2순위로, 최선책이 존재하지 않을때 결정
	//						한다.
	//						조건은 "패널이름", "제작자"는 같은나 버전은 다른 경우를 말한다.
	//						대개, 이때의 개정횟수은 "제시한 개정횟수보다 높은 버전"이며,
	//						target의 호환성(compatibilities)에 source의 버전이 포함된 경우를
	//						말한다.
	//	동작조건:	
	//	메모	:	식별자란, "이름", "개정번호", "제작자"를 말한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEPanel NE_DLL &NEStandardPanelManager::getPanel(const NEExportable::Identifier& identifier)
	{
		//	pre:
		NEPanel* null_pointer = NE_NULL;


		//	main:
		type_index	second_fit_index = -1; // 이름과 차선책. 만약 차선책조차 없다면 -1이 유지된다.
		int	second_fit_revision = 0; // 차선책의 개정횟수

		for(type_index n=0; n < _panelset.getLength() ;n++)
		{
			const NEExportable::ModuleHeader& header = _panelset.getElement(n).getHeader();

			//	만약 제작자와 이름이 같다면:
			if(identifier.isSameModule(header))
			{
				//	같은 종류의 패널을 발견한 경우:
				//		개정횟수마져 일치하면:
				if(header.getRevision() == identifier.getRevision())
				{
					//		최선책 발견:	더이상 검색할 이유가 없다.
					return _panelset.getElement(n);
				}
				else //	차선책 경합:
				{
					//		보다 최신 패널인지 판단:	현재 알고있는 차선책의 개정횟수보다 큰가?
					if(header.getRevision() > second_fit_revision)
					{
						//		호환성 판단:	호환이 가능한 버전인지 확인할 필요성이 생겼다.
						const NEIntSet& compatibilities = header.getRevisionCompatibilities();

						for(type_index iterator=0; iterator < compatibilities.getLength() ;iterator++)
						{
							//		만약 타겟의 호환 가능한 개정횟수에, 인자로 주어진 패널의 개정횟수가 포함된다면,					
							if(identifier.getRevision() == compatibilities.getElement(iterator))
							{
								//		타겟이 보다 높은 버전일 가능성이 크다.
								//		차선책 갱신:	차선책을 갱신할 필요가 있다.
								second_fit_revision = header.getRevision();
								second_fit_index = n;
							}
						}
					}
				}
			}
		}



		//	post:	모든 탐색을 실시했으나 최선책을 찾지 못했다.
		//			차선책으로 갱신된 인덱스가 가리키는 패널을 내보낸다.
		//		차선책을 찾았다면:
		if(second_fit_index != -1)
		{
			ALERT_WARNING("W201011C45 : 비슷한 패널만 검색됨\n주어진 패널의 이름, 개발자, 개정번호까지 일치하는 패널은 없었습니다.\n개발자와 이름이 같은 것으로 보아, 동일한 패널로 보이나, 개정번호가 다른 패널은 찾았습니다.\n패널 매니져는 이 패널을 반환할 것입니다.\n찾으려는 식별자 :\n\t이름 : %s\n\t개발자 : %s\n\t개정번호 : %d\n대신 찾은 패널의 개정번호 : %d", identifier.getName().toCharPointer(), identifier.getDeveloper().toCharPointer(), identifier.getRevision(), _panelset.getElement(second_fit_index).getHeader().getRevision())
			return _panelset.getElement(second_fit_index);
		}
		else//	차선책을 찾지 못했다면:	만약 차선책조차 찾지 못했다면 처음에 second_fit_index로 주어졌던
			//							더미패널이 내보내질 것이다.
		{		
			ALERT_ERROR("E201011C44 : 일치하는 패널 검색 실패\n주어진 패널의 이름, 개발자와 일치하는 패널이 없습니다. 패널매니져는 더미패널을 반환할 것입니다.\n찾으려는 식별자 :\n\t이름 : %s\n\t개발자 : %s\n\t개정번호 : %d", identifier.getName().toCharPointer(), identifier.getDeveloper().toCharPointer(), identifier.getRevision())
			return *null_pointer;
		}
	}
	
	const NEPanel NE_DLL &NEStandardPanelManager::getPanel(const NEExportable::Identifier& identifier) const
	{
		//	pre:
		NEPanel* null_pointer = NE_NULL;


		//	main:
		type_index	second_fit_index = -1; // 이름과 차선책. 만약 차선책조차 없다면 -1이 유지된다.
		int	second_fit_revision = 0; // 차선책의 개정횟수

		for(type_index n=0; n < _panelset.getLength() ;n++)
		{
			const NEExportable::ModuleHeader& header = _panelset.getElement(n).getHeader();

			//	만약 제작자와 이름이 같다면:
			if(identifier.isSameModule(header))
			{
				//	같은 종류의 패널을 발견한 경우:
				//		개정횟수마져 일치하면:
				if(header.getRevision() == identifier.getRevision())
				{
					//		최선책 발견:	더이상 검색할 이유가 없다.
					return _panelset.getElement(n);
				}
				else //	차선책 경합:
				{
					//		보다 최신 패널인지 판단:	현재 알고있는 차선책의 개정횟수보다 큰가?
					if(header.getRevision() > second_fit_revision)
					{
						//		호환성 판단:	호환이 가능한 버전인지 확인할 필요성이 생겼다.
						const NEIntSet& compatibilities = header.getRevisionCompatibilities();

						for(type_index iterator=0; iterator < compatibilities.getLength() ;iterator++)
						{
							//		만약 타겟의 호환 가능한 개정횟수에, 인자로 주어진 패널의 개정횟수가 포함된다면,					
							if(identifier.getRevision() == compatibilities.getElement(iterator))
							{
								//		타겟이 보다 높은 버전일 가능성이 크다.
								//		차선책 갱신:	차선책을 갱신할 필요가 있다.
								second_fit_revision = header.getRevision();
								second_fit_index = n;
							}
						}
					}
				}
			}
		}



		//	post:	모든 탐색을 실시했으나 최선책을 찾지 못했다.
		//			차선책으로 갱신된 인덱스가 가리키는 패널을 내보낸다.
		//		차선책을 찾았다면:
		if(second_fit_index != -1)
		{
			ALERT_WARNING("W201011C45 : 비슷한 패널만 검색됨\n주어진 패널의 이름, 개발자, 개정번호까지 일치하는 패널은 없었습니다.\n개발자와 이름이 같은 것으로 보아, 동일한 패널로 보이나, 개정번호가 다른 패널은 찾았습니다.\n패널 매니져는 이 패널을 반환할 것입니다.\n찾으려는 식별자 :\n\t이름 : %s\n\t개발자 : %s\n\t개정번호 : %d\n대신 찾은 패널의 개정번호 : %d", identifier.getName().toCharPointer(), identifier.getDeveloper().toCharPointer(), identifier.getRevision(), _panelset.getElement(second_fit_index).getHeader().getRevision())
			return _panelset.getElement(second_fit_index);
		}
		else//	차선책을 찾지 못했다면:	만약 차선책조차 찾지 못했다면 처음에 second_fit_index로 주어졌던
			//							더미패널이 내보내질 것이다.
		{		
			ALERT_ERROR("E201011C44 : 일치하는 패널 검색 실패\n주어진 패널의 이름, 개발자와 일치하는 패널이 없습니다. 패널매니져는 더미패널을 반환할 것입니다.\n찾으려는 식별자 :\n\t이름 : %s\n\t개발자 : %s\n\t개정번호 : %d", identifier.getName().toCharPointer(), identifier.getDeveloper().toCharPointer(), identifier.getRevision())
				return *null_pointer;
		}
	}

	const NEPanelManager::DLLHeaderList NE_DLL &NEStandardPanelManager::getPanelHeaderList() const
	{
		return _dllheaderset;
	}

	NEPanelSet NE_DLL &NEStandardPanelManager::getPanelSet()
	{
		return _panelset;
	}

	const NEPanelSet NE_DLL &NEStandardPanelManager::getPanelSet() const
	{
		return _panelset;
	}
	
	type_result NE_DLL NEStandardPanelManager::initialize()
	{
		//	pre:		
		//		초기화:
		_release(); // release()를 하면 안된다.




		//	main:
		//		모듈 Fetch:
		_linkDLL();
		_linkPanel();

		return RESULT_SUCCESS;
	}

	type_result NE_DLL NEStandardPanelManager::execute()
	{
		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &NEStandardPanelManager::clone() const
	{
		return *(new NEStandardPanelManager(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &NEStandardPanelManager::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T( _NAME );
			_header.getDeveloper() = _T( _AUTHOR );
			_header.setRevision(_REVISION);
			_header.getComment() = _T( _COMMENT );
			_header.getVersion()  = _T( _VERSION );
			_header.getReleaseDate() = _T( _DATE );
			_header.getModuleDependencies().create(_DEPENDENCIES_COUNT);
			_header.setMaxErrorCodeCount(NEStandardPanelManager::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL NEStandardPanelManager::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		default:
			return _T("알수 없는 에러");
		}
	}
	
	
	
	void NE_DLL NEStandardPanelManager::release()
	{
		NEPanelManager::release();
		
		_release();
	}

	type_result NE_DLL NEStandardPanelManager::isValid() const
	{
		type_result result = NEPanelManager::isValid();
		if(NEResult::hasError(result)) return result;
		result = _dllheaderset.isValid();
		if(NEResult::hasError(result)) return result;
		result = _panelset.isValid();
		if(NEResult::hasError(result)) return result;
		
		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	연결된 DLL 파일로부터, 실행 엔트리포인트에 접근해서 패널을 가져온다.
	//	동작조건:
	//	메모	:	가져온 패널은 의존성을 고려해서 재 정렬한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEStandardPanelManager::_linkPanel()
	{
		//	배경:	
		//		의존성:	
		//				패널에는 의존성이라는 게 존재하는데,
		//				이는 초기화시에, 다른 패널이 먼저 초기화되어있야 함을 의미한다.
		//	
		//				예를 들어, 윈도우의 DC를 얻어서 조작하는 패널이 있을 경우,
		//				이 패널은 윈도우를 생성하는 패널이 먼저 초기화가 되어야만 초기화가 가능할 것이다.
		//				또한 소멸의 경우도, 윈도우 패널이 먼저 소멸되어서는 안된다.
		//
		//		의존성 재정렬:
		//				이러한 의존성을 사전에 파악, 초기화가 일어나기 전에 정렬해,
		//				배치하는 것을 말한다.
		//				초기화는 0번부터 일어나므로, 의존성이 적은 패널일 수록 앞자리에 위치하게 된다.
		//				소멸은 뒷자리부터 일어나게 된다.



		//	main:
		//		임시 버퍼 생성:
		NEPanelList bucket; // 나중에 _panelset로 값을 넘겨줄 리스트. DLL 엔트리 포인트로부터 여기에 패널을 채우게 된다.			

		//		버퍼에 데이터 축적:
		for(type_index n=0; n < _dllheaderset.getLength() ;n++)
			bucket.push(_dllheaderset[n].getPanelEntryPoint()()); // entrypoint로부터 NEListTemplate가 넘어온다.

		//		중복 제거 필터링:
		_filterNestedName(bucket);

		//		패널셋에 데이터 축적:	정렬된 임시버퍼를 복사한다
		_pushPanelSet(bucket);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	최종적으로 의존성을 고려해서 정렬된 패널리스트로부터 패널을 복사한다.
	//	동작조건:
	//	메모	:	push되는 순서대로 패널의 scriptcode를 부과한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEStandardPanelManager::_pushPanelSet(NEPanelList& buffer)
	{
		//	pre:
		if(buffer.getLength() <= 0) return;



		//	main: buffer의 담긴 패널을 최종적으로 _panelset에 넣는다
		//		패널셋의 버퍼공간 생성:	
		_panelset.create(buffer.getLength());		

		//		buffer로부터의 복사:
		for(NEPanelList::Iterator* iterator = buffer.getIterator(0); iterator != NE_NULL ;iterator = iterator->getNext())
		{
			NEPanel& target = iterator->getValue();
			_panelset.push(target);
		}
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	추가하려는 패널이 이미 존재하는 패널이름을 갖고 있다면, 보다 최신버전
	//				만 넣으려 한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEStandardPanelManager::_filterNestedName(NEPanelList& source)
	{
		//	main:
		for(type_index n=0; n < source.getLength() ;n++)
		{		
			//	대상1 추출:
			const NEExportable::ModuleHeader& source_header = source[n].getHeader();

			//	대상1과 비교:	대상1과 같은 패널이 있는지 확인한다
			for(type_index target_index = n+1; target_index < source.getLength() ; target_index++)
			{
				//	대상2 추출:
				const NEExportable::ModuleHeader& target_header = source[target_index].getHeader();

				//	조건1:	완전히 같은 패널을 발견했다면
				if( source_header.NEExportable::Identifier::operator==(target_header) )
				{	
					//	추가 하지 않는다:
					source.remove(target_index); 
#ifdef DEVELOPER
					ALERT_WARNING("W201011C41 : 동일한 패널 복수 존재\n같은 식별자를 지닌 패널이 2개 이상 존재합니다.\n패널매니져는 나중에 식별한 패널은 읽지 않을 것입니다.\n동일한 패널의 식별자:\n\t이름 : %s\n\t개발자 : %s\n\t개정번호 : %d", target_header.getName().toCharPointer(), target_header.getDeveloper().toCharPointer(), target_header.getRevision())
#endif
					break;
				}
			}
		}
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	지정된 폴더에 존재하는 DLL 파일을 검색한다.
	//	동작조건:
	//	메모	:	NEFileSystem의 검색기능을 사용한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEStandardPanelManager::_linkDLL()
	{
		//	pre:
		//		버퍼 준비:
		NETString path = Editor::getInstance().getSettings().getPanelDirectory() + _T("\\*.dll");



		//	main:
		//		검색 준비:
		NEFileSystem filesystem(path.toCharPointer(), true); //	테스트니까 일단 풀 경로를 지정한다. 릴리즈에서는 "Modules/*.dll" 만 하면 됨
		//		루핑:
		
		while(true)
		{
			filesystem.findFile();
			const NEFileSystem::TaskUnit& task = filesystem.getLastElement();
			if( ! &task) break;
			
			_pushDLLHeader(task.getFilePath());
		}
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	검색한 DLL 파일을 프로세스에 올리고, 엔트리포인트의 주소를 가져온다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEStandardPanelManager::_pushDLLHeader(LPCTSTR dllpath)
	{
		//	배경:
		//		왜 push를 하고 참조자를 가져오는가:
		//			push하는 과정에서 소멸자와 복사생성자가 호출되기 때문이다.
		//			Header의 소멸자는 FreeLibrary를 호출해서 연결한 DLL을 소멸시킨다.
		//			이런 오버헤드를 줄이기 위해서, 미리 값을 집어넣고 외부에서 조작한다


		//	pre:
		//		파라메터 검사:
		if(!dllpath) return;
		//		타겟팅:
		NEINIManager& ini = Kernal::getInstance().getINIManager();



		//	main:
		//		헤더 버퍼 생성:	
		_dllheaderset.push(StandardPanelDLLHeader());
		//		버퍼 타겟팅:
		NEPanelManager::DLLHeader& target = _dllheaderset[_dllheaderset.getLengthLastIndex()];
		//		기본적인 정보 삽입:
		//			경로:
		target.getType();
		target.getPanelEntryPoint();
		target.getPath() = dllpath; // NETString에 의해서 동적생성된다.
		//			인스턴스:
		target.setInstance( LoadLibrary(target.getPath().toCharPointer()) );
		//			읽기 가능 flag:
		//				버퍼 생성:
		NETString value;
		//				INI로부터 값 가져옴:
		type_result result = ini.readModuleIniString(getHeader(), dllpath, value);
		//		로드 여부 조건 검사:
		//			만약 에러가 발생했다면:
		if(NEResult::hasError(result))			
			ini.writeModuleIniString(getHeader(), target.getPath(), NETString(true));
		else	//	에러가 없다면:
		{
			//			가져온 값이 false(로드 안함) 이라면:
			if( ! value.toBoolean())
			{
				ALERT_INFORMATION("I201011C53 : DLL 동적 연결 취소\nINI를 통해서 발견한 DLL을 로드 하지 않기로 했습니다.\n로드하고 싶다면 INI의 키값을 false에서 true로 바꾸십시오.\n취소된 DLL 파일명 : %s", target.getPath().toCharPointer())
				_dllheaderset.pop();
				return;
			}
		}
		//		조건1:	DLL을 못 읽었다면
		if( ! target.getInstance())
		{	//		파일을 읽지 못했음:
#ifdef _DEBUG
			ALERT_ERROR("E201011C40 : DLL 동적 연결 실패\nDLL은 찾았으나 동적 연결에 실패했습니다.\n올바른 DLL 파일이 아니거나, 릴리즈 / 디버그 모드가 다를 경우 이 메세지가 발생할 수 있습니다.\n다시 확인 해보십시오.\nKernal 빌드 모드 : Debug\n파일명 : %s", target.getPath().toCharPointer())
#else
			ALERT_ERROR("E201011C40 : DLL 동적 연결 실패\nDLL은 찾았으나 동적 연결에 실패했습니다.\n올바른 DLL 파일이 아니거나, 릴리즈 / 디버그 모드가 다를 경우 이 메세지가 발생할 수 있습니다.\n다시 확인 해보십시오.\nKernal 빌드 모드 : Release\n파일명 : %s", target.getPath().toCharPointer())
#endif		
			_dllheaderset.pop();
		}
		else
		{	//		로드 성공:
			//			진입점을 가져옴:
			target.setPanelEntryPoint( reinterpret_cast<PanelEntryPoint>(GetProcAddress(target.getInstance(), _getPanelEntryPointStringOfDLL().toCharPointer())) );

			//			조건1-1:	진입점을 가져오지 못했다면
			if( ! target.getPanelEntryPoint())
			{	//			동작 실패:	로드는 성공했지만 엔트리포인트 등록에는 실패
				ALERT_INFORMATION("I201011C39 : 실행 엔트리포인트 접근 실패\nDLL 확인 및 동적 DLL 연결에는 성공했으나 실행 엔트리 포인트에 연결하지 못했습니다.\n해당 패널 개발자가 잘못된 엔트리포인트를 사용하고 있을 가능성이 있습니다.\n패널매니져가 이 DLL을 제외할 것입니다.\n파일명 : %s", target.getPath().toCharPointer())
				_dllheaderset.pop();
			}
		}
	}

	const NEStandardPanelManager& NEStandardPanelManager::_assign(const NEStandardPanelManager& source)
	{
		if(this == &source) return *this;
		
		_dllheaderset = source._dllheaderset;
		_panelset = source._panelset;
		
		return *this;
	}

	void NEStandardPanelManager::_release()
	{
		_dllheaderset.release();
		_panelset.release();
	}

	type_result NE_DLL NEStandardPanelManager::_onFetchModule()
	{
		return RESULT_SUCCESS;
	}
}
