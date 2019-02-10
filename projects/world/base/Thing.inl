#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
	class Res;
	class Node;
	class Class;
	class Visitor;
	class Instance;
	class Container;
	template <typename T> class TStrong;
	typedef TStrong<Node> Strong;
	typedef TStrong<const Node> CStrong;
	template <typename T> class TWeak;
	typedef TWeak<Node> Weak;
	typedef TWeak<const Node> CWeak;

	///	Thing은 World의 최상위 객체
	class Thing
	{	WRD_CLASS_DECL(Thing)
		template <typename T, typename S> friend class TVisitation; //	_tour를 위한 것이다.
	public:
		virtual ~Thing();

	public:
		virtual const Class& getSuper() const;
		virtual Res& release() = 0;
		wbool isNull() const;
		wbool isExist() const;
		virtual wbool isSuper(const Class& it) const;
		wbool isSuper(const Thing& it) const;
		template <typename T> wbool isSuper() const;
		wbool isSub(const Thing& it) const;
		wbool isSub(const Class& it) const;
		template <typename T> wbool isSub() const;
		//	to는 명시적캐스팅이다. 
		//		사용자의 개입이 가능한 유일한 캐스팅의 1 종류이며, 
		//		A타입에 대한 명시적캐스팅은 어떠한 타입이 나올지 제한되지 않는다.
		//		A클래스.to()는 전혀다른 B객체가 나올 수도 있다.
		virtual Strong to(const Class& cls);
		CStrong to(const Class& cls) const;
		template <typename T> Strong to();
		template <typename T> CStrong to() const;
		//	Casting:
		//		World의 캐스팅은 다음으로 구분된다.
		//			1) native 다운캐스팅:	thing::down<T>(), Thing::down(Class&)
		//			[invisible]	native에서 편의를 위해 제공되는 함수다.
		//
		//			2) 명시적캐스팅:	Thing::to(Class&), Thing::to<T>()
		//			[visible] 명시적 캐스팅은 총 3가지로 이루어져있다.
		//				1. 다운/업캐스팅(Thing::down(Class&)를 사용한다)
		//				2. 묵시적 캐스팅 파이프
		//				3. 생성자를 통한 캐스팅: cls가 가지고 있는 생성자를 통해서,
		//				변환이 가능한지 확인하고, 가능하다면 이걸 이용한다.
		//				속도가 매우 오래걸린다.
		//
		//			3) 묵시적캐스팅:	2번과 동일
		//			[invisible, automatically] 명시적 캐스팅은 속도를 많이 필요로 하기,
		//			때문에 매 함수 호출시 인자마다 호출될 캐스팅으로는 적합하지 않다.
		//			묵시적 캐스팅은 pretype에 대해서 빠르게 동작하는 캐스팅을 의미하며,
		//			사용자가 캐스팅하는 주체가 pretype일 경우에 한해서 자동으로 묵시적
		//			캐스팅이 이루어진다.
		//				예)	void print(int a)
		//				MyClass cls;
		//				print(cls); // err. MyClass -> int는 묵시적캐스팅이 아니다.
		//				print(3.5); // ok. float은 pretype이므로 묵시적 캐스팅이 동작한다.
		//			묵시적 캐스팅은 각 pretype들이 to함수를 override해서 자신의 간이 캐스팅
		//			테이블을 끼워놓음으로써 해결한다. 중간에 msg를 만들어 보낼 필요가 없으므로
		//			속도가 더 빨라진다.
		//			묵시적 캐스팅은 컴파일러의 함수 디덕션과 NativeBidging 2곳에서 사용된다.

		//	구체클래스로 캐스트한다. dynamic_cast와 동급이다.
		//	invisible이다.
		template <typename T> T& down() { return (T&) _down(T::getClassStatic()); }
		template <typename T> const T& down() const { return (T&) _down(T::getClassStatic()); }
		virtual Thing& _down(const Class& cls);
		const Thing& _down(const Class& cls) const;
		//	가상할당자이다. 할당연산자는 virtual이 안되기 때문에 제대로 할당을 하고 싶다면 항상 구체타입을 알고 있어야만 한다.
		virtual Res& assign(const Thing& it);

	protected:
		//	Visitor에 의해서 하위 구성요소(ownee)들을 어떻게 순회시킬지를 정한다.
		virtual Res& _tour(Visitor& visitor) const;
		virtual Res& _tour(Visitor& visitor);
	};
}
