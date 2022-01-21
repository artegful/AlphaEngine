#pragma once

#include <memory>
#include "glm/vec2.hpp"
#include "Render/RendererAPI.h"

namespace Alpha
{
	class RenderCommand
	{
	public:
		static void SetAPI(API api);

		static void DrawIndexed();

		static void SetClearColor(const glm::vec4& color);
		static void Clear();

	private:
		static std::unique_ptr<RendererAPI> RendererApi;
	};
}