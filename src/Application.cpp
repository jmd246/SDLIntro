#include<Application.hpp>

Application::Application(const char* title, int w, int h) {
    // Set desired OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);

    window = SDL_CreateWindow(title, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    m_renderer = new Renderer();
    SDL_SetWindowRelativeMouseMode(window,true);
    if (!InitSDL()) {
        throw std::exception("error");
    }
    if (!InitGLad())  throw std::exception("error");
    glEnable(GL_DEPTH_TEST);
}

void Application::run()
{
    // Main loop
  
    
  

    std::vector<Vertex> vertices = {
        // Front face (+Z)
        {{-0.5f, -0.5f,  0.5f}, {0, 0, 1}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0, 0, 1}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0, 0, 1}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0, 0, 1}, {0.0f, 1.0f}},

        // Back face (-Z)
        {{ 0.5f, -0.5f, -0.5f}, {0, 0, -1}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0, 0, -1}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0, 0, -1}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0, 0, -1}, {0.0f, 1.0f}},

        // Left face (-X)
        {{-0.5f, -0.5f, -0.5f}, {-1, 0, 0}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {-1, 0, 0}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {-1, 0, 0}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {-1, 0, 0}, {0.0f, 1.0f}},

        // Right face (+X)
        {{ 0.5f, -0.5f,  0.5f}, {1, 0, 0}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {1, 0, 0}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1, 0, 0}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1, 0, 0}, {0.0f, 1.0f}},

        // Top face (+Y)
        {{-0.5f,  0.5f,  0.5f}, {0, 1, 0}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0, 1, 0}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0, 1, 0}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0, 1, 0}, {0.0f, 1.0f}},

        // Bottom face (-Y)
        {{-0.5f, -0.5f, -0.5f}, {0, -1, 0}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {0, -1, 0}, {1.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0, -1, 0}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {0, -1, 0}, {0.0f, 1.0f}}
    };

    std::vector<unsigned int> indices = {
        // Front face
        0, 1, 2,
        2, 3, 0,

        // Back face
        4, 5, 6,
        6, 7, 4,

        // Left face
        8, 9,10,
       10,11, 8,

       // Right face
      12,13,14,
      14,15,12,

      // Top face
     16,17,18,
     18,19,16,

     // Bottom face
    20,21,22,
    22,23,20
    };

    Camera camera;
    m_renderer->SetCamera(camera);
    Mesh triangleMesh(vertices, indices);

     isRunning = true;
     Shader shader("../assets/Shaders/vert.txt", "../assets/Shaders/frag.txt");
     if (!shader.build()) {
         return;
     }

     std::string uniformName = "greenVal";
   
     float  prevTime = SDL_GetTicks(),currTime=SDL_GetTicks();

    while (isRunning) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        currTime = SDL_GetTicks();
        float   dt = currTime - prevTime;
        dt /= 1000;
        prevTime = currTime;
        float greenVal = sin(currTime/200) / 2.0f + 0.5f;
        ProcessInput(dt);
        m_renderer->BeginFrame(glm::vec4(0.1f, 0.2f, 0.3f, 1.0f));

        shader.setFloat(uniformName, greenVal);
        m_renderer->DrawMesh(triangleMesh, shader, model);
       
        m_renderer->EndFrame(window);
    }
}

Application::~Application()
{
    Cleanup();
}

void Application::ProcessInput(float dt)
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
        else if (event.type == SDL_EVENT_MOUSE_MOTION) {
            float xoffset = static_cast<float>(event.motion.xrel);
            float yoffset = static_cast<float>(-event.motion.yrel); // invert Y
            std::cout << xoffset << "    " << yoffset << std::endl;
            m_renderer->m_cam.ProcessMouseMovement(xoffset, yoffset, false);
        }
    }
        const bool* state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_W]) m_renderer->m_cam.ProcessKeyboard('w', dt);
        if (state[SDL_SCANCODE_S]) m_renderer->m_cam.ProcessKeyboard('s', dt);
        if (state[SDL_SCANCODE_A]) m_renderer->m_cam.ProcessKeyboard('a', dt);
        if (state[SDL_SCANCODE_D]) m_renderer->m_cam.ProcessKeyboard('d', dt);
        if (state[SDL_SCANCODE_ESCAPE]) {
            isRunning = false;
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
    delete(m_renderer);
    SDL_Quit();
}

void Application::Update()
{
}

void Application::Render()
{
}
