#include "OpenGLRenderContext.h"

#include "Core/Core.h"
#include <sstream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

using namespace std::string_literals;

namespace Alpha
{
	void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
			GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		if (type == GL_DEBUG_TYPE_ERROR)
		{
			AL_ENGINE_ASSERT(false, message);
		}
		else
		{
			AL_ENGINE_INFO("(", severity, ") ", message);
		}
	}

	void OpenGLRenderContext::Initialize(GLFWwindow* window)
	{
		this->window = window;

		glewExperimental = GL_TRUE;

		GLenum result = glewInit();
		AL_ENGINE_ASSERT(result == GLEW_OK, "Glew initialization failed with: "s + reinterpret_cast<const char*>(glewGetErrorString(result)));

		#ifdef AL_DEBUG

		//glEnable(GL_DEBUG_OUTPUT);
		//glDebugMessageCallback(MessageCallback, 0);
		
		#endif
	}

	void OpenGLRenderContext::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}
}