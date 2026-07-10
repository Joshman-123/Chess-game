#pragma once
#include <stdint.h>
namespace piece
{
    enum class MoveReturnType : uint8_t 
    {
        INVALID_MOVE,
        SUCESS,
    };

    class IChessPiece
    {
        public:
        virtual ~IChessPiece();
        virtual MoveReturnType move() = 0;
    };
}