#include "engine/convert.h"

namespace gl3 {
    rp3d::Vector3 convert::glm_to_rp3d(const glm::vec3& vec3)
    {
        rp3d::Vector3 rp3dVec;
        rp3dVec.x = vec3.x;
        rp3dVec.y = vec3.y;
        rp3dVec.z = vec3.z;

        return rp3dVec;
    }

    glm::vec3 convert::rp3d_to_glm(const rp3d::Vector3& Vector3)
    {
        glm::vec3 glmVec;
        glmVec.x = Vector3.x;
        glmVec.y = Vector3.y;
        glmVec.z = Vector3.z;

        return glmVec;
    }

    void convert::glm_normalize(glm::vec3& vec3)
    {
        rp3d::Vector3 _helper = glm_to_rp3d(vec3);
        _helper.normalize();
        vec3 = rp3d_to_glm(_helper);
    }

    float convert::rp3d_distance(rp3d::Vector3 firstPoint, rp3d::Vector3 secondPoint)
    {
        float distance;
        distance = sqrt(pow(firstPoint.x - secondPoint.x, 2) + pow(firstPoint.y - secondPoint.y, 2) + pow(firstPoint.z - secondPoint.z, 2));

        return distance;
    }
}