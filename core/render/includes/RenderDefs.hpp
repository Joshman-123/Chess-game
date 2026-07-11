#pragma once
#include <stdint.h>
#include <string>
namespace render
{
    enum class RenderType : uint8_t
    {
        OPEN_GL,
        VULKAN
    };

    enum class RenderErr : uint8_t
    {
        NO_ERR,
        INCORRECT_SEQUENCE,
        INVALID_ARGUMENTS,
        BINDING_CREATION_FAILED
    };

    struct RenderConfig
    {
        std::string m_renderType{};
        std::string m_windowName{};
        uint32_t m_width{};
        uint32_t m_height{};
        uint32_t m_samples{};
    };
}