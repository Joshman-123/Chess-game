add_library(OpenGLRender OBJECT
    src/OpenGLRender.cpp
    src/VertexBufferObject.cpp
    src/VertexArrayObject.cpp
    src/ElementBufferObject.cpp
    src/Shader.cpp
)

target_include_directories(OpenGLRender
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
        ${CMAKE_SOURCE_DIR}
)
add_definitions(-DDEBUG_BUILD)
target_link_libraries(OpenGLRender PUBLIC utility Render)
target_include_directories(OpenGLRender
    PRIVATE
        ../../../third_party/glad/include
        ../../../third_party/
)

target_compile_features(OpenGLRender PRIVATE cxx_std_23)