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
		virtual ~Window() = default;

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void SwapBuffers() = 0;
		virtual void SetEventCallback(std::function<void(Event&)> callback) = 0;

		virtual bool ShouldClose() const = 0;
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;

	};
}

