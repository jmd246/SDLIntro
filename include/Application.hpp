#ifndef APPLICATION_HPP
#define  APPLICATION_HPP
#include<glad/glad.h>
#include <SDL3/SDL_opengl.h>  
#include <iostream>
#include<Renderer.hpp>
#include <SDL3/SDL_keyboard.h>

class Application
{
public:
	Application(const char* title, int w, int h);
	void run();

	~Application();

private:
	bool InitGLad();
	bool InitSDL();
    void Cleanup();

	void Update();
	void Render();
	void ProcessInput(float	dt);

	bool isRunning = false;
	SDL_Event event;
	SDL_Window *window = nullptr;
	SDL_GLContext context = nullptr;
	Renderer* m_renderer = nullptr;

};

#endif // !APPLICATION_HPP

