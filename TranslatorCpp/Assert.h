#pragma once

#ifdef DEBUG
	#define ASSERT(x) { if (!(x)) throw std::exception(#x);}
#else
	#define ASSERT(x) (__assume (x))
#endif