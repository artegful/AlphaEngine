#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace Resources
{
	template<typename T>
	class ResourceAllocator
	{
	public:
		static ResourceAllocator<T>& Get();

		template<typename... Args>
		std::shared_ptr<T> Add(const std::string& filePath, Args&&... args);

		template<typename... Args>
		std::shared_ptr<T> Add(const std::string& firstFile, const std::string& secondFile, Args&&... args);

	private:
		std::unordered_map<std::string, std::shared_ptr<T>> pathToPtr;
	};

	template<typename T>
	ResourceAllocator<T>& ResourceAllocator<T>::Get()
	{
		static ResourceAllocator<T> allocator;

		return allocator;
	}

	template<typename T>
	template<typename... Args>
	std::shared_ptr<T> ResourceAllocator<T>::Add(const std::string& filePath, Args&&... args)
	{
		auto result = pathToPtr.find(filePath);

		if (result != pathToPtr.end())
		{
			return result->second;
		}

		std::shared_ptr<T> ptr = std::make_shared<T>(filePath, args...);
		pathToPtr[filePath] = ptr;

		return ptr;
	}
}


