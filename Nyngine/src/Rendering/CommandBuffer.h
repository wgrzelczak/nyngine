#pragma once
#include "Preinclude.h"
#include "Command.h"

namespace ny::Rendering
{
    class CommandBuffer
    {
    public:
        CommandBuffer();
        ~CommandBuffer();

        std::vector<Command>& GetCommands();
        void PushCommand(Command cmd);
        void Clear();

    private:
        std::vector<Command> m_commands;
    };
} // namespace ny::Rendering