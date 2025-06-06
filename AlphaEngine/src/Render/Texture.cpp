#include "Texture.h"

#include "Core/Core.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLTexture.h"

namespace Alpha
{
	std::shared_ptr<Texture> Texture::Create(const std::string& path)
	{
		switch (RendererAPI::GetAPI())
		{
		case API::OpenGL: return std::make_shared<OpenGLTexture>(path);
		}

		AL_ENGINE_ASSERT(false, "Provided rendering API is not supported");
		return nullptr;
	}

	std::shared_ptr<Texture> Texture::Create(size_t width, size_t height)
	{
		switch (RendererAPI::GetAPI())
		{
		case API::OpenGL: return std::make_shared<OpenGLTexture>(width, height);
		}

		AL_ENGINE_ASSERT(false, "Provided rendering API is not supported");
		return nullptr;
	}
}