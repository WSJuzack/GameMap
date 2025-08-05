#pragma once

#include "reactphysics3d/reactphysics3d.h"
#include "glm/glm.hpp"

namespace gl3 {

    class convert {
    public:
        static rp3d::Vector3 glm_to_rp3d(const glm::vec3& vec3);
        static glm::vec3 rp3d_to_glm(const rp3d::Vector3& Vector3);
        static void glm_normalize(glm::vec3& vec3);
        static float rp3d_distance(rp3d::Vector3 firstPoint, rp3d::Vector3 secondPoint);
    private:

    };
}