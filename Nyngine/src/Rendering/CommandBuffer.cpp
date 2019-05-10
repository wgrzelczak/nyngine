#include "pch.h"
#include "CommandBuffer.h"

namespace ny::Rendering
{
    CommandBuffer::CommandBuffer()
    {
    }

    CommandBuffer::~CommandBuffer()
    {
    }

    std::vector<Command>& CommandBuffer::GetCommands()
    {
        return m_commands;
    }

    void CommandBuffer::PushCommand(Command cmd)
    {
        m_commands.push_back(std::move(cmd));
    }

    void CommandBuffer::Clear()
    {
        m_commands.clear();
    }

} // namespace ny::Rendering