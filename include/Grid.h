#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

class Grid {
    public:
        Grid(int shaderProgram);
        void draw();
        void rotate(float angle, glm::vec3 rotate);
    private:
        int shaderProgram;
        glm::vec3 initRotate;
        float initRotateAngle;
};
