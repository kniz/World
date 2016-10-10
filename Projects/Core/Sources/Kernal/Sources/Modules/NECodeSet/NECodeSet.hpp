//	---------------------------------------------------------------------------------
//	클래스명:	NECodeSet
//	설명	:	복수의 모듈 스크립트의 코드를 serialize 하기 위해서 존재하는 클래스다.
//				모듈스크립트는 다른 코드와 달리 노드엔진이 구동 직전에 fetch되는 모듈
//				의 인덱스로 결정된다. 
//				다시 말하면 pc 환경이 같다고 해도 모듈의 스크립트 코드가 바뀔 수 있으므로
//				이를 다루는 것도 까다로우며, serialize도 단순히 int형을 저장하는 방식이
//				아니라 식별자 전체를 저장해야 한다.
//	관계	:	기반클래스.	NEIntSet
//	특성	:	serialize시, NEModule의 식별자를 저장함으로써, 모듈의 독립성을 보장한다.
//	사용방법:	NETVector를 참고하라.
//	메모	:	
//	히스토리:	2011-07-19	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../NECode/NECode.hpp"
#include "../NETVector/NETVector.hpp"
#include "../NETDeeper/NETDeeper.hpp"

namespace NE
{
	template
	class NE_DLL NETDeeper<NETVector<NECode>>;
	class NE_DLL NECodeSet : public NETDeeper<NETVector<NECode>>
	{
		typedef NETDeeper<NETVector<NECode>> _Super;
		
		NE_DECLARE_CLASS(NECodeSet, _Super);

		//	생성자:
	public:
		NECodeSet();
		NECodeSet(type_count size, const NECodeType& initial_type);
		NECodeSet(const NECode& single_code);
		NECodeSet(const NECodeType& initial_type);
		NECodeSet(const This& source);

		//	소멸자:
	public:
		virtual ~NECodeSet();

		//	연산자 오버로딩:
		//		왜 다른 operator를 정의하지 않는가?
		//			operator=는 컴파일러가 상위클래스를 호출하는 함수를 작성한다
		//			(리턴값이 하위클래스)
		//			operator==와 같은 기타 함수는 상위클래스를 상속받는다 (리턴
		//			값이 상위클래스)
		//			때문에 멤버변수가 존재하지 않는 Stub 연산자 오버로딩 함수라
		//			면 상위클래스의 함수를 상속할 수 있다.
		//			따라서 리턴값이 상위클래스로 나오게 되는 경우에만, Stub의 형
		//			태로 연산자 오버로딩 하게된다.
	public:
		This& operator=(const This& source);
		This& operator+=(const This& source);
		This operator+(const This& source) const;

	public:
		const NECodeType& getCodeType() const;
		NECodeType& getCodeType();

		//	인터페이스:
		//		상속:
		//			NETVector:
	public:
		using Super::setElement;
		virtual type_result setElement(type_index index, const NECode* const source);
		using Super::insert;
		virtual type_index insert(type_index index, const NECode* const source);
		//			NEObject:
	public:
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	public:
		type_count removeDuplicated();

	private:
		This& _assign(const This& source);
		type_bool _isElementDuplicated(const NECode& new_one) const;

	private:
		NECodeType _type;		
	};
}