#include "OpenGLRendererAPI.h"

#include <memory>
#include "GL/glew.h"
#include "Render/VertexArray.h"
#include "Render/Shader.h"

namespace Alpha
{
	void OpenGLRendererAPI::Initialize()
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const VertexArray& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray.GetAmountOfElements(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawIndexed(const VertexArray& vertexArray, size_t amount)
	{
		glDrawElements(GL_TRIANGLES, amount, GL_UNSIGNED_INT, nullptr);
	}
}

