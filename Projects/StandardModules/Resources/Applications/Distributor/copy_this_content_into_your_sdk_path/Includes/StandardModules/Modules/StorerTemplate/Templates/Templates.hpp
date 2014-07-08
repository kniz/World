#pragma once

#include "../StorerTemplate.hpp"

namespace NE
{
	namespace BooleanStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("BooleanStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("BooleanStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("BooleanStorer),
#endif
				_DEVELOPER[]	= _T("haku"),
				_VERSION[]		= _T("0.0.1a"),
				_COMMENT[]		= _T("0번키에 Boolean을 저장합니다. 아무런 동작도 하지 않습니다"),
				_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEBooleanKey, BooleanStorerNameSpace::_NAME, BooleanStorerNameSpace::_DEVELOPER, 1, BooleanStorerNameSpace::_VERSION, BooleanStorerNameSpace::_COMMENT, BooleanStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEBooleanKey, BooleanStorerNameSpace::_NAME, BooleanStorerNameSpace::_DEVELOPER, 1, BooleanStorerNameSpace::_VERSION, BooleanStorerNameSpace::_COMMENT, BooleanStorerNameSpace::_DATE, 0> BooleanStorer;


	namespace CharStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("CharStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("CharStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("CharStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 Char을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NECharKey, CharStorerNameSpace::_NAME, CharStorerNameSpace::_DEVELOPER, 1, CharStorerNameSpace::_VERSION, CharStorerNameSpace::_COMMENT, CharStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NECharKey, CharStorerNameSpace::_NAME, CharStorerNameSpace::_DEVELOPER, 1, CharStorerNameSpace::_VERSION, CharStorerNameSpace::_COMMENT, CharStorerNameSpace::_DATE, 0> CharStorer;


	namespace WCharStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("WCharStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("WCharStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("WCharStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 WChar을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEWCharKey, WCharStorerNameSpace::_NAME, WCharStorerNameSpace::_DEVELOPER, 1, WCharStorerNameSpace::_VERSION, WCharStorerNameSpace::_COMMENT, WCharStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEWCharKey, WCharStorerNameSpace::_NAME, WCharStorerNameSpace::_DEVELOPER, 1, WCharStorerNameSpace::_VERSION, WCharStorerNameSpace::_COMMENT, WCharStorerNameSpace::_DATE, 0> WCharStorer;


	namespace ByteStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("ByteStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("ByteStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("ByteStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 Byte을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEByteKey, ByteStorerNameSpace::_NAME, ByteStorerNameSpace::_DEVELOPER, 1, ByteStorerNameSpace::_VERSION, ByteStorerNameSpace::_COMMENT, ByteStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEByteKey, ByteStorerNameSpace::_NAME, ByteStorerNameSpace::_DEVELOPER, 1, ByteStorerNameSpace::_VERSION, ByteStorerNameSpace::_COMMENT, ByteStorerNameSpace::_DATE, 0> ByteStorer;


	namespace ShortStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("ShortStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("ShortStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("ShortStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 Short을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEShortKey, ShortStorerNameSpace::_NAME, ShortStorerNameSpace::_DEVELOPER, 1, ShortStorerNameSpace::_VERSION, ShortStorerNameSpace::_COMMENT, ShortStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEShortKey, ShortStorerNameSpace::_NAME, ShortStorerNameSpace::_DEVELOPER, 1, ShortStorerNameSpace::_VERSION, ShortStorerNameSpace::_COMMENT, ShortStorerNameSpace::_DATE, 0> ShortStorer;


	namespace UShortStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("UShortStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("UShortStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("UShortStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 UShort을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEUShortKey, UShortStorerNameSpace::_NAME, UShortStorerNameSpace::_DEVELOPER, 1, UShortStorerNameSpace::_VERSION, UShortStorerNameSpace::_COMMENT, UShortStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEUShortKey, UShortStorerNameSpace::_NAME, UShortStorerNameSpace::_DEVELOPER, 1, UShortStorerNameSpace::_VERSION, UShortStorerNameSpace::_COMMENT, UShortStorerNameSpace::_DATE, 0> UShortStorer;


	namespace IntStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("IntStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("IntStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("IntStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 Int을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEIntKey, IntStorerNameSpace::_NAME, IntStorerNameSpace::_DEVELOPER, 1, IntStorerNameSpace::_VERSION, IntStorerNameSpace::_COMMENT, IntStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEIntKey, IntStorerNameSpace::_NAME, IntStorerNameSpace::_DEVELOPER, 1, IntStorerNameSpace::_VERSION, IntStorerNameSpace::_COMMENT, IntStorerNameSpace::_DATE, 0> IntStorer;


	namespace UIntStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("UIntStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("UIntStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("UIntStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 UInt을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEUIntKey, UIntStorerNameSpace::_NAME, UIntStorerNameSpace::_DEVELOPER, 1, UIntStorerNameSpace::_VERSION, UIntStorerNameSpace::_COMMENT, UIntStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEUIntKey, UIntStorerNameSpace::_NAME, UIntStorerNameSpace::_DEVELOPER, 1, UIntStorerNameSpace::_VERSION, UIntStorerNameSpace::_COMMENT, UIntStorerNameSpace::_DATE, 0> UIntStorer;


	namespace UByteStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("UByteStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("UByteStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("UByteStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 UByte을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEUByteKey, UByteStorerNameSpace::_NAME, UByteStorerNameSpace::_DEVELOPER, 1, UByteStorerNameSpace::_VERSION, UByteStorerNameSpace::_COMMENT, UByteStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEUByteKey, UByteStorerNameSpace::_NAME, UByteStorerNameSpace::_DEVELOPER, 1, UByteStorerNameSpace::_VERSION, UByteStorerNameSpace::_COMMENT, UByteStorerNameSpace::_DATE, 0> UByteStorer;


	namespace NodeIdStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("NodeIdStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("NodeIdStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("NodeIdStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 NodeId을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NENodeIdKey, NodeIdStorerNameSpace::_NAME, NodeIdStorerNameSpace::_DEVELOPER, 1, NodeIdStorerNameSpace::_VERSION, NodeIdStorerNameSpace::_COMMENT, NodeIdStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NENodeIdKey, NodeIdStorerNameSpace::_NAME, NodeIdStorerNameSpace::_DEVELOPER, 1, NodeIdStorerNameSpace::_VERSION, NodeIdStorerNameSpace::_COMMENT, NodeIdStorerNameSpace::_DATE, 0> NodeIdStorer;


	namespace FloatStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("FloatStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("FloatStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("FloatStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 Float을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEFloatKey, FloatStorerNameSpace::_NAME, FloatStorerNameSpace::_DEVELOPER, 1, FloatStorerNameSpace::_VERSION, FloatStorerNameSpace::_COMMENT, FloatStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEFloatKey, FloatStorerNameSpace::_NAME, FloatStorerNameSpace::_DEVELOPER, 1, FloatStorerNameSpace::_VERSION, FloatStorerNameSpace::_COMMENT, FloatStorerNameSpace::_DATE, 0> FloatStorer;


	namespace DoubleStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("DoubleStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("DoubleStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("DoubleStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 Double을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEDoubleKey, DoubleStorerNameSpace::_NAME, DoubleStorerNameSpace::_DEVELOPER, 1, DoubleStorerNameSpace::_VERSION, DoubleStorerNameSpace::_COMMENT, DoubleStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEDoubleKey, DoubleStorerNameSpace::_NAME, DoubleStorerNameSpace::_DEVELOPER, 1, DoubleStorerNameSpace::_VERSION, DoubleStorerNameSpace::_COMMENT, DoubleStorerNameSpace::_DATE, 0> DoubleStorer;


	namespace StringStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("StringStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("StringStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("StringStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 String을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEStringKey, StringStorerNameSpace::_NAME, StringStorerNameSpace::_DEVELOPER, 1, StringStorerNameSpace::_VERSION, StringStorerNameSpace::_COMMENT, StringStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEStringKey, StringStorerNameSpace::_NAME, StringStorerNameSpace::_DEVELOPER, 1, StringStorerNameSpace::_VERSION, StringStorerNameSpace::_COMMENT, StringStorerNameSpace::_DATE, 0> StringStorer;


	namespace WStringStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("WStringStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("WStringStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("WStringStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 WString을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEWStringKey, WStringStorerNameSpace::_NAME, WStringStorerNameSpace::_DEVELOPER, 1, WStringStorerNameSpace::_VERSION, WStringStorerNameSpace::_COMMENT, WStringStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEWStringKey, WStringStorerNameSpace::_NAME, WStringStorerNameSpace::_DEVELOPER, 1, WStringStorerNameSpace::_VERSION, WStringStorerNameSpace::_COMMENT, WStringStorerNameSpace::_DATE, 0> WStringStorer;


	namespace Int64StorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("Int64Storer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("Int64Storer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("Int64Storer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 Int64을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEInt64Key, Int64StorerNameSpace::_NAME, Int64StorerNameSpace::_DEVELOPER, 1, Int64StorerNameSpace::_VERSION, Int64StorerNameSpace::_COMMENT, Int64StorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEInt64Key, Int64StorerNameSpace::_NAME, Int64StorerNameSpace::_DEVELOPER, 1, Int64StorerNameSpace::_VERSION, Int64StorerNameSpace::_COMMENT, Int64StorerNameSpace::_DATE, 0> Int64Storer;


	namespace NodeSetStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("NodeSetStorerStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("NodeSetStorerStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("NodeSetStorerStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 NodeSetStorer을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEManagedNodeSetKey, NodeSetStorerNameSpace::_NAME, NodeSetStorerNameSpace::_DEVELOPER, 1, NodeSetStorerNameSpace::_VERSION, NodeSetStorerNameSpace::_COMMENT, NodeSetStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEManagedNodeSetKey, NodeSetStorerNameSpace::_NAME, NodeSetStorerNameSpace::_DEVELOPER, 1, NodeSetStorerNameSpace::_VERSION, NodeSetStorerNameSpace::_COMMENT, NodeSetStorerNameSpace::_DATE, 0> NodeSetStorer;


	namespace ModuleSetStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("ModuleSetStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("ModuleSetStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("ModuleSetStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 ModuleSet을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEManagedModuleSetKey, ModuleSetStorerNameSpace::_NAME, ModuleSetStorerNameSpace::_DEVELOPER, 1, ModuleSetStorerNameSpace::_VERSION, ModuleSetStorerNameSpace::_COMMENT, ModuleSetStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEManagedModuleSetKey, ModuleSetStorerNameSpace::_NAME, ModuleSetStorerNameSpace::_DEVELOPER, 1, ModuleSetStorerNameSpace::_VERSION, ModuleSetStorerNameSpace::_COMMENT, ModuleSetStorerNameSpace::_DATE, 0> ModuleSetStorer;


	namespace BooleanSetStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("BooleanSetStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("BooleanSetStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("BooleanSetStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 BooleanSet을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEBooleanSetKey, BooleanSetStorerNameSpace::_NAME, BooleanSetStorerNameSpace::_DEVELOPER, 1, BooleanSetStorerNameSpace::_VERSION, BooleanSetStorerNameSpace::_COMMENT, BooleanSetStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEBooleanSetKey, BooleanSetStorerNameSpace::_NAME, BooleanSetStorerNameSpace::_DEVELOPER, 1, BooleanSetStorerNameSpace::_VERSION, BooleanSetStorerNameSpace::_COMMENT, BooleanSetStorerNameSpace::_DATE, 0> BooleanSetStorer;


	namespace ByteSetStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("ByteSetStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("ByteSetStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("ByteSetStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 ByteSet을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEByteSetKey, ByteSetStorerNameSpace::_NAME, ByteSetStorerNameSpace::_DEVELOPER, 1, ByteSetStorerNameSpace::_VERSION, ByteSetStorerNameSpace::_COMMENT, ByteSetStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEByteSetKey, ByteSetStorerNameSpace::_NAME, ByteSetStorerNameSpace::_DEVELOPER, 1, ByteSetStorerNameSpace::_VERSION, ByteSetStorerNameSpace::_COMMENT, ByteSetStorerNameSpace::_DATE, 0> ByteSetStorer;


	namespace UByteSetStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("UByteSetStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("UByteSetStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("UByteSetStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 UByteSet을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEUByteSetKey, UByteSetStorerNameSpace::_NAME, UByteSetStorerNameSpace::_DEVELOPER, 1, UByteSetStorerNameSpace::_VERSION, UByteSetStorerNameSpace::_COMMENT, UByteSetStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEUByteSetKey, UByteSetStorerNameSpace::_NAME, UByteSetStorerNameSpace::_DEVELOPER, 1, UByteSetStorerNameSpace::_VERSION, UByteSetStorerNameSpace::_COMMENT, UByteSetStorerNameSpace::_DATE, 0> UByteSetStorer;


	namespace ShortSetStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("ShortSetStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("ShortSetStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("ShortSetStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 ShortSet을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEShortSetKey, ShortSetStorerNameSpace::_NAME, ShortSetStorerNameSpace::_DEVELOPER, 1, ShortSetStorerNameSpace::_VERSION, ShortSetStorerNameSpace::_COMMENT, ShortSetStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEShortSetKey, ShortSetStorerNameSpace::_NAME, ShortSetStorerNameSpace::_DEVELOPER, 1, ShortSetStorerNameSpace::_VERSION, ShortSetStorerNameSpace::_COMMENT, ShortSetStorerNameSpace::_DATE, 0> ShortSetStorer;


	namespace UShortSetStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("UShortSetStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("UShortSetStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("UShortSetStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 UShortSet을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEUShortSetKey, UShortSetStorerNameSpace::_NAME, UShortSetStorerNameSpace::_DEVELOPER, 1, UShortSetStorerNameSpace::_VERSION, UShortSetStorerNameSpace::_COMMENT, UShortSetStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEUShortSetKey, UShortSetStorerNameSpace::_NAME, UShortSetStorerNameSpace::_DEVELOPER, 1, UShortSetStorerNameSpace::_VERSION, UShortSetStorerNameSpace::_COMMENT, UShortSetStorerNameSpace::_DATE, 0> UShortSetStorer;
	
		
	namespace IntSetStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("IntSetStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("IntSetStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("IntSetStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 IntSet을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEIntSetKey, IntSetStorerNameSpace::_NAME, IntSetStorerNameSpace::_DEVELOPER, 1, IntSetStorerNameSpace::_VERSION, IntSetStorerNameSpace::_COMMENT, IntSetStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEIntSetKey, IntSetStorerNameSpace::_NAME, IntSetStorerNameSpace::_DEVELOPER, 1, IntSetStorerNameSpace::_VERSION, IntSetStorerNameSpace::_COMMENT, IntSetStorerNameSpace::_DATE, 0> IntSetStorer;


	namespace UIntSetStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("UIntSetStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("UIntSetStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("UIntSetStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 UIntSet을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEUIntSetKey, UIntSetStorerNameSpace::_NAME, UIntSetStorerNameSpace::_DEVELOPER, 1, UIntSetStorerNameSpace::_VERSION, UIntSetStorerNameSpace::_COMMENT, UIntSetStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEUIntSetKey, UIntSetStorerNameSpace::_NAME, UIntSetStorerNameSpace::_DEVELOPER, 1, UIntSetStorerNameSpace::_VERSION, UIntSetStorerNameSpace::_COMMENT, UIntSetStorerNameSpace::_DATE, 0> UIntSetStorer;


	namespace NodeIdSetStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("NodeIdSetStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("NodeIdSetStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("NodeIdSetStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 NodeIdSet을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NENodeIdSetKey, NodeIdSetStorerNameSpace::_NAME, NodeIdSetStorerNameSpace::_DEVELOPER, 1, NodeIdSetStorerNameSpace::_VERSION, NodeIdSetStorerNameSpace::_COMMENT, NodeIdSetStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NENodeIdSetKey, NodeIdSetStorerNameSpace::_NAME, NodeIdSetStorerNameSpace::_DEVELOPER, 1, NodeIdSetStorerNameSpace::_VERSION, NodeIdSetStorerNameSpace::_COMMENT, NodeIdSetStorerNameSpace::_DATE, 0> NodeIdSetStorer;


	namespace FloatSetStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("FloatSetStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("FloatSetStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("FloatSetStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 FloatSet을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEFloatSetKey, FloatSetStorerNameSpace::_NAME, FloatSetStorerNameSpace::_DEVELOPER, 1, FloatSetStorerNameSpace::_VERSION, FloatSetStorerNameSpace::_COMMENT, FloatSetStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEFloatSetKey, FloatSetStorerNameSpace::_NAME, FloatSetStorerNameSpace::_DEVELOPER, 1, FloatSetStorerNameSpace::_VERSION, FloatSetStorerNameSpace::_COMMENT, FloatSetStorerNameSpace::_DATE, 0> FloatSetStorer;


	namespace DoubleSetStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("DoubleSetStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("DoubleSetStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("DoubleSetStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 DoubleSet을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEDoubleSetKey, DoubleSetStorerNameSpace::_NAME, DoubleSetStorerNameSpace::_DEVELOPER, 1, DoubleSetStorerNameSpace::_VERSION, DoubleSetStorerNameSpace::_COMMENT, DoubleSetStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEDoubleSetKey, DoubleSetStorerNameSpace::_NAME, DoubleSetStorerNameSpace::_DEVELOPER, 1, DoubleSetStorerNameSpace::_VERSION, DoubleSetStorerNameSpace::_COMMENT, DoubleSetStorerNameSpace::_DATE, 0> DoubleSetStorer;


	namespace StringSetStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("StringSetStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("StringSetStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("StringSetStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 StringSet을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEStringSetKey, StringSetStorerNameSpace::_NAME, StringSetStorerNameSpace::_DEVELOPER, 1, StringSetStorerNameSpace::_VERSION, StringSetStorerNameSpace::_COMMENT, StringSetStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEStringSetKey, StringSetStorerNameSpace::_NAME, StringSetStorerNameSpace::_DEVELOPER, 1, StringSetStorerNameSpace::_VERSION, StringSetStorerNameSpace::_COMMENT, StringSetStorerNameSpace::_DATE, 0> StringSetStorer;


	namespace WStringSetStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("WStringSetStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("WStringSetStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("WStringSetStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 WStringSet을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEWStringSetKey, WStringSetStorerNameSpace::_NAME, WStringSetStorerNameSpace::_DEVELOPER, 1, WStringSetStorerNameSpace::_VERSION, WStringSetStorerNameSpace::_COMMENT, WStringSetStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEWStringSetKey, WStringSetStorerNameSpace::_NAME, WStringSetStorerNameSpace::_DEVELOPER, 1, WStringSetStorerNameSpace::_VERSION, WStringSetStorerNameSpace::_COMMENT, WStringSetStorerNameSpace::_DATE, 0> WStringSetStorer;


	namespace Int64SetStorerNameSpace
	{
#ifdef DEVELOPER
#	ifdef _DEBUG
		TCHAR	_NAME[]			= _T("Int64SetStorer.dev.dbg"),	
#	else
		TCHAR	_NAME[]			= _T("Int64SetStorer.dev"),
#	endif	
#else
		TCHAR	_NAME[]			= _T("Int64SetStorer),
#endif
			_DEVELOPER[]	= _T("haku"),
			_VERSION[]		= _T("0.0.1a"),
			_COMMENT[]		= _T("0번키에 Int64Set을 저장합니다. 아무런 동작도 하지 않습니다"),
			_DATE[]			= _T("2012-04-14");
	}

	template
	class NE_DLL StorerTemplate <NEInt64SetKey, Int64SetStorerNameSpace::_NAME, Int64SetStorerNameSpace::_DEVELOPER, 1, Int64SetStorerNameSpace::_VERSION, Int64SetStorerNameSpace::_COMMENT, Int64SetStorerNameSpace::_DATE, 0>;
	typedef StorerTemplate <NEInt64SetKey, Int64SetStorerNameSpace::_NAME, Int64SetStorerNameSpace::_DEVELOPER, 1, Int64SetStorerNameSpace::_VERSION, Int64SetStorerNameSpace::_COMMENT, Int64SetStorerNameSpace::_DATE, 0> Int64SetStorer;	



#ifdef _UNICODE
	typedef WStringStorer		TStringStorer;
	typedef WStringSetStorer	TStringSetStorer;
#else
	typedef StringStorer		TStringStorer;
	typedef StringSetStorer		TStringSetStorer;
#endif
}