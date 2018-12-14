#pragma once

#include "Thing.hpp"
#include "Id.hpp"
#include "../binds/TStrong.inl"

namespace wrd
{
	class Block;
	class Node;

	class Instance : public Thing
	{	WRD_CLASS(Instance, Thing)
		//	Instance는 World에서 인스턴스 관리를 대신해준다. 여기서부터 bind가 가능하다.

	public:
		Instance();
		//	why was virtual copyconstructor defined with private accessor?:
		//		WorldFrx basically is based on class Node.
		//		So, if all classes returns TStrong<Instance> as a returntype of clone()
		//		user may needs to cast it to Node. inconvenient.
		//		however, if we declared this as a private member-function and 
		//		define clone() non-virtual function as public, we can return Node
		//		as a return-type of clone if it's subclass of Node.
		//
		//	in summary:
		//		clone()  : a wrapper for providing easy-to-use return type.
		//		_clone() : it's a really what cloning happens. subclasses will
		//		override it.
		TStrong<Instance> clone() const;
		ID getId() const;
		wcnt getSerial() const;
		const InstBlk& getBlock() const;
		wbool isHeap() const;
		TStrong<Node> toStrong();
		TStrong<const Node> toStrong() const;
		TWeak<Node> toWeak();
		TWeak<const Node> toWeak() const;

	private:
		virtual TStrong<Instance> _clone() const;

	private:
		Id _id;
	};
}
