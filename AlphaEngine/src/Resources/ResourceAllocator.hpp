#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <filesystem>

namespace Alpha
{
	template<typename T>
	class ResourceAllocator
	{
	public:
		static ResourceAllocator<T>& Instance();

		template<typename... Args>
		static std::shared_ptr<T> Get(const std::string& filePath, Args&&... args);

	private:
		std::unordered_map<std::string, std::shared_ptr<T>> pathToPtr;

		template<typename... Args>
		std::shared_ptr<T> AddOrGet(const std::string& filePath, Args&&... args);
	};

	template<typename T>
	ResourceAllocator<T>& ResourceAllocator<T>::Instance()
	{
		static ResourceAllocator<T> allocator;

		return allocator;
	}

	template<typename T>
	template<typename... Args>
	std::shared_ptr<T> ResourceAllocator<T>::Get(const std::string& filePath, Args&&... args)
	{
		return Instance().AddOrGet(filePath, std::forward<Args>(args)...);
	}

	template<typename T>
	template<typename... Args>
	std::shared_ptr<T> ResourceAllocator<T>::AddOrGet(const std::string& filePath, Args&&... args)
	{
		std::filesystem::path path(filePath);
		std::string fullPath = std::filesystem::absolute(path).string();

		auto result = pathToPtr.find(fullPath);

		if (result != pathToPtr.end())
		{
			return result->second;
		}

		std::shared_ptr<T> ptr = T::Create(filePath, args...);
		pathToPtr[fullPath] = ptr;

		return ptr;
	}
}


