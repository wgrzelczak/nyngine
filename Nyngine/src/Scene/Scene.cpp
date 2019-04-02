#include "pch.h"
#include "Scene.h"

namespace ny
{
    void Scene::Init()
    {
        m_entities.emplace_back();
        m_entities.back().m_components.push_back(std::make_shared<Component>());
    }

    void Scene::Destroy()
    {
        for (auto e : m_entities)
        {
            e.Destroy();
        }
        m_entities.clear();
    }

    void Scene::Update()
    {
        for (const auto& e : m_entities)
        {
            for (const auto& c : e.m_components)
            {
                c->Update();
            }
        }
    }
} // namespace ny