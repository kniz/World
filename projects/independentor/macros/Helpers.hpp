#pragma once

//		helpers:
#define WRD_VOID()
#define WRD_SPACE WRD_VOID() WRD_VOID()
#define WRD_CONSUME_ARGS(...)
#define WRD_UNWRAP(...) __VA_ARGS__

#define WRD_UNCONST_0()				WRD_UNCONST_1(unconst)
#define WRD_UNCONST_1(value)		WRD_UNCONST_2(This, value)
#define WRD_UNCONST_2(type, value)	WRD_UNWRAP(type)* value = const_cast<WRD_UNWRAP(type)*>(this);
#define WRD_UNCONST(...)			WRD_OVERLOAD(WRD_UNCONST, __VA_ARGS__)

#define WRD_DELAY(x) x WRD_VOID()

//	why delaying comma expressoin?:
//		it can causes delimiter issue on expanding macros for template parameters.
#define _COMMA() ,
#define WRD_COMMA() WRD_DELAY(_COMMA)()
