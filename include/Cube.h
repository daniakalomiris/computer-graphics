#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

class Cube {
    public:
        Cube(glm::vec3 rgb, int shaderProgram);
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
        void setRotateSelf(bool rotateSelf);
    private:
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
        bool rotateSelf;
};
