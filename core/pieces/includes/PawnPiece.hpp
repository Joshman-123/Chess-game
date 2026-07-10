#pragma once
#include <stdint.h>
#include <PieceInterface.hpp>
namespace piece
{
    class PawnPiece final : public IChessPiece
    {
        public:
        PawnPiece();
        virtual ~PawnPiece();
        MoveReturnType move() override;
        private:
        PawnPiece(const PawnPiece&) = delete;
        PawnPiece& operator=(const PawnPiece&) = delete;    
        PawnPiece(PawnPiece&&) = delete;
        PawnPiece& operator=(PawnPiece&&) = delete;
    };
}