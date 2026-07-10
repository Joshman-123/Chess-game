#pragma once
#include <stdint.h>
namespace core
{
    enum class CoreRetType : uint8_t
    {
        FAILED,
        SUCESS
    };

    class CoreGame final
    {
        public:
        CoreGame();
        ~CoreGame();
        CoreRetType Run();
        private:
        CoreGame(const CoreGame&) = delete;
        CoreGame& operator=(const CoreGame&) = delete;
        CoreGame(CoreGame&&) = delete;
        CoreGame& operator=(CoreGame&&) = delete;
    };
}