#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

class Cube {
    public:
        Cube(glm::vec3 rgb, int shaderProgram);
        Cube(glm::vec3 rgb, int shaderProgram, const char* fileName);
        int createVAO();
        void draw(int renderMode);
        void setInitRotate(float angle, glm::vec3 rotate);
        void setInitTranslate(glm::vec3 translate);
        void setInitScale(glm::vec3 scale);
        void setRotate(float angle, glm::vec3 rotate);
        void setTranslate(glm::vec3 translate);
        void setScale(glm::vec3 scale);
        glm::vec3 getInitRotate();
        glm::vec3 getInitTranslate();
        glm::vec3 getInitScale();
        GLuint createTexture(const char* filename);
        void toggleTexture();
    private:
        glm::vec3 rgb;
        int shaderProgram;
        glm::mat4 initRotateM;
        glm::mat4 initTranslateM;
        glm::mat4 initScaleM;
        glm::mat4 modelWorldMatrix;
        glm::mat4 sourceMatrix;
        glm::mat4 updateMatrix;
        glm::vec3 initRotate;
        glm::vec3 initTranslate;
        glm::vec3 initScale;
        float initRotateAngle;
        bool isTextured;
        GLuint textureID;
        int vertexArrayObject;
        glm::vec3 vertexColor;
};
