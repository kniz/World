//	---------------------------------------------------------------------------------
//	클래스명:	NEUnit
//	설명	:	아이디(제조번호)가 존재한다.
//				serialize 이전과 이후에 관계없이 항상 유니크한 객체 자체를 구분할 수 있게 해준다.
//				이와 비슷하게 동작하는 것으로 주소값이 존재하나, 이는 매번 runtime마다 변경되므로,
//				id와는 다르다.
//				바인딩
//	관계	:	기반 클래스.	NEObject
//	특성	:	추상클래스
//	알고리즘:	
//	사용방법:	execute()로 클래스가 담당하고 있는 메인 기능을 실행시킨다.
//				enable(), disable()로 인터페이스의 기능을 ON / OFF 할 수 있다.
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	2011-06-05	이태훈	개발 완료.
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../NEObject/NEObject.hpp"

namespace NE
{
	class NE_DLL NEUnit : public NEObject
	{
		//	프렌드:
	public:
		friend class NEIndexedKeySet;
		friend class NEIndexedModuleSet;
		friend class NEIndexedNodeSet;

		//	생성자:
	public:
		NEUnit();
		NEUnit(const NEUnit& source);

		//	소멸자:
	public:
		virtual ~NEUnit();

		//	연산자 중첩:
	public:
		const NEUnit& operator=(const NEUnit& source);
		bool operator==(const NEUnit& source) const;
		bool operator!=(const NEUnit& source) const;

		//	접근자:
	public:
		type_id getId() const;

		//	인터페이스:
		//		상속:
		//			NEObject:
	public:
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

		//	내부함수:
	private:
		void _release();
		const NEUnit& _assign(const NEUnit& source);

		//	멤버변수:
	private:
		type_id _id;
	};

}