//	---------------------------------------------------------------------------------
//	클래스명:	NEDebugManager
//	설명	:	에러, 경고, 정보 메세지를 표현 및 저장하는 클래스.
//	관계	:	기반클래스.	NEModule
//	특성	:	이 역시 모듈의 일종이다.
//	알고리즘:	NEINIManager 로부터 ini를 읽어서 조건에 맞는 동작을 수행한다.
//	사용방법:	에러메세지를 남기고자 할때는 DebugMacro.hpp를 참조하라.
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once	

//	include:
#include "../NEModule/NEModule.hpp"

#ifdef DEVELOPER
#	include <iostream>
#	include <time.h>

namespace NE
{	
	class NE_DLL NEDebugManager: public NEModule
	{
		//	내부클래스:
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"
#include "innerclass/Flag/Flag.hpp"
#include "innerclass/DebugMacro/DebugMacro.hpp"
#include "innerclass/FlagSet/FlagSet.hpp"

		//	생성자:
	public:
		NEDebugManager();
		NEDebugManager(const NEDebugManager& source);

		//	소멸자:
	public:
		virtual ~NEDebugManager();
		
	public:
		const NEDebugManager& operator=(const NEDebugManager& source);

		//	접근자:
	public:
		bool isDebugModeEnabled() const;
		void setDebugMode(bool debug_mode);		
		bool isConsoleEnabled() const;
		void setConsoleEnabled(bool enable);
		bool isLogEnabled() const;
		void setLogEnabled(bool enable);
		bool isMessageBoxEnabled() const;
		void setMessageBoxEnabled(bool enable);
		bool isDebugWindowEnabled() const;
		void setDebugWindowEnabled(bool enable);
		bool isErrorLevelEnabled() const;
		void setErrorLevelEnabled(bool enable);
		bool isWarningLevelEnabled() const;	
		void setWarningLevelEnabled(bool enable);	
		bool isInformationLevelEnabled() const;
		void setInformationLevelEnabled(bool enable);
		FlagSet& getFlagSet();
		const FlagSet& getFlagSet() const;
		
		//	인터페이스:
		//		상속:
		//			NEDebugManager:
	public:
		virtual type_result initialize();
		//			NEExportable:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;
		//			NEUnit:
	private:
		virtual type_result execute();
		//			NEObject:
	public:
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEObject& clone() const;
		virtual type_result isValid() const;
		virtual void release();
		virtual NEType::Type getType() const;
		
		//		고유 인터페이스:
	public:
		type_result openConsole();
		type_result closeConsole();
		void loadFromINI();
		void saveToINI() const;
		void printDebugWindow(NETString message) const;
		void printMessageBox(NETString message) const;
		void writeLogFile(NETString message);
		void printConsole(NETString message);
		void alert(NETString debug_message);
		void _cdecl alert(const NEExportable::Identifier& identifier, NEResult::Level level, LPCTSTR printf_type_string, ...);
		bool isAcceptedLevel(NEResult::Level level) const;
		bool isConsoleOpened() const;
		
		//	내부함수:
	private:		
		type_result _initialize();
		const NEDebugManager& _assign(const NEDebugManager& source);
		void _release();
		type_result _loadModuleDebugFlag(const NEExportable::Identifier& identifier, NE_OUT TCHAR& loaded_data);
		type_result _loadFlag(LPCTSTR search_string, NE_OUT bool& loaded_data);
		void _loadFlagFromINI();
		void _loadFlagSetFromINI();
		void _saveModuleDebugFlag(const NEModule& module) const;
		void _saveFlag(bool flag, LPCTSTR search_string) const;
		void _saveFlagToINI() const;
		void _saveFlagSetToINI() const;
		void _openLogFile();
		void _closeLogFile();
		void _checkFolderExist() const;
		NETString _generateFilename() const;
		NETString _getDate() const;
		NETString _getTime() const;
		
		//	멤버 변수:
	protected:
		//		Flag:
		//			ModuleFlag:
		FlagSet _flagset;
		//			DebugFlag:
		bool _debug_mode_enabled;
		bool _console_enabled;
		bool _log_enabled;
		bool _messagebox_enabled;
		bool _debugwindow_enabled;
		bool _error_enabled;
		bool _warning_enabled;
		bool _information_enabled;
		//		FileSaver:
		NESequencialFileSaver _saver;
		//			console:
		/*
						콘솔창을 자기가 열었다면, 소멸자에서 콘솔창을 닫고 소멸해야 한다.
		*/
		bool _did_i_open_the_console;
	};
}
#else
namespace NE
{
	class NE_DLL NEDebugManager : public NEDebugManager
	{
		//	내부클래스:
	public:
#include "innerclass/DebugMacro/DebugMacro.hpp"

		//	생성자:
	public:
		NEDebugManager();
		NEDebugManager(const NEDebugManager& source);

		//	소멸자:
	public:
		virtual ~NEDebugManager();

		//	인터페이스:
		//		상속:
		//			NEDebugManager:
	public:
		virtual const NEExportable::Header& getHeader() const;
		//			NEUnit:
	public:
		virtual type_result execute();
		//			NEObject:
	public:
		virtual NEType::Type getType() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEObject& clone() const;
		virtual type_result isValid() const;
		virtual void release();
	};
}
#endif
