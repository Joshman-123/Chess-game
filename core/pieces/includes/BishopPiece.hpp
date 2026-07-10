#pragma once
#include <stdint.h>
#include <PieceInterface.hpp>
namespace piece
{
    class BishopPiece final : public IChessPiece
    {
        public:
        BishopPiece();
        virtual ~BishopPiece();
        MoveReturnType move() override;
        private:
        BishopPiece(const BishopPiece&) = delete;
        BishopPiece& operator=(const BishopPiece&) = delete;    
        BishopPiece(BishopPiece&&) = delete;
        BishopPiece& operator=(BishopPiece&&) = delete;
    };
}