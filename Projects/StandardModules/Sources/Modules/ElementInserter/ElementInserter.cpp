#include "ElementInserter.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL ElementInserter::ElementInserter()
		: NEModule()
	{
				
	}

	NE_DLL ElementInserter::ElementInserter(const ElementInserter& source)
		: NEModule(source)
	{
		
	}

	NE_DLL ElementInserter::~ElementInserter()
	{

	}
	
	type_result NE_DLL ElementInserter::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push(NEKeySelector());
		getKeySet().push(NEIntKey());
		getKeySet().push(NEKeySelector());
				
		return RESULT_SUCCESS;
	}

	type_result NE_DLL ElementInserter::execute()
	{
		//	pre:		
		type_index index = (static_cast<const NEIntKey&>( getKeySet()[1] )).getValue();
		NEKeySelector	&key_to_be_inserted = static_cast<NEKeySelector&>( getKeySet()[2]),
						&collector = static_cast<NEKeySelector&>(getKeySet()[0]);



		//	main:
		bool is_there_error_cause_of_invalid_type = false;
		while(NEKey* collector_key = &collector.getKey())
		{
			while(true)
			{
				NEKey& key = key_to_be_inserted.getKey();
				if( ! &key)
					break;

				switch(collector_key->getType())
				{
				case NEType::NEBOOLEAN_SET_KEY:
					{
						NEBooleanSet& collector = (static_cast<NEBooleanSetKey&>(*collector_key)).getValue();					
						_insertToCollector(collector, index, NEBooleanKey(key).getValue());
					}				
					break;
				case NEType::NEBYTE_SET_KEY:
					{
						NEByteSet& collector = (static_cast<NEByteSetKey&>(*collector_key)).getValue();
						_insertToCollector(collector, index, NEByteKey(key).getValue());
					}
					break;
				case NEType::NEUBYTE_SET_KEY:
					{
						NEUByteSet& collector = (static_cast<NEUByteSetKey&>(*collector_key)).getValue();
						_insertToCollector(collector, index, NEUByteKey(key).getValue());
					}
					break;
				case NEType::NESHORT_SET_KEY:
					{
						NEShortSet& collector = (static_cast<NEShortSetKey&>(*collector_key)).getValue();
						_insertToCollector(collector, index, NEShortKey(key).getValue());
					}
					break;
				case NEType::NEUSHORT_SET_KEY:
					{
						NEUShortSet& collector = (static_cast<NEUShortSetKey&>(*collector_key)).getValue();
						_insertToCollector(collector, index, NEUShortKey(key).getValue());
					}
					break;
				case NEType::NEINT_SET_KEY:
					{
						NEIntSet& collector = (static_cast<NEIntSetKey&>(*collector_key)).getValue();
						_insertToCollector(collector, index, NEIntKey(key).getValue());
					}
					break;
				case NEType::NEUINT_SET_KEY:
					{
						NEUIntSet& collector = (static_cast<NEUIntSetKey&>(*collector_key)).getValue();
						_insertToCollector(collector, index, NEUIntKey(key).getValue());
					}
					break;
				case NEType::NEINT64_SET_KEY:
					{
						NEInt64Set& collector = (static_cast<NEInt64SetKey&>(*collector_key)).getValue();
						_insertToCollector(collector, index, NEInt64Key(key).getValue());
					}
					break;
				case NEType::NEFLOAT_SET_KEY:
					{
						NEFloatSet& collector = (static_cast<NEFloatSetKey&>(*collector_key)).getValue();
						_insertToCollector(collector, index, NEFloatKey(key).getValue());
					}
					break;
				case NEType::NEDOUBLE_SET_KEY:
					{
						NEDoubleSet& collector = (static_cast<NEDoubleSetKey&>(*collector_key)).getValue();
						_insertToCollector(collector, index, NEDoubleKey(key).getValue());
					}
					break;
				case NEType::NESTRING_SET_KEY:
					{
						NEStringSet& collector = (static_cast<NEStringSetKey&>(*collector_key)).getValue();
						_insertToCollector(collector, index, NEStringKey(key).getValue());
					}
					break;
				case NEType::NEWSTRING_SET_KEY:
					{
						NEWStringSet& collector = (static_cast<NEWStringSetKey&>(*collector_key)).getValue();
						_insertToCollector(collector, index, NEWStringKey(key).getValue());
					}
					break;
				default:
					is_there_error_cause_of_invalid_type = true;
					ALERT_ERROR(" : 잘못된 타입입니다.\n타입 : %d", collector_key->getType())
				}
			}
		}

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &ElementInserter::clone() const
	{
		return *(new ElementInserter(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &ElementInserter::getHeader() const
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
			_header.setMaxErrorCodeCount(ElementInserter::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL ElementInserter::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		case THERE_IS_NO_COLLECTOR_KEY:
			return _T("콜렉터가 없음");

		case INVALID_COLLECTOR_TYPE:
			return _T("ElementInserter가 지원하지 않는 콜렉터의 타입");

		default:
			return _T("알수 없는 에러");
		}
	}

	template <typename T, bool useHeap, NEType::Type type>
	type_result ElementInserter::_insertToCollector(NEArrayTemplate<T, useHeap, T, type>& collector, type_index index, const T& source)
	{
		//	pre:
		//		collector:
		if(collector.getLength() >= collector.getSize())
			collector.resize(collector.getLength() + 1);
		//		index:
		type_result result = RESULT_SUCCESS;
		if(index < 0)
		{
			result = RESULT_TYPE_WARNING;
			ALERT_WARNING(" : 인덱스가 0보다 작습니다. 0으로 강제 보정합니다.\n\t주어진 인덱스 : %d", index)
			index = 0;
		}
		if(index > collector.getLength())
			index = collector.getLength();



		//	main:
		return collector.insert(index, source);
	}
}
