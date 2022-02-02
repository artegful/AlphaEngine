#pragma once

#include <memory>
#include <functional>

#include "Core.h"
#include "Render/RenderContext.h"

struct GLFWwindow;

namespace Alpha
{
	struct Event;

	class Window
	{
	public:
		Window(int width, int height, std::function<void(Event&)> eventCallback);

		bool ShouldClose() const;
		int GetWidth() const;
		int GetHeight() const;

		void Update();
		void Initialize();

		void SwapBuffers();

		GLFWwindow* GetNativeWindow();

	private:
		static std::function<void(Event&)> EventCallback;
		GLFWwindow* window;
		std::unique_ptr<RenderContext> renderContext;

		int width;
		int height;

		void InitializeWindow();
		void BindEvents();

		void Bind(GLFWwindow* window, int button, int action, int mods);
	};
}

