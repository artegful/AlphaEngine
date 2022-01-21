#pragma once

#ifdef AL_LOGGING

	#include <iostream>
	#include <chrono>

	#ifdef AL_WINDOWS
		#ifndef NOMINMAX
		# define NOMINMAX
		#endif
		#include <windows.h>
	#endif
	
	class Logger
	{
	public:
		enum class Color
		{
			White = 15,
			Yellow = 14,
			Red = 12,
			Blue = 1
		};

		template<typename ...Args>
		static void Output(Args&&... args)
		{
			std::cout << std::chrono::system_clock::now() << ": ";
			(std::cout << ... << args);
			std::cout << '\n';
		}

		template<typename ...Args>
		static void Output(Color color, Args&&... args)
		{
			#ifdef AL_WINDOWS
				SetConsoleTextAttribute(console, (uint16_t)color);
			#endif

			Output(std::forward<Args>(args)...);

			#ifdef AL_WINDOWS
				SetConsoleTextAttribute(console, (uint16_t)Color::White);
			#endif
		}

	private:
		inline static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	};

	#define AL_ENGINE_INFO(...)    { Logger::Output("[ENGINE][info] ", __VA_ARGS__); }
	#define AL_ENGINE_WARNING(...) { Logger::Output(Logger::Color::Yellow, "[ENGINE][warning] ", __VA_ARGS__); } 
	#define AL_ENGINE_ERROR(...)   { Logger::Output(Logger::Color::Red, "[ENGINE][error] ", __VA_ARGS__); } 

	#define AL_INFO(...)		   { Logger::Output("[info] ", __VA_ARGS__); }
	#define AL_WARNING(...)		   { Logger::Output(Logger::Color::Yellow, "[warning] ", __VA_ARGS__); } 
	#define AL_ERROR(...)		   { Logger::Output(Logger::Color::Red, "[error] ", __VA_ARGS__); } 

#else

	#define AL_ENGINE_INFO(...)   
	#define AL_ENGINE_WARNING(...)
	#define AL_ENGINE_ERROR(...)  

	#define AL_INFO(...)   
	#define AL_WARNING(...)
	#define AL_ERROR(...)  

#endif