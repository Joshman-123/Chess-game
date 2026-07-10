#pragma once
#include <stdint.h>
#include <PieceInterface.hpp>
namespace piece
{
    class KnightPiece final : public IChessPiece
    {
        public:
        KnightPiece();
        virtual ~KnightPiece();
        MoveReturnType move() override;
        private:
        KnightPiece(const KnightPiece&) = delete;
        KnightPiece& operator=(const KnightPiece&) = delete;    
        KnightPiece(KnightPiece&&) = delete;
        KnightPiece& operator=(KnightPiece&&) = delete;
    };
}