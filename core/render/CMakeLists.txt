add_library(Render
    includes/RenderFactory.hpp
    src/RenderFactory.cpp
)

target_include_directories(Render
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(Render PUBLIC utility)
