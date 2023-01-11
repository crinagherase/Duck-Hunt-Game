#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* object2D::DrawCircle(const std::string &name, int triangles){
    std::vector<VertexFormat> vertices;
    GLfloat arg;
    bool fill = true;
    int num_segments = triangles * 3;
    std::vector<unsigned int> indices;
    vertices.emplace_back(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    for (GLshort i = 0; i < num_segments; i++) {
        arg = i * 2 * M_PI / num_segments ;
        vertices.emplace_back(glm::vec3(cos(arg), sin(arg), 0), glm::vec3(0.01f, 0.34f, 0.22f));
        indices.push_back(i);
    }
    indices.push_back(num_segments);
    indices.push_back(1);
    Mesh* circle = new Mesh(name);
    circle->InitFromData(vertices, indices);
    return circle;
}
Mesh* object2D::CreateTriangle(
        const std::string &name,
        glm::vec3 node1,
        glm::vec3 node2,
        glm::vec3 node3,
        glm::vec3 color,
        bool fill)
{
    std::vector<VertexFormat> vertices =
            {
                    VertexFormat(node1, color),
                    VertexFormat(node2, color),
                    VertexFormat(node3, color)
            };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        //indices.push_back(0);
        //indices.push_back(2);
    }

    triangle->InitFromData(vertices, indices);
    return triangle;
}
Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}
Mesh* object2D::CreateRectangle(
        const std::string &name,
        glm::vec3 leftBottomCorner,
        float width,
        float height,
        glm::vec3 color,
        bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
            {
                    VertexFormat(corner, color),
                    VertexFormat(corner + glm::vec3(width, 0, 0), color),
                    VertexFormat(corner + glm::vec3(width, height, 0), color),
                    VertexFormat(corner + glm::vec3(0, height, 0), color)
            };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}
