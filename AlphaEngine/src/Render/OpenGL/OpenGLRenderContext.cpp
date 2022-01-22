#include "OpenGLRenderContext.h"

#include "Core/Core.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

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
			//AL_ENGINE_INFO("(", severity, ") ", message);
		}
	}

	void OpenGLRenderContext::Initialize(GLFWwindow* window)
	{
		this->window = window;

		glfwMakeContextCurrent(window);

		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK)
		{
			glfwDestroyWindow(window);
			glfwTerminate();
		}

		#ifdef AL_DEBUG

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);
		
		#endif
	}

	void OpenGLRenderContext::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}
}