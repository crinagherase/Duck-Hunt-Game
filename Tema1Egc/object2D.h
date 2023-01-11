#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{
    Mesh* DrawCircle(const std::string &name, int triangles);
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string &name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill);
    Mesh* CreateTriangle(const std::string &name, glm::vec3 node1, glm::vec3 node2, glm::vec3 node3, glm::vec3 color, bool fill = true);
}
