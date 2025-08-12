#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <glm/glm.hpp>
#include <SDL3/SDL.h>
#include <Shader.hpp>
#include <Mesh.hpp>
#include <Camera.hpp>
class Renderer{
   public:
   void BeginFrame(const glm::vec4& clearColor);
   void EndFrame(SDL_Window*	window);

   void DrawMesh(const Mesh& mesh, const Shader& shader, const glm::mat4& model);
   void SetCamera(Camera& camera);
   Camera m_cam;

   private:
};
#endif