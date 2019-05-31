#pragma once

namespace ny
{
    class Scene
    {
    public:
        Scene() {}
        ~Scene() {}

        void Init();
        void Destroy();
        void Update();
    };
} // namespace ny