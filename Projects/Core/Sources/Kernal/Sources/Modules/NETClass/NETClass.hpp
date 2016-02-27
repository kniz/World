//	---------------------------------------------------------------------------------
//	Name			:	NETClass
//	Comments		:	
//	Releationships	:
//	Charateristics	:	
//	Usage			:	
//	Memo			:	
//	Author			:	2016-02-13	kniz	Creations
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../NEClassBase/NEClassBase.hpp"
#include "define/ClassMacro.hpp"
#include <typeinfo>

namespace NE
{
	template <typename T>
	class NETClass : public NEClassBase
	{
		//	Declarations:
	public:
		typedef NETClass<T> This;
		typedef NEClassBase Super;
		typedef T Trait;
		typedef typename Trait::Super SuperTrait;
		typedef NETClass<SuperTrait> SuperClass;

		//	Constructors:
	public:
		NETClass();
		NETClass(const NETClass& source);

		//	Destructors:
	public:
		virtual ~NETClass();

		//	Interfaces:
		//		Virtuals:
	public:
		virtual const NETString& getName() const;
		virtual const NEClassBaseList& getSuperClasses() const;
		virtual const type_bool& isRegistered() const;
		virtual const NEClassBaseList& getSubClasses() const;
		virtual NEObject& instantiate() const;
		//			Inherited:
		//				NEObject:
	public:
		virtual NEObject& clone() const;

	public:
		const NEClassBase& getSuperClass() const;

		//	Statics:
	public:
		static const NEClassBaseList& getSubClassesStatically();
		static const NEClassBaseList& getSuperClassesStatically();
		static const NEString& getNameStatically();
		static const type_bool& isRegisteredStatically();
	};
}

#include "NETClass.inl"