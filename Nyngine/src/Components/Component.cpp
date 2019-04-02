#include "pch.h"
#include "Component.h"
#include "Preinclude.h"

namespace ny
{
    Component::Component()
    {
    }
    Component::~Component()
    {
        NY_TRACE("Component destroyed");
    }
    void Component::Update()
    {
        NY_TRACE("Update");
    }
} // namespace ny