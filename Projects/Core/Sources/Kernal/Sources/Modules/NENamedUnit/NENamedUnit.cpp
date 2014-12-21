#include "NENamedUnit.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NENamedUnit::NENamedUnit()
		: NEExecutableUnit(), 
		_namecode(NECodeType::NAME, true), _scriptcode(NECodeType::SCRIPT, true)// 상위 생성자
	{
		_scriptcode.create(1);
		_scriptcode.push(NE_HAS_NO_SCRIPTCODE);

		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NENamedUnit::NENamedUnit(type_code)
		: NEExecutableUnit(), 
		_namecode(NECodeType::NAME, true), _scriptcode(NECodeType::SCRIPT, true)// 상위 생성자
	{
		_scriptcode.create(1);
		_scriptcode.push(NE_HAS_NO_SCRIPTCODE);

		_release();		
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NENamedUnit::NENamedUnit(const NENamedUnit& source)
		: NEExecutableUnit(source), _namecode(source._namecode), _scriptcode(source._scriptcode)
	{	
		_assign(source);
		
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NENamedUnit::~NENamedUnit()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NENamedUnit::operator==(const NENamedUnit& source) const
	{
		if(this == &source) return true;
		if(NEExecutableUnit ::operator==(source) == false) return false;
		if(_namecode != source._namecode) return false;
		if(_scriptcode != source._scriptcode) return false;

		return true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NENamedUnit::operator!=(const NENamedUnit& source) const
	{
		return !(operator==(source));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NENamedUnit NE_DLL &NENamedUnit::operator=(const NENamedUnit& source)
	{
		NEExecutableUnit ::operator=(source);

		return _assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NENamedUnit::release()
	{
		NEExecutableUnit ::release();

		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileSaver NE_DLL &NENamedUnit::serialize(NEBinaryFileSaver& saver) const 
	{
		NEExecutableUnit::serialize(saver);

		return saver << _namecode << _scriptcode;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NENamedUnit::serialize(NEBinaryFileLoader& loader)
	{
		NEExecutableUnit ::serialize(loader);

		return loader >> _namecode >> _scriptcode;
	}



	type_result NE_DLL NENamedUnit::isValid() const
	{
		if(_scriptcode[0].getCode() < NE_HAS_NO_SCRIPTCODE) return RESULT_TYPE_ERROR;
		if(_namecode[0].getCode() < 0) return RESULT_TYPE_ERROR;
		
		return RESULT_SUCCESS;
	}
	
	
	
	
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NENamedUnit::_release()
	{
		/*
			scriptcode값은 변경하면 안된다.
		*/
		_namecode.create(1);
		_namecode.push(0);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NENamedUnit& NENamedUnit::_assign(const NENamedUnit& source)
	{
		//	pre:
		if(this == &source) return *this;

		_scriptcode = source._scriptcode;
		_namecode = source._namecode;

		return *this;
	}

	const NECodeSet NE_DLL &NENamedUnit::getCodeSet(const NECodeType& type) const
	{
		switch(type.getCodeType())
		{
		case NECodeType::NAME:		return _scriptcode;
		case NECodeType::SCRIPT:	return _scriptcode;
		}

		NECodeSet* nullpointer = 0x00;
		return *nullpointer;
	}

	type_result NENamedUnit::setCodeSet(const NECodeSet& source)
	{
		if(source.getLength() <= 0) return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION | RESULT_WRONG_BOUNDARY;
		const NECode& code = source[0];

		switch(code.getCodeType())
		{
		case NECodeType::NAME:
			_namecode.pop();
			_namecode.push(code);
			return RESULT_SUCCESS;
		}

		return RESULT_TYPE_WARNING | RESULT_INVALID_DATA;
	}

}
