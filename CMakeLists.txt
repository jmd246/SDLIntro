cmake_minimum_required(VERSION 3.20)
project(SdlIntro LANGUAGES CXX)

# Use C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force CMake to use your specific vcpkg installation
set(CMAKE_TOOLCHAIN_FILE
    "C:/Users/Owner/OneDrive/Desktop/SDLIntro/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file"
)



# Find SDL3 and OpenGL
find_package(SDL3 CONFIG REQUIRED)

find_package(imgui CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED)




# Create your executable
add_executable(SdlIntro src/main.cpp src/Shader.cpp src/Application.cpp src/Mesh.cpp src/Renderer.cpp src/Camera.cpp)

target_include_directories(SdlIntro PRIVATE include)


# Link SDL3 and OpenGL
target_link_libraries(SdlIntro PRIVATE glad::glad SDL3::SDL3 OpenGL::GL)


