#ifndef MESH_HPP
#define MESH_HPP
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textCoord;
};

class Mesh{
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
        ~Mesh();
        void draw() const;
    private:
        void setupMesh();
        GLuint vao = 0, vbo = 0, ebo = 0;
        const std::vector<Vertex> m_vertices;
        const std::vector<uint32_t> m_indices;
};

#endif