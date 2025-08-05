#ifndef APPLICATION_HPP
#define  APPLICATION_HPP

#include <SDL3/SDL.h>
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
	void ProcessInput();

	bool isRunning = false;
	SDL_Event event;
	SDL_Window *window = nullptr;
	SDL_GLContext context = nullptr;

};

#endif // !APPLICATION_HPP

