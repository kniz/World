#include "NEUnit.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEUnit::NEUnit()
		: NEObject(), _id(NE_HAS_NO_ID)
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEUnit::NEUnit(const NEUnit& source)
		: NEObject(source), _id(NE_HAS_NO_ID)
	{
		_assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEUnit::~NEUnit()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEUnit NE_DLL &NEUnit::operator=(const NEUnit& source) 
	{
		return _assign(source);		
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEUnit::operator==(const NEUnit& source) const 
	{
		if(this == &source) return true;
		if(_id != source._id) return false;

		return true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEUnit::operator!=(const NEUnit& source) const 
	{
		return !(operator==(source));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_id NE_DLL NEUnit::getId() const
	{
		return _id;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEUnit::release() 
	{
		return _release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileSaver NE_DLL &NEUnit::serialize(NEBinaryFileSaver& saver) const 
	{
		return saver << _id;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NEUnit::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _id;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEUnit::_release()
	{
		/*
			참조: _id는 NENamedUnit::_scriptcode와 동일한 정책을 갖는다.
			한번 부여받으면, 외부에서 변경할 수 없으며(자신의 소유자 객체는 예외일 
			수 있음) 부여받은 정보는 다른 객체로 복사/전이 되지 않는다.
			초기화 및 해제될 수 도 없다.
		*/
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEUnit& NEUnit::_assign(const NEUnit& source)
	{
		if(this == &source) return *this;

		/*
			참조: _id는 NENamedUnit::_scriptcode와 동일한 정책을 갖는다.
			한번 부여받으면, 외부에서 변경할 수 없으며(자신의 소유자 객체는 예외일 
			수 있음) 부여받은 정보는 다른 객체로 복사/전이 되지 않는다.
			초기화 및 해제될 수 도 없다.
		*/

		return *this;
	}
}