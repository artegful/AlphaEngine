#pragma once

#ifdef AL_DEBUG

	#ifdef AL_WINDOWS
		#define AL_DEBUG_BREAK() __debugbreak()
	#else
		#error "This platform is not supported"
	#endif	

#else
	#define AL_DEBUG_BREAK()
#endif

#define AL_EXPAND(x) x

#define AL_STRINGIFY(x) #x