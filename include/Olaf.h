#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

#include "Cube.h"
#include "Sphere.h"

class Olaf {
    public:
        Olaf(int shaderProgram);
        ~Olaf();
        void draw();
        void drawLeftFoot();
        void drawRightFoot();
        void drawLowerBody();
        void drawUpperBody();
        void drawHead();
        void drawLeftHand();
        void drawRightHand();
        void drawNose();
        void drawLeftEye();
        void drawRightEye();
        void drawHair();
        void rotate(float angle, glm::vec3 rotate);
        void translate(glm::vec3 translate);
        void scale(glm::vec3 scale);
        void rotateSelf(bool self);
        glm::vec3 getInitRotate();
        glm::vec3 getInitTranslate();
        glm::vec3 getInitScale();
        float getInitRotateAngle();
        void setRenderMode(int renderMode);
    private:
        int shaderProgram;
        glm::vec3 rgb;
        Cube* leftFoot;
        Cube* rightFoot;
        Cube* lowerBody;
        Cube* upperBody;
        Cube* head;
        Cube* leftHand;
        Cube* rightHand;
        Cube* nose;
        Cube* leftEye;
        Cube* rightEye;
        Cube* hair;
        glm::vec3 initRotate;
        glm::vec3 initTranslate;
        glm::vec3 initScale;
        float initRotateAngle;
        int renderMode;
};
