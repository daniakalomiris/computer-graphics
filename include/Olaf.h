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
        void drawLowerHat();
        void drawUpperHat();
        void drawUpperScarf();
        void drawLowerScarf();
        void drawButton();
        void rotate(float angle, glm::vec3 rotate);
        void translate(glm::vec3 translate);
        void scale(glm::vec3 scale);
        glm::vec3 getInitRotate();
        glm::vec3 getInitTranslate();
        glm::vec3 getInitScale();
        float getInitRotateAngle();
        void setRenderMode(int renderMode);
        void toggleTexture();
        void walkForward();
        void walkBackward();
    private:
        int shaderProgram;
        glm::vec3 rgb;
        Sphere* leftFoot;
        Sphere* rightFoot;
        Sphere* lowerBody;
        Sphere* upperBody;
        Sphere* head;
        Sphere* leftHand;
        Sphere* rightHand;
        Cube* nose;
        Sphere* leftEye;
        Sphere* rightEye;
        Sphere* lowerHat;
        Sphere* upperHat;
        Sphere* upperScarf;
        Sphere* lowerScarf;
        Sphere* button;
        glm::vec3 initRotate;
        glm::vec3 initTranslate;
        glm::vec3 initScale;
        float initRotateAngle;
        int renderMode;
        glm::mat4 modelWorldMatrix;
        glm::vec3 movementRotate;
        float movementAngle;
};
