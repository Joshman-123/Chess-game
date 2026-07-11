#pragma once

#include <Util.hpp>
#include <RenderDefs.hpp>
#include <expected>
#include <memory>
#include <RenderBaseInterface.hpp>
namespace render
{
    using RndrInfOrErr = std::expected<std::unique_ptr<RenderInf>, RenderErr>;
    class RenderFactory final
    {
        public:
        static RndrInfOrErr create(const RenderConfig &f_config);
        private:
        RenderFactory() = delete;
        ~RenderFactory() = delete;
        DELETE_COPY_MOVE_OPERATORS(RenderFactory);
        
    };
}