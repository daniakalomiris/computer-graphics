#define GLEW_STATIC 1 // this allows linking with Static Library on Windows without DLL
#include <GL/glew.h> // include GLEW (OpenGL Extension Wrangler)

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context, initializing OpenGL and binding inputs

#include <glm/glm.hpp> // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>

#include "Olaf.h"

#include <iostream>

using namespace std;
using namespace glm;

Olaf::Olaf(int shaderProgram) {
    this->shaderProgram = shaderProgram;

    // initialize all of olaf's part using cube model
    this->leftFoot = new Cube(vec3(1.0f, 1.0f, 1.0f), shaderProgram);
    this->rightFoot = new Cube(vec3(1.0f, 1.0f, 1.0f), shaderProgram);
    this->lowerBody = new Cube(vec3(1.0f, 1.0f, 1.0f), shaderProgram);
    this->upperBody = new Cube(vec3(1.0f, 1.0f, 1.0f), shaderProgram);
    this->head = new Cube(vec3(1.0f, 1.0f, 1.0f), shaderProgram);
    this->leftHand = new Cube(vec3(1.0f, 1.0f, 1.0f), shaderProgram);
    this->rightHand = new Cube(vec3(1.0f, 1.0f, 1.0f), shaderProgram);
    this->nose = new Cube(vec3(1.0f, 0.65f, 0.0f), shaderProgram);
    this->leftEye = new Cube(vec3(0.0f, 0.0f, 0.0f), shaderProgram);
    this->rightEye = new Cube(vec3(0.0f, 0.0f, 0.0f), shaderProgram);
    this->hair = new Cube(vec3(0.0f, 0.0f, 0.0f), shaderProgram);
    
    // default transformations are zero matrices
    // the initial transformations are set in each part's draw() method
    this->initScale = vec3(0.0f, 0.0f, 0.0f);
    this->initTranslate = vec3(0.0f, 0.0f, 0.0f);
    this->initRotate = vec3(1.0f, 1.0f, 1.0f);
    this->initRotateAngle = 0.0f;
    
    // default render mode is triangles
    this->renderMode = GL_TRIANGLES;
}

Olaf::~Olaf() {
    delete leftFoot;
    delete rightFoot;
    delete lowerBody;
    delete upperBody;
    delete head;
    delete leftHand;
    delete rightHand;
    delete nose;
    delete leftEye;
    delete rightEye;
    delete hair;
}

// draws the entire olaf model
void Olaf::draw() {
    drawLeftFoot();
    drawRightFoot();
    drawLowerBody();
    drawUpperBody();
    drawHead();
    drawLeftHand();
    drawRightHand();
    drawNose();
    drawLeftEye();
    drawRightEye();
    drawHair();
}

// each part is set with initial transformations 
// any additional transformations made in the main game loop will change here
// when initRotate, initTranslate and initScale change

void Olaf::drawLeftFoot() {
    leftFoot->createVAO();
    leftFoot->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    leftFoot->setRotate(initRotateAngle, initRotate);
    leftFoot->setInitTranslate(vec3(-1.0f, 0.25f, 0.0f));
    leftFoot->setTranslate(initTranslate);
    leftFoot->setInitScale(vec3(1.0f, 0.5f, 0.5f));
    leftFoot->setScale(initScale);
    leftFoot->draw(renderMode);
}

void Olaf::drawRightFoot() {
    rightFoot->createVAO();
    rightFoot->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    rightFoot->setRotate(initRotateAngle, initRotate);
    rightFoot->setInitTranslate(vec3(1.0f, 0.25f, 0.0f));
    rightFoot->setTranslate(initTranslate);
    rightFoot->setInitScale(vec3(1.0f, 0.5f, 0.5f));
    rightFoot->setScale(initScale);
    rightFoot->draw(renderMode);
}

void Olaf::drawLowerBody() {
    lowerBody->createVAO();
    lowerBody->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    lowerBody->setRotate(initRotateAngle, initRotate);
    lowerBody->setInitTranslate(vec3(0.0f, 1.75f, 0.0f));
    lowerBody->setTranslate(initTranslate);
    lowerBody->setInitScale(vec3(3.5f, 2.5f, 1.0f));
    lowerBody->setScale(initScale);
    lowerBody->draw(renderMode);
}

void Olaf::drawUpperBody() {
    upperBody->createVAO();
    upperBody->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    upperBody->setRotate(initRotateAngle, initRotate);
    upperBody->setInitTranslate(vec3(0.0f, 3.75f, 0.0f));
    upperBody->setTranslate(initTranslate);
    upperBody->setInitScale(vec3(2.5f, 1.5f, 1.0f));
    upperBody->setScale(initScale);
    upperBody->draw(renderMode);
}

void Olaf::drawHead() {
    head->createVAO();
    head->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    head->setRotate(initRotateAngle, initRotate);
    head->setInitTranslate(vec3(0.0f, 5.00f, 0.0f));
    head->setTranslate(initTranslate);
    head->setInitScale(vec3(1.5f, 1.0f, 1.0f));
    head->setScale(initScale);
    head->draw(renderMode);
}
 
