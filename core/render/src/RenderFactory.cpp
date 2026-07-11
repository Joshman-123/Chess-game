#include <iostream>
#include "Binding.hpp"
#include "RenderFactory.hpp"
#include <utility> // Required for std::unexpected
namespace render
{
    RndrInfOrErr RenderFactory::create(const RenderConfig &f_config)
    {
        if ((f_config.m_renderType.empty() || f_config.m_windowName.empty() || f_config.m_width == 0U || f_config.m_height == 0U))
        {
            return std::unexpected(RenderErr::INVALID_ARGUMENTS);
        }

        auto l_infOrErr = utl::Binding<RenderInf>::create(f_config.m_renderType, f_config);

        if (not l_infOrErr.has_value())
        {
            return std::unexpected(RenderErr::BINDING_CREATION_FAILED);
        }

        return std::move(l_infOrErr.value());
    }
}
