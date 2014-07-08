#include "ElementRemover.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL ElementRemover::ElementRemover()
		: NEModule()
	{
				
	}

	NE_DLL ElementRemover::ElementRemover(const ElementRemover& source)
		: NEModule(source)
	{
		
	}

	NE_DLL ElementRemover::~ElementRemover()
	{

	}
	
	type_result NE_DLL ElementRemover::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push(NEKeySelector());
		getKeySet().push(NEIntKey());
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL ElementRemover::execute()
	{
		NEKeySelector& selector = static_cast<NEKeySelector&>( getKeySet()[0] );
		type_index index = (static_cast<const NEIntKey&>( getKeySet()[1] )).getValue();
		



		type_result result = RESULT_SUCCESS;

		while(true)
		{
			NEKey& collector_key = selector.getKey();
			if( ! &collector_key)
				break;

			switch(collector_key.getType())
			{
			case NEType::NEBOOLEAN_SET_KEY:
				{
					NEBooleanSet& collector = (static_cast<NEBooleanSetKey&>(collector_key)).getValue();
					NEResult::addErrorFlag(result, collector.remove(index));
				}				
				break;
			case NEType::NEBYTE_SET_KEY:
				{
					NEByteSet& collector = (static_cast<NEByteSetKey&>(collector_key)).getValue();
					NEResult::addErrorFlag(result, collector.remove(index));
				}
				break;
			case NEType::NEUBYTE_SET_KEY:
				{
					NEUByteSet& collector = (static_cast<NEUByteSetKey&>(collector_key)).getValue();
					NEResult::addErrorFlag(result, collector.remove(index));
				}
				break;
			case NEType::NESHORT_SET_KEY:
				{
					NEShortSet& collector = (static_cast<NEShortSetKey&>(collector_key)).getValue();
					NEResult::addErrorFlag(result, collector.remove(index));
				}
				break;
			case NEType::NEUSHORT_SET_KEY:
				{
					NEUShortSet& collector = (static_cast<NEUShortSetKey&>(collector_key)).getValue();
					NEResult::addErrorFlag(result, collector.remove(index));
				}
				break;
			case NEType::NEINT_SET_KEY:
				{
					NEIntSet& collector = (static_cast<NEIntSetKey&>(collector_key)).getValue();
					NEResult::addErrorFlag(result, collector.remove(index));
				}
				break;
			case NEType::NEUINT_SET_KEY:
				{
					NEUIntSet& collector = (static_cast<NEUIntSetKey&>(collector_key)).getValue();
					NEResult::addErrorFlag(result, collector.remove(index));
				}
				break;
			case NEType::NEINT64_SET_KEY:
				{
					NEInt64Set& collector = (static_cast<NEInt64SetKey&>(collector_key)).getValue();
					NEResult::addErrorFlag(result, collector.remove(index));
				}
				break;
			case NEType::NEFLOAT_SET_KEY:
				{
					NEFloatSet& collector = (static_cast<NEFloatSetKey&>(collector_key)).getValue();
					NEResult::addErrorFlag(result, collector.remove(index));
				}
				break;
			case NEType::NEDOUBLE_SET_KEY:
				{
					NEDoubleSet& collector = (static_cast<NEDoubleSetKey&>(collector_key)).getValue();
					NEResult::addErrorFlag(result, collector.remove(index));
				}
				break;
			case NEType::NESTRING_SET_KEY:
				{
					NEStringSet& collector = (static_cast<NEStringSetKey&>(collector_key)).getValue();
					NEResult::addErrorFlag(result, collector.remove(index));
				}
				break;
			case NEType::NEWSTRING_SET_KEY:
				{
					NEWStringSet& collector = (static_cast<NEWStringSetKey&>(collector_key)).getValue();
					NEResult::addErrorFlag(result, collector.remove(index));
				}
				break;
			default:
				NEResult::setErrorCode(result, INVALID_DATA_TYPE);
				ALERT_ERROR(" : 잘못된 타입입니다.\n타입 : %d", collector_key.getType())
			}
		}
		

		return result;
	}

	NEObject NE_DLL &ElementRemover::clone() const
	{
		return *(new ElementRemover(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &ElementRemover::getHeader() const
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
			_header.setMaxErrorCodeCount(ElementRemover::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL ElementRemover::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		case INVALID_DATA_TYPE:
			return _T("알수 없는 콜렉터 타입");

		default:
			return _T("알수 없는 에러");
		}
	}
}
