#pragma once
#include <assert.h>

#ifdef _DEBUG
	#define ASSERT_WITH_MSG(x, msg) { if (!(x)) { _wassert(_CRT_WIDE(msg), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)); throw -1; } }
#else
	#define ASSERT_WITH_MSG(x,msg) (__assume (x))
#endif

#define ASSERT(x) ASSERT_WITH_MSG(x, #x)

#define FAIL(x) ASSERT_WITH_MSG(false, x)

