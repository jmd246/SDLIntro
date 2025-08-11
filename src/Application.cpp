#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>  
#include <iostream>
#include <Shader.hpp>
#include <Mesh.hpp>
#include <Application.hpp>

Application::Application(const char* title, int w, int h) {
    // Set desired OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);

    window = SDL_CreateWindow(title, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!InitSDL()) {
        throw std::exception("error");
    }
    if (!InitGLad())  throw std::exception("error");
}

void Application::run()
{
    // Main loop
    float triangle[] = {
       -0.5,-0.5f,0,
       0.5f,-0.5f,0,
       0,0.5f,0
    };
    std::vector<Vertex> vertices = {
      {{-0.5f, -0.5f, 0.0f}, {}, {0.0f, 0.0f}},
      {{0.5f, -0.5f, 0.0f}, {}, {1.0f, 0.0f}},
      {{0.0f,  0.5f, 0.0f}, {}, {0.5f, 1.0f}}
    };

    std::vector<uint32_t> indices = { 0, 1, 2 };

    Mesh triangleMesh(vertices, indices);

     isRunning = true;
     Shader shader("../assets/Shaders/vert.txt", "../assets/Shaders/frag.txt");
     if (!shader.build()) {
         return;
     }

     std::string uniformName = "greenVal";
    while (isRunning) {
        float currTime = SDL_GetTicks();
        float greenVal = cos(currTime/1000) / 2.0f + 0.5f;
        ProcessInput();
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.setFloat(uniformName, greenVal);
        shader.use();
        triangleMesh.draw();
        SDL_GL_SwapWindow(window);
    }
}

Application::~Application()
{
    Cleanup();
}

void Application::ProcessInput()
{
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            isRunning = false;
        }
        else if (event.type == SDL_EVENT_WINDOW_RESIZED) {
            int newWidth = event.window.data1;
            int newHeight = event.window.data2;
            glViewport(0, 0, newWidth, newHeight);
        }
    }
}

bool Application::InitGLad()
{
    // Create OpenGL context
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }
	return true;
}

bool Application::InitSDL()
{
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        return false;
    }
    context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cerr << "SDL_GL_CreateContext Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        return false;
    }
	return true;
}

void Application::Cleanup()
{
    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Application::Update()
{
}

void Application::Render()
{
}
