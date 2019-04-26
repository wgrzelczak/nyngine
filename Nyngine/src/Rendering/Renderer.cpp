#include "pch.h"
#include "Renderer.h"
#include "Core/Engine.h"
#include "glad/glad.h"

namespace ny::Rendering
{
    void Renderer::Init()
    {
        m_material = std::make_shared<Material>("Assets/Shaders/default.vs", "Assets/Shaders/default.fs");

        //TODO
        float vertices[] = {
            -1, 1, 0, 1, 1, 1,
            -1, -1, 0, 1, 1, 1,
            1, 1, 0, 1, 1, 1,

            1, 0, 0, 1, 0, 0,
            1, -1, 0, 0, 1, 0,
            0, -1, 0, 0, 0, 1};
        unsigned int indices[] = {
            0, 1, 2,
            3, 4, 5};

        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);

        glBindVertexArray(VAO);
    }

    void Renderer::BeginFrame()
    {
        glClearColor(0.25f, 0.25f, 0.25f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(m_material->GetId());
        glUniform1ui(glGetUniformLocation(m_material->GetId(), "time"), ny::Core::Time::DeltaFromStart());

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        u32 width = ny::Core::Engine::GetInstance()->GetWindow().GetWidth();
        u32 height = ny::Core::Engine::GetInstance()->GetWindow().GetHeight();

        f32 ratio = width / (f32)height;
        glViewport(0, 0, width, height);
    }
} // namespace ny::Rendering