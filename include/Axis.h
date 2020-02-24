#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

#include "Cube.h"

class Axis {
    public:
        Axis(int shaderProgram);
        ~Axis();
        void draw();
        void drawX();
        void drawY();
        void drawZ();
        void rotate(float angle, glm::vec3 rotate);
    private:
        int shaderProgram;
        Cube* x;
        Cube* y;
        Cube* z;
        glm::vec3 initRotate;
        float initRotateAngle;
};
