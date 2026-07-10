#pragma once
#include <stdint.h>
#include <PieceInterface.hpp>
namespace piece
{
    class RookPiece final : public IChessPiece
    {
        public:
        RookPiece();
        virtual ~RookPiece();
        MoveReturnType move() override;
        private:
        RookPiece(const RookPiece&) = delete;
        RookPiece& operator=(const RookPiece&) = delete;    
        RookPiece(RookPiece&&) = delete;
        RookPiece& operator=(RookPiece&&) = delete;
    };
}