#pragma once

#include <vector>

namespace Alpha
{
	class Layer;

	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void AddLayer(Layer* layer);
		void AddOverlay(Layer* overlay);

		void RemoveLayer(Layer* layer);
		void RemoveOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin();
		std::vector<Layer*>::iterator end();

	private:
		std::vector<Layer*> layers;

		std::vector<Layer*>::iterator layerInsertIterator;
	};
}