void Olaf::drawLeftHand() {
    leftHand->createVAO();
    leftHand->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    leftHand->setRotate(initRotateAngle, initRotate);
    leftHand->setInitTranslate(vec3(-2.0f, 3.75f, 0.0f));
    leftHand->setTranslate(initTranslate);
    leftHand->setInitScale(vec3(3.0f, 0.25f, 0.25f));
    leftHand->setScale(initScale);
    leftHand->draw(renderMode);
}

void Olaf::drawRightHand() {
    rightHand->createVAO();
    rightHand->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    rightHand->setRotate(initRotateAngle, initRotate);
    rightHand->setInitTranslate(vec3(2.0f, 3.75f, 0.0f));
    rightHand->setTranslate(initTranslate);
    rightHand->setInitScale(vec3(3.0f, 0.25f, 0.25f));
    rightHand->setScale(initScale);
    rightHand->draw(renderMode);
}

void Olaf::drawNose() {
    nose->createVAO();
    nose->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    nose->setRotate(initRotateAngle, initRotate);
    nose->setInitTranslate(vec3(0.0f, 5.00f, 0.5f));
    nose->setTranslate(initTranslate);
    nose->setInitScale(vec3(0.15f, 0.15f, 1.0f));
    nose->setScale(initScale);
    nose->draw(renderMode);
}

void Olaf::drawLeftEye() {
    leftEye->createVAO();
    leftEye->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    leftEye->setRotate(initRotateAngle, initRotate);
    leftEye->setInitTranslate(vec3(-0.4f, 5.25f, 0.5f));
    leftEye->setTranslate(initTranslate);
    leftEye->setInitScale(vec3(0.15f, 0.15f, 0.25f));
    leftEye->setScale(initScale);
    leftEye->draw(renderMode);
}

void Olaf::drawRightEye() {
    rightEye->createVAO();
    rightEye->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    rightEye->setRotate(initRotateAngle, initRotate);
    rightEye->setInitTranslate(vec3(0.4f, 5.25f, 0.5f));
    rightEye->setTranslate(initTranslate);
    rightEye->setInitScale(vec3(0.15f, 0.15f, 0.25f));
    rightEye->setScale(initScale);
    rightEye->draw(renderMode);
}

void Olaf::drawHair() {
    hair->createVAO();
    
    // draw middle hair
    hair->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    hair->setRotate(initRotateAngle, initRotate);
    hair->setInitTranslate(vec3(0.0f, 5.75f, 0.0f));
    hair->setTranslate(initTranslate);
    hair->setInitScale(vec3(0.05f, 1.0f, 0.05f));
    hair->setScale(initScale);
    hair->draw(renderMode);
    
    // draw left hair
    hair->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    hair->setRotate(initRotateAngle, initRotate);
    hair->setInitTranslate(vec3(-0.1f, 5.75f, 0.0f));
    hair->setTranslate(initTranslate);
    hair->setInitScale(vec3(0.05f, 1.0f, 0.05f));
    hair->setScale(initScale);
    hair->draw(renderMode);
    
    // draw right hair
    hair->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    hair->setRotate(initRotateAngle, initRotate);
    hair->setInitTranslate(vec3(0.1f, 5.75f, 0.0f));
    hair->setTranslate(initTranslate);
    hair->setInitScale(vec3(0.05f, 1.0f, 0.05f));
    hair->setScale(initScale);
    hair->draw(renderMode);
}

// set olaf rotation when world orientation changes
void Olaf::rotate(float angle, glm::vec3 rotate) {
    this->initRotateAngle = angle;
    this->initRotate = rotate;
}

// set olaf translation
void Olaf::translate(glm::vec3 translate) {
    this->initTranslate = translate;
}

// set olaf scaling
void Olaf::scale(glm::vec3 scale) {
    this->initScale = scale;
}

void Olaf::rotateSelf(bool self) {
    leftFoot->setRotateSelf(self);
    rightFoot->setRotateSelf(self);
    lowerBody->setRotateSelf(self);
    upperBody->setRotateSelf(self);
    head->setRotateSelf(self);
    leftHand->setRotateSelf(self);
    rightHand->setRotateSelf(self);
    nose->setRotateSelf(self);
    leftEye->setRotateSelf(self);
    rightEye->setRotateSelf(self);
    hair->setRotateSelf(self);
}

// get initial rotation vector
vec3 Olaf::getInitRotate() {
    return initRotate;
}

// get initial translation vector
vec3 Olaf::getInitTranslate() {
    return initTranslate;
}

// get intial scaling vector
vec3 Olaf::getInitScale() {
    return initScale;
}

// get initial rotation angle
float Olaf::getInitRotateAngle() {
    return initRotateAngle;
}

// sets render mode for cube models
void Olaf::setRenderMode(int renderMode) {
    this->renderMode = renderMode;
}

