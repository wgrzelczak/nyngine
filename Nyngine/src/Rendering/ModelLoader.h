#pragma once
#include "Preinclude.h"
#include "Mesh.h"

namespace ny::Rendering::ModelLoader
{
    void LoadObj(Mesh& mesh, std::string filename);
} // namespace ny::Rendering::ModelLoader