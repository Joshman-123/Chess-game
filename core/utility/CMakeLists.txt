add_library(utility
    includes/AutoRegister.hpp
    includes/Binding.hpp
    includes/Util.hpp
    includes/Logger.hpp
    src/dummy.cpp
)

target_include_directories(utility
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
        ${CMAKE_SOURCE_DIR}
)

target_compile_features(utility PUBLIC cxx_std_23)
