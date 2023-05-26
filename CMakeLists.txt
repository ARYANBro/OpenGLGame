cmake_minimum_required(VERSION 3.0.0)
project(OpenGLGame VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 23)

find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_subdirectory(Vendor/stb_image)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Game/Include
)

file(GLOB_RECURSE Source
    Game/*.cpp
    Engine/*.cpp
)

add_compile_definitions(
    _UNICODE
    NOMINMAX
)

link_libraries(
    glad::glad
    opengl32
    stb_image
    glm::glm
)
    
add_executable(OpenGLGame ${Source})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
