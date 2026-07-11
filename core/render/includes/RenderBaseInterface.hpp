#pragma once
#include "RenderDefs.hpp"
namespace render
{
    class RenderInf
    {
        public:
        virtual ~RenderInf() = default;
        virtual RenderErr execute() = 0;
    };
}