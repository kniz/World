
#include "NECodeSet.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NECodeSet::NECodeSet()
		: SuperClass()
	{
		_type = NECodeType::UNDEFINED;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NECodeSet::NECodeSet(type_count size)
		: SuperClass(size)
	{
		_type = NECodeType::UNDEFINED;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NECodeSet::NECodeSet(const NECodeSet& source)
		: SuperClass(source)
	{
		_type = source._type;
	}

	NECodeSet::NECodeSet(NECodeType::CodeType initial_type)
		: SuperClass()
	{
		setCodeType(initial_type);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NECodeSet::~NECodeSet()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NECodeSet NE_DLL &NECodeSet::operator+=(const NECodeSet& source)
	{
		SuperClass::operator+=(source);

		return *this;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NECodeSet NE_DLL NECodeSet::operator+(const NECodeSet& source) const
	{
		NECodeSet buffer(getSize() + source.getSize());

		buffer.push(*this);
		buffer.push(source);

		return buffer;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEType::Type NE_DLL NECodeSet::getType() const
	{
		return NEType::NECODE_SET;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-19	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	//	save는 기존의 NEPointerArray로도 가능하다
	NEBinaryFileSaver NE_DLL &NECodeSet::serialize(NEBinaryFileSaver& saver) const
	{	
		saver << (type_uint) _type;

		return SuperClass::serialize(saver);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-19	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NECodeSet::serialize(NEBinaryFileLoader& loader)
	{	
		type_uint bucket = 0;
		loader >> bucket;
		_type = NECodeType::CodeType(bucket);
		
		return SuperClass::serialize(loader);		
	}

	NEObject NE_DLL &NECodeSet::clone() const
	{
		return *(new ThisClass(*this));
	}

	type_result NECodeSet::setElement(type_index index, const NECode& source)
	{
		if(find(source) != NE_INDEX_ERROR) return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;

		type_result result = getElement(index).setIfValid(source);

		if(_type == NECodeType::UNDEFINED)
			setCodeType(source.getCodeType());

		return result;
	}

	type_index NECodeSet::insert(type_index index, const NECode& source)
	{		
		NECode to_insert(_type, source.getCode());		
		type_index n = NE_INDEX_ERROR;

		if(find(to_insert) == NE_INDEX_ERROR) 
		{
			if(NEResult::hasError(to_insert.isValid())) return NE_INDEX_ERROR;

			n = SuperClass::insert(index, source);
		}

		if(	_type == NECodeType::UNDEFINED					&&
			source.getCodeType() != NECodeType::UNDEFINED	)
			setCodeType(source.getCodeType());

		return n;
	}

	type_index NECodeSet::insert(type_index index, const NEExportable::Identifier& identifier)
	{
		if(_type == NECodeType::SCRIPT)
		{
			const NEModule& fetched = Kernal::getInstance().getModuleManager().getModule(identifier);
			if( ! &fetched)
			{
				KERNAL_ERROR("주어진 Identifier로 모듈을 가져오지 못했습니다.");
			}
			return insert(index, NECode(_type, fetched.getScriptCode()));
		}

		KERNAL_ERROR("Script용 CodeSet이 아닌데요");
		return NE_INDEX_ERROR;
	}

	type_index NECodeSet::insert(type_index index, type_code source)
	{
		return insert(getLength(), NECode(_type, source));
	}

	type_index NECodeSet::push(const NEExportable::Identifier& identifier)
	{
		return insert(getLength(), identifier);
	}

	type_index NECodeSet::push(type_code source)
	{
		return insert(getLength(), source);
	}

	type_index NECodeSet::pushFront(const NEExportable::Identifier& identifier)
	{
		return insert(0, identifier);
	}

	type_index NECodeSet::pushFront(type_code source)
	{
		return insert(0, source);
	}

	type_result NECodeSet::setCodeType(NECodeType::CodeType type)
	{ 
		using namespace NECodeType;


		//	main:		
		switch(type)
		{		
		case SCRIPT:	case GROUP:	case NAME:		case PRIORITY:
			_type = type;
			return _synchronizeCodeType();
		case ALL:		case ME:	case RECENT:
			_type = type;
			break;

		case UNDEFINED:
			return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;
		}

		KERNAL_ERROR("잘못된 NECodeType 입니다.");
		return RESULT_TYPE_ERROR;			
	};

	NECodeType::CodeType NECodeSet::getCodeType() const
	{
		return _type;
	}

	void NECodeSet::release()
	{
		_type = NECodeType::UNDEFINED;

		return SuperClass::release();
	}

	type_result NECodeSet::_synchronizeCodeType()
	{
		for(int n=0; n < getLength(); n++)
		{
			NECode& code = getElement(n);
			if(code.getCodeType() != _type)
				code.setCodeType(_type);
		}

		return _removeInvalidCodes();
	}

	type_result NECodeSet::_removeInvalidCodes()
	{
		for(int n=0; n < getLength() ;)
			if(NEResult::hasError(getElement(n).isValid()))
				remove(n);
			else
				n++;

		return RESULT_SUCCESS;
	}

	type_index NECodeSet::find(const type_code source) const
	{
		return SuperClass::find(NECode(_type, source));
	}

	NECodeSet& NECodeSet::operator=(const NECodeSet& source)
	{
		if(this == &source) return *this;



		return *this;
	}

}