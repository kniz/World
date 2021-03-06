#pragma once

#include "overload.hpp"

#define WRD_UNCONST_FUNC_2(type, funcCall) { \
        type* uncThis = const_cast<type*>(this); \
        return uncThis->funcCall; \
    }
#define WRD_UNCONST_FUNC_1(funcCall) WRD_UNCONST_FUNC_2(me, funcCall);
#define WRD_UNCONST_FUNC(...) WRD_OVERLOAD(WRD_UNCONST_FUNC, __VA_ARGS__)
