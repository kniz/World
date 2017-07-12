///	@file	NE_OVERLOADER.hpp
///	@brief	Make it possible to provide overloaded macro.
///	@remark	These are codes inspired from Boost library. added the PATCH for VS.
#pragma once

#include "Concaterator.hpp"
#include "ArgumentCounter.hpp"

///	Implementing Macro Overloding:
///		by count of given arguments, let compiler determine which macro should works.
///		code inspired by Boost library, patched for visual studio's weird varadic macro.
//		branch to macro that would be expanded by its argument count:
//
//		usage:
//			//	define macro:
//			#define MyMacro_1(x) (x)+5
//			#define MyMacro_2(x, y) (x)+(y)
//			#define MyMacro(...)	NE_MACRO_OVERLOADER(MyMacro, __VA_ARGS__)
//
//			//	using:
//			cout << MyMacro(5) << ", " << MyMacro(3, 5) << "\n";
//
//		output:
//			10, 8
#define _OVERLOADER(macro_name, argcount)	NE_MACRO_CONCATERATOR(macro_name, argcount)
#define NE_MACRO_OVERLOADER(macro_name, ...)	\
	_OVERLOADER(macro_name, NE_MACRO_CONCATERATOR(_, NE_MACRO_ARGCOUNT(__VA_ARGS__)))(__VA_ARGS__)