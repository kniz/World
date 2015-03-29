#include "Console.hpp"
#include <iostream>

namespace Console
{
	using namespace NE;
	const NEExportable::ModuleHeader& Console::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING) {
			_header.getName() = "Console";
			_header.getDeveloper() = "kniz";
			_header.setRevision(1);
			_header.getComment() = "콘솔창에 주어진 문장을 출력하거나 입력을 받아 키에 저장합니다.";
			_header.getVersion() = "0.0.1a";
			_header.getReleaseDate() = "2015-03-23";
			NE::NETStringSet& args = _header.getArgumentsComments();
			args.create(1);
			args.push("String\nREAD로 하면 키값을 읽어서 화면에 출력합니다.\nWRITE로 하면 입력을 받아 키에 저장합니다.");
		}

		return _header;
	}

	type_result Console::_onFetchModule()
	{
		return arg_string.setPurposeLimitation(NEArgumentBase::READ_OR_WRITTEN);
	}

	type_result Console::_onFetchArguments(NEArgumentList& tray)
	{
		tray.push(arg_string);
		return RESULT_SUCCESS;
	}

	type_result Console::_onExecute()
	{
		using namespace NE;
		using namespace std;
		NEDebugManager& debugger = Kernal::getInstance().getDebugManager();

#ifdef _UNICODE
		wostream& COUT = wcout;
		wistream& CIN = wcin;
		std::cout.imbue(std::locale("korean"));
#else
		ostream& COUT = cout;
		istream& CIN = cin;
#endif

		if( ! debugger.isConsoleOpened()) {
			type_result result = debugger.openConsole();

			if(NEResult::hasError(result))
				return ALERT_ERROR("콘솔을 열지 못했습니다.");
		}


		if (arg_string.getPurpose() == NEArgumentBase::READ_BY) {
			COUT << arg_string.getValue().toCharPointer();
		}			
		else {
			TCHAR buf[256] = {0, };
			CIN >> buf;
			arg_string.setValue(buf);
		}

		return RESULT_SUCCESS;
	}

	NEObject& Console::clone() const
	{
		return *(new Console(*this));
	}
}