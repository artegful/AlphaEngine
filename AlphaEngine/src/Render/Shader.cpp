#include "Shader.h"

#include "Core/Core.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLShader.h"

namespace Alpha
{
	std::shared_ptr<Shader> Shader::Create(const std::string& path)
	{
		switch (RendererAPI::GetAPI())
		{
		case API::OpenGL: return std::make_shared<OpenGLShader>(path);
		}

		AL_ENGINE_ASSERT(false, "Provided rendering API is not supported");
		return nullptr;
	}
}