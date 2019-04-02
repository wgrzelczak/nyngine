#include "pch.h"
#include "Core\Application.h"
#include "GameLayer.h"

int main(int argc, char** agrv)
{
    ny::Core::Application app;

    app.PreInit();
    app.Init();

    //app.PushLayer<GameLayer>();

    app.Run();
    app.Shutdown();

    return 0;
}