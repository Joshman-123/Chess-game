#pragma once
#include <stdint.h>
#include <PieceInterface.hpp>
namespace piece
{
    class KingPiece final : public IChessPiece
    {
        public:
        KingPiece();
        virtual ~KingPiece();
        MoveReturnType move() override;
        private:
        KingPiece(const KingPiece&) = delete;
        KingPiece& operator=(const KingPiece&) = delete;    
        KingPiece(KingPiece&&) = delete;
        KingPiece& operator=(KingPiece&&) = delete;
    };
}