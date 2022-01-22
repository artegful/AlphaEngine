#pragma once

namespace Alpha
{
	class Layer
	{
	public:
		virtual void Open() { }
		virtual void Close() { }
		virtual void Update(float deltaTime) { }
	};
}

