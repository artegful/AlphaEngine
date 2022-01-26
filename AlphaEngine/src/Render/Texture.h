#pragma once

#include <memory>
#include <string>

namespace Alpha
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void Bind(int slot = 0) = 0;
		virtual void Unbind() = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;

		static std::shared_ptr<Texture> Create(const std::string& path);
	};
}