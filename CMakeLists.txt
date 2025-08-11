cmake_minimum_required(VERSION 3.20)
project(SdlIntro LANGUAGES CXX)

# Use C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# Find SDL3 and OpenGL
find_package(SDL3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_library(glad STATIC)

target_sources(glad PRIVATE src/glad.c)

set_target_properties(glad PROPERTIES
    LINKER_LANGUAGE C
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
)

target_include_directories(glad PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)


# Create your executable
add_executable(SdlIntro src/main.cpp src/Shader.cpp src/Application.cpp src/Mesh.cpp)

target_include_directories(SdlIntro PRIVATE include)


# Link SDL3 and OpenGL
target_link_libraries(SdlIntro PRIVATE glad SDL3::SDL3 OpenGL::GL)

# Assume SDL3.dll is located in the vcpkg installed path
set(SDL3_DLL "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-windows/bin/SDL3.dll")

add_custom_command(TARGET SdlIntro POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${SDL3_DLL}"
    $<TARGET_FILE_DIR:SdlIntro>)
