#pragma once

#include <string>

namespace Alpha
{
	struct NameComponent
	{
		std::string Name;

		NameComponent(const std::string& name) :
			Name(name)
		{ }
		NameComponent(const NameComponent&) = default;

		operator std::string() const
		{
			return Name;
		}
	};
}