#pragma once

#include <memory>
#include <functional>

#include "Core.h"
#include "Window.h"
#include "Render/RenderContext.h"

struct GLFWwindow;

namespace Alpha
{
	struct Event;

	class GlfwWindow : public Window
	{
	public:
		GlfwWindow(int width, int height);

		void Initialize() override;
		void Update() override;
		void SwapBuffers() override;
		void SetEventCallback(std::function<void(Event&)> callback) override;

		bool ShouldClose() const override;
		int GetWidth() const override;
		int GetHeight() const override;

		GLFWwindow* GetNativeWindow();

	private:
		GLFWwindow* window;
		std::function<void(Event&)> eventCallback;
		std::unique_ptr<RenderContext> renderContext;

		int width;
		int height;

		void InitializeWindow();
		void MakeContextCurrent();
		void BindEvents();
	};
}

