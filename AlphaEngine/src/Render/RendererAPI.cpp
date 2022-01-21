#include "RendererAPI.h"

#include "glm/vec4.hpp"
#include "Core/Core.h"
#include "OpenGL/OpenGLRendererAPI.h"

namespace Alpha
{
	API RendererAPI::Api = API::None;

	API RendererAPI::GetAPI()
	{
		AL_ASSERT(Api != API::None, "Rendering API set to None, you must provide a valid API type before rendering initialization");

		return Api;
	}

	RendererAPI* RendererAPI::Create()
	{
		switch (Api)
		{
			case API::OpenGL: return new OpenGLRendererAPI();
		}

		AL_ENGINE_ASSERT(false, "Provided Render API is not supported");
		return nullptr;
	}
}