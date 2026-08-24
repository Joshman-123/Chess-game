#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <functional>
#include <tuple>
#include <cstdint>
#include <expected>
#include <stdexcept>
#include <stdio.h>  
#include "Logger.hpp"
namespace utl
{
    enum class BindingErr : uint8_t
    {
        BINDING_NOT_FOUND
    };

    template <typename Base>
    class Binding
    {
    public:
        using UptrOrErr = std::expected<std::unique_ptr<Base>, BindingErr>;
        using ErasedCtor =
            std::function<std::unique_ptr<Base>(void *)>;

        template <typename... Args>
        static UptrOrErr create(
            const std::string &name, Args &&...args)
        {
            auto it = registry().find(name);
            if (it == registry().end())
            {
                return std::unexpected(BindingErr::BINDING_NOT_FOUND);
            }

            auto tuple = std::make_tuple(std::forward<Args>(args)...);
            return it->second(static_cast<void *>(&tuple));
        }

        static void registerCtor(const std::string &name, ErasedCtor ctor)
        {
            LOG_INFO("Registering binding for '%s'", name.c_str());
            registry().emplace(name, std::move(ctor));
        }

    private:
        static std::unordered_map<std::string, ErasedCtor> &registry()
        {
            static std::unordered_map<std::string, ErasedCtor> inst;
            return inst;
        }
    };
}
