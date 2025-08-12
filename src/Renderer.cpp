#include <Renderer.hpp>


void Renderer::DrawMesh(const Mesh& mesh,const Shader& shader, const glm::mat4& model) {
	shader.use();
    std::string names[3] = {
    "model","view","projection"
    };
    shader.setMat4(names[0], model);
    shader.setMat4(names[1], m_cam.GetViewMatrix());
    shader.setMat4(names[2], m_cam.GetProjectionMatrix(1.0f));
    mesh.draw();
}
void Renderer::BeginFrame(const glm::vec4& clearColor) {
    glClearColor(clearColor.r,clearColor.g,clearColor.b,clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}
void Renderer::EndFrame(SDL_Window* window) {
    SDL_GL_SwapWindow(window);
}
void    Renderer::SetCamera(Camera& cam) {
    m_cam = cam;
}