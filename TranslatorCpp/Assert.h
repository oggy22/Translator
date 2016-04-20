#pragma once

#ifdef _DEBUG
	#define ASSERT(x) { if (!(x)) throw std::exception(#x);}
	#define ASSERT_WITH_MSG(x,msg) { if (!(x)) throw std::exception(msg);}
#else
	#define ASSERT(x) (__assume (x))
	#define ASSERT_WITH_MSG(x,msg) (__assume (x))
#endif