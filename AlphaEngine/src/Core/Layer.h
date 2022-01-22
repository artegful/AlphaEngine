#pragma once

namespace Alpha
{
	struct Event;

	class Layer
	{
	public:
		virtual void Open() { }
		virtual void Close() { }
		virtual void Update(float deltaTime) { }

		virtual void OnEvent(Event& event) { }
		virtual void OnImGui() { }
	};
}

