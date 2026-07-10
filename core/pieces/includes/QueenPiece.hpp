#pragma once
#include <stdint.h>
#include <PieceInterface.hpp>
namespace piece
{
    class QueenPiece final : public IChessPiece
    {
        public:
        QueenPiece();
        virtual ~QueenPiece();
        MoveReturnType move() override;
        private:
        QueenPiece(const QueenPiece&) = delete;
        QueenPiece& operator=(const QueenPiece&) = delete;    
        QueenPiece(QueenPiece&&) = delete;
        QueenPiece& operator=(QueenPiece&&) = delete;
    };
}