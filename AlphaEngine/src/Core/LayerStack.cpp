#include "LayerStack.h"
#include "Layer.h"
#include <algorithm>

namespace Alpha
{
    LayerStack::~LayerStack()
    {
        for (auto layer : layers)
        {
            delete layer;
        }
    }

    void LayerStack::AddLayer(Layer* layer)
    {
        layers.emplace(layers.begin() + insertIndex, layer);
        insertIndex++;
        layer->Open();
    }

    void LayerStack::AddOverlay(Layer* overlay)
    {
        layers.emplace_back(overlay);
        overlay->Open();
    }

    void LayerStack::RemoveLayer(Layer* layer)
    {
        auto result = std::find(layers.begin(), layers.begin() + insertIndex, layer);

        if (result != layers.end())
        {
            (*result)->Close();
            delete (*result);

            layers.erase(result);
            insertIndex--;
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

    std::vector<Layer*>::reverse_iterator LayerStack::rbegin()
    {
        return layers.rbegin();
    }

    std::vector<Layer*>::reverse_iterator LayerStack::rend()
    {
        return layers.rend();
    }
}
