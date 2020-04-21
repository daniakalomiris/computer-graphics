#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

#include <GL/glew.h>

#include "Cube.h"

class Ground {
    public:
        Ground(int shaderProgram);
        Ground(int shaderProgram, const char* fileName);
        void draw();
        void rotate(float angle, glm::vec3 rotate);
        void createTexture(const char* filename);
        void toggleTexture();
    private:
        int shaderProgram;
        glm::vec3 initRotate;
        float initRotateAngle;
        bool isTextured;
        GLuint textureID;
        Cube* floor;
        int renderMode;
};
