#include "FrameCounter.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL FrameCounter::FrameCounter()
		: NEModule()
	{
					
	}

	NE_DLL FrameCounter::FrameCounter(const FrameCounter& source)
		: NEModule(source)
	{
		
	}

	NE_DLL FrameCounter::~FrameCounter()
	{

	}
	
	type_result NE_DLL FrameCounter::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push( NEIntKey(0) );
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL FrameCounter::execute()
	{
		//	타겟팅:
		static_cast<NEIntKey&>(getKeySet()[0]).getValue() = Kernal::getInstance().getNodeManager().getLocalStack().getFrameCount();

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &FrameCounter::clone() const
	{
		return *(new FrameCounter(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &FrameCounter::getHeader() const
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
			_header.setMaxErrorCodeCount(FrameCounter::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL FrameCounter::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		default:
			return _T("알수 없는 에러");
		}
	}
}
