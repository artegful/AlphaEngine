#pragma once

#ifdef AL_ASSERTS

	#include <filesystem>

	#define AL_ASSERT_IMPL(type, check, message, ...) { if(!(check)) { AL##type##ERROR(message, __VA_ARGS__); AL_DEBUG_BREAK(); } }

	#define AL_ASSERT_WITH_MESSAGE_IMPL(type, check, ...)  AL_ASSERT_IMPL(type, check, "Assertion '", AL_STRINGIFY(check), "' at ", std::filesystem::path(__FILE__).filename().string(), ":", __LINE__, " failed with message: ", __VA_ARGS__)
	#define AL_ASSERT_WITHOUT_MESSAGE_IMPL(type, check, ...)  AL_ASSERT_IMPL(type, check, "Assertion '", AL_STRINGIFY(check), "' at ", std::filesystem::path(__FILE__).filename().string(), ":", __LINE__, " failed")

	#define AL_CHOOSE_MACRO_NAME(arg1, arg2, macro, ...) macro

	#define AL_CHOOSE_MACRO(...) AL_EXPAND( AL_CHOOSE_MACRO_NAME(__VA_ARGS__, AL_ASSERT_WITH_MESSAGE_IMPL, AL_ASSERT_WITHOUT_MESSAGE_IMPL) )

	#define AL_ENGINE_ASSERT(...) AL_EXPAND( AL_CHOOSE_MACRO(__VA_ARGS__)(_ENGINE_, __VA_ARGS__) )
	#define AL_ASSERT(...) AL_EXPAND( AL_CHOOSE_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )

#else

#endif
