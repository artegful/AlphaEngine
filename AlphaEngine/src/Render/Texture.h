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

		virtual void SetData(void* data, size_t size, int channels = 3) = 0;
		virtual void SetType(const std::string& type) = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual std::string GetPath() const = 0;
		virtual std::string GetType() const = 0;

		virtual bool operator==(const Texture& texture) = 0;

		static std::shared_ptr<Texture> Create(const std::string& path);
		static std::shared_ptr<Texture> Create(size_t width, size_t height);
	};
}