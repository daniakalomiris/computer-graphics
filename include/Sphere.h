#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

class Sphere {
    public:
        Sphere(glm::vec3 rgb, int shaderProgram);
        Sphere(glm::vec3 rgb, int shaderProgram, const char* fileName);
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
        void setShinyMaterial();
        void moveForward();
        void moveBackward();
        GLboolean getIsMovingForward();
        GLboolean getIsMovingBackward();
        void setMoveRotate(float angle, glm::vec3 rotate);
    private:
        struct Vertex {
            glm::vec3 position;
            glm::vec3 normal;
            glm::vec3 color;
        };
        unsigned int mVAO;
        unsigned int mVBO;
        unsigned int numOfVertices;
        glm::vec3 rgb;
        int shaderProgram;
        glm::mat4 modelWorldMatrix = glm::mat4(1.0f);
        glm::mat4 initRotateM;
        glm::mat4 initTranslateM;
        glm::mat4 initScaleM;
        glm::vec3 initRotate;
        glm::vec3 initTranslate;
        glm::vec3 initScale;
        float initRotateAngle;
        bool isTextured;
        GLuint textureID;
        glm::vec3 vertexColor;
        GLboolean isMovingForward;
        GLboolean isMovingBackward;
        glm::vec3 movementRotate;
        float movementAngle;
        glm::mat4 moveRotateM;
};
