#pragma once
#include "Preinclude.h"

namespace ny::Rendering
{
    namespace Attribute
    {
        using type = u16;
        const type aPosition = BIT_POSITION(0);
        const type aNormal = BIT_POSITION(1);

        const type aColor3 = BIT_POSITION(2);
        const type aColor4 = BIT_POSITION(3);

        const type aTexture0 = BIT_POSITION(4);
        const type aTexture1 = BIT_POSITION(5);
    } // namespace Attribute
    using Attrib_t = Attribute::type;

    enum class MaterialType
    {
        Undefined,
        Solid,
        Texture,
        TextureColorBlend,
        TexturesBlend
    };

    class AttributesHelper
    {
    public:
        static Attrib_t GetByType(MaterialType type)
        {
            switch (type)
            {
            case MaterialType::Undefined:
                NY_ERROR("[Rendering] Invalid MaterialType!");
                break;
            case MaterialType::Solid:
                return Attribute::aPosition | Attribute::aColor3;
                break;
            case MaterialType::Texture:
                return Attribute::aPosition | Attribute::aTexture0;
                break;
            case MaterialType::TextureColorBlend:
                return Attribute::aPosition | Attribute::aTexture0 | Attribute::aColor3;
                break;
            case MaterialType::TexturesBlend:
                return Attribute::aPosition | Attribute::aTexture0 | Attribute::aTexture1;
                break;
            }
            return 0;
        }

        static bool IsAttribSet(Attrib_t all, Attrib_t single)
        {
            return (BIT_ARE_SET(all, single));
        }

        static u32 GetAttributeSize(Attrib_t attrib)
        {
            switch (attrib)
            {
            case Attribute::aPosition:
                return 3 * sizeof(f32);
            case Attribute::aNormal:
                return 3 * sizeof(f32);
            case Attribute::aColor3:
                return 3 * sizeof(f32);
            case Attribute::aColor4:
                return 4 * sizeof(f32);
            case Attribute::aTexture0:
                return 2 * sizeof(f32);
            case Attribute::aTexture1:
                return 2 * sizeof(f32);
            }

            NY_ERROR("[Rendering] Invalid attrib!");
            return 0;
        }

        static u32 GetAttributesSize(Attrib_t attribs)
        {
            u32 size = 0;
            if (IsAttribSet(attribs, Attribute::aPosition)) size += GetAttributeSize(Attribute::aPosition);
            if (IsAttribSet(attribs, Attribute::aNormal)) size += GetAttributeSize(Attribute::aNormal);
            if (IsAttribSet(attribs, Attribute::aColor3)) size += GetAttributeSize(Attribute::aColor3);
            if (IsAttribSet(attribs, Attribute::aColor4)) size += GetAttributeSize(Attribute::aColor4);
            if (IsAttribSet(attribs, Attribute::aTexture0)) size += GetAttributeSize(Attribute::aTexture0);
            if (IsAttribSet(attribs, Attribute::aTexture1)) size += GetAttributeSize(Attribute::aTexture1);

            return size;
        }
    };
} // namespace ny::Rendering