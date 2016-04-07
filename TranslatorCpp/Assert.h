#pragma once

#ifdef DEBUG
	#define Assert(x) { if (!(x)) throw std::exception(#x);}
#else
	#define __assume (x)
#endif