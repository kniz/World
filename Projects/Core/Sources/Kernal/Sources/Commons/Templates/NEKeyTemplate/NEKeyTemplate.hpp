//	---------------------------------------------------------------------------------
//	클래스명:	NEKeyTemplate<typename T, NEType::Type type>
//	설명	:	주어진 템플릿parameter T를 관리하는 클래스.
//				NEType::Type은 NEKeyTamplate의 타입이 된다. getType() 호출시 NEType::Type을 반환
//				한다.
//	관계	:	기반클래스.	NEKey
//	특성	:	외부에 공개되었다. 외부에서 상속 및 인스턴스 생성 가능하다.
//	알고리즘:	연산자 및 함수 호출시, operand의 타입을 확인후, 일치 할 경우 연산을 
//				수행한다.
//	사용방법:	public인 value를 바로 사용한다.
//	메모	:	
//	히스토리:	2011-06-05	이태훈	개발 완료
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../../../Modules/NEKeyTemplateBase/NEKeyTemplateBase.hpp"
#include "../../../Modules/NEString/NEString.hpp"
#include "../../../Modules/NEWString/NEWString.hpp"
#include "../../../Modules/NEBooleanSet/NEBooleanSet.hpp"
#include "../../../Modules/NEByteSet/NEByteSet.hpp"
#include "../../../Modules/NEUByteSet/NEUByteSet.hpp"
#include "../../../Modules/NEShortSet/NEShortSet.hpp"
#include "../../../Modules/NEUShortSet/NEUShortSet.hpp"
#include "../../../Modules/NEIntSet/NEIntSet.hpp"
#include "../../../Modules/NEUIntSet/NEUIntSet.hpp"
#include "../../../Modules/NEInt64Set/NEInt64Set.hpp"
#include "../../../Modules/NEFloatSet/NEFloatSet.hpp"
#include "../../../Modules/NEDoubleSet/NEDoubleSet.hpp"
#include "../../../Modules/NEModuleCodeSet/NEModuleCodeSet.hpp"
#include "../../../Modules/NENodeCodeSet/NENodeCodeSet.hpp"

namespace NE
{
	template <typename T, NEType::Type type>
	class NEKeyTemplate : public NEKeyTemplateBase
	{
	public:
		typedef NEKeyTemplate<T, type> ThisClass;
		typedef NEKeyTemplateBase SuperClass;
		typedef T Trait;

		//	생성자:
	public:
		NEKeyTemplate(const T& source = T(), const NETString& keyname = "");
		NEKeyTemplate(const NEKeyTemplate<T, type>& source);
		NEKeyTemplate(const NEKey& source);

		//	소멸자:
	public:
		virtual ~NEKeyTemplate();

		//	연산자 중첩:
	public:
		const NEKeyTemplate<T, type>& operator=(const NEKeyTemplate<T, type>& source);
		bool operator==(const NEKeyTemplate<T, type>& source) const;		
		bool operator!=(const NEKeyTemplate<T, type>& source) const;
		NEKeyTemplate<T, type> operator+(const NEKeyTemplate<T, type>& source) const;
		const NEKeyTemplate<T, type>& operator+=(const NEKeyTemplate<T, type>& source);
											 
		//	인터페이스:
		//		접근자:
	public:
		T& getValue();
		const T& getValue() const;
		
		//		상속:
		//			NEKey:
	public:
		virtual type_result assign(const NEKey& source);
		virtual type_result extend(const NEKey& source);
		virtual bool isEqualTo(const NEKey& source) const;
		virtual bool isLower(const NEKey& source) const;

		//			NEObject:
	public:
		virtual NEObject& clone() const;
		virtual void release(); 
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual	NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEType::Type getType() const;

		//	멤버변수:
	protected:
		T _value;
	};
}

#include "NEKeyTemplate.inl"