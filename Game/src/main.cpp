#include "pch.h"
#include "Core\Engine.h"
#include "NyngineApp.h"

int main(int argc, char** agrv)
{
    auto* engine = ny::Core::Engine::GetInstance();

    engine->Run(new NyngineApp());

    return 0;
}