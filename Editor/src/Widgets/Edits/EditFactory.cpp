#include "EditFactory.h"

#include "glm/vec3.hpp"
#include "Reflection/MetadataType.h"
#include "Reflection/MetadataVectorUsage.h"
#include "Reflection/MetadataFileType.h"

#include "BoolEdit.h"
#include "FloatEdit.h"
#include "VectorEdit.h"
#include "ColorEdit.h"
#include "EnumEdit.h"
#include "ReflectedItemEdit.h"
#include "FileEdit.h"

BaseEdit* EditFactory::CreateEdit(const rttr::instance& instance, const rttr::property& property, QWidget* parent)
{
    rttr::type type = property.get_type();

    if (type == rttr::type::get<bool>())
    {
        return new BoolEdit(instance, property, parent);
    }
    if (type == rttr::type::get<float>())
    {
        return new FloatEdit(instance, property, parent);
    }
    if (type == rttr::type::get<glm::vec2>())
    {
        return new VectorEdit<2>(instance, property, parent);
    }
    if (type == rttr::type::get<glm::vec3>())
    {
        return new VectorEdit<3>(instance, property, parent);
    }
    if (type == rttr::type::get<glm::vec4>())
    {
        rttr::variant vectorUsage = property.get_metadata(Alpha::MetadataType::VectorUsage);

        if (vectorUsage.is_valid() && vectorUsage.convert<Alpha::MetadataVectorUsage>() == Alpha::MetadataVectorUsage::Color)
        {
            return new ColorEdit(instance, property, parent);
        }

        return new VectorEdit<4>(instance, property, parent);
    }
    if (type.is_enumeration())
    {
        return new EnumEdit(instance, property, parent);
    }
    if (type == rttr::type::get<std::string>())
    {
        rttr::variant vectorUsage = property.get_metadata(Alpha::MetadataType::FileType);

        if (vectorUsage.is_valid())
        {
            Alpha::MetadataFileType type = vectorUsage.convert<Alpha::MetadataFileType>();

            switch (type)
            {
            case Alpha::MetadataFileType::Model:
                return new FileEdit(instance, property, "Models (*.obj; *.fbx)", parent);
              
            case Alpha::MetadataFileType::Sprite:
                return new FileEdit(instance, property, "Textures (*.png; *.jpg)", parent);
            }
        }
    }

    return new ReflectedItemEdit(instance, property, parent);
}
