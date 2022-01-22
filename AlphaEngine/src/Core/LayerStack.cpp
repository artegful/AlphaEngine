#include "LayerStack.h"
#include "Layer.h"
#include <algorithm>

namespace Alpha
{
    LayerStack::LayerStack() :
        layerInsertIterator(layers.begin())
    { }

    LayerStack::~LayerStack()
    {
        for (auto layer : layers)
        {
            delete layer;
        }
    }

    void LayerStack::AddLayer(Layer* layer)
    {
        layerInsertIterator = layers.emplace(layerInsertIterator, layer);
        layer->Open();
    }

    void LayerStack::AddOverlay(Layer* overlay)
    {
        layers.push_back(overlay);
        overlay->Open();
    }

    void LayerStack::RemoveLayer(Layer* layer)
    {
        auto result = std::find(layers.begin(), layers.end(), layer);

        if (result != layers.end())
        {
            (*result)->Close();
            delete (*result);

            layers.erase(result);
            layerInsertIterator--;
        }
    }

    void LayerStack::RemoveOverlay(Layer* overlay)
    {
        auto result = std::find(layers.begin(), layers.end(), overlay);

        if (result != layers.end())
        {
            (*result)->Close();
            delete (*result);

            layers.erase(result);
        }
    }

    std::vector<Layer*>::iterator LayerStack::begin()
    {
        return layers.begin();
    }


    std::vector<Layer*>::iterator LayerStack::end()
    {
        return layers.end();
    }
}
