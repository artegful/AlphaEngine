#include "Utils.h"

#include <filesystem>

std::string Alpha::Utils::GetNameFromPath(const std::string& path)
{
	return std::filesystem::path(path).filename().string();
}
