#pragma once
#include "Binding.hpp"
#include <tuple>
#include <type_traits>
namespace utl
{
    template <typename Base, typename Concrete, typename... CtorArgs>
    struct AutoRegister
    {
        static_assert(std::is_base_of<Base, Concrete>::value,
                      "Concrete must derive from Base");

        AutoRegister(const char *name)
        {
            Binding<Base>::registerCtor(
                name,
                [](void *data) -> std::unique_ptr<Base>
                {
                    auto *tup =
                        static_cast<std::tuple<CtorArgs...> *>(data);

                    return construct(*tup,
                                     std::index_sequence_for<CtorArgs...>{});
                });
        }

    private:
        template <std::size_t... I>
        static std::unique_ptr<Base>
        construct(std::tuple<CtorArgs...> &tup,
                  std::index_sequence<I...>)
        {
            return std::make_unique<Concrete>(
                std::get<I>(tup)...);
        }
    };
}
