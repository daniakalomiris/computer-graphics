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
    this->leftFoot = new Sphere(vec3(1.0f, 1.0f, 1.0f), shaderProgram);
    this->rightFoot = new Sphere(vec3(1.0f, 1.0f, 1.0f), shaderProgram);
    this->lowerBody = new Sphere(vec3(1.0f, 1.0f, 1.0f), shaderProgram);
    this->upperBody = new Sphere(vec3(1.0f, 1.0f, 1.0f), shaderProgram);
    this->head = new Sphere(vec3(1.0f, 1.0f, 1.0f), shaderProgram);
    this->leftHand = new Sphere(vec3(1.0f, 1.0f, 1.0f), shaderProgram);
    this->rightHand = new Sphere(vec3(1.0f, 1.0f, 1.0f), shaderProgram);
    this->nose = new Cube(vec3(0.0f, 0.0f, 0.0f), shaderProgram, "carrot.jpg");
    this->leftEye = new Sphere(vec3(0.5f, 0.3f, 0.0f), shaderProgram);
    this->rightEye = new Sphere(vec3(0.5f, 0.3f, 0.0f), shaderProgram);
    this->lowerHat = new Sphere(vec3(0.55f, 0.55f, 0.55f), shaderProgram);
    this->upperHat = new Sphere(vec3(0.55f, 0.55f, 0.55f), shaderProgram);
    this->upperScarf = new Sphere(vec3(1.0f, 0.0f, 0.0f), shaderProgram);
    this->lowerScarf = new Sphere(vec3(1.0f, 0.0f, 0.0f), shaderProgram);
    this->button = new Sphere(vec3(0.0f, 0.0f, 0.0f), shaderProgram);
  
    this->modelWorldMatrix = glm::mat4(1.0f);

    // default transformations are zero matrices
    // the initial transformations are set in each part's draw() method
    this->initScale = vec3(0.0f, 0.0f, 0.0f);
    this->initTranslate = vec3(0.0f, 0.0f, 0.0f);
    this->initRotate = vec3(1.0f, 1.0f, 1.0f);
    this->initRotateAngle = 0.0f;

    // default render mode is triangles
    this->renderMode = GL_TRIANGLES;
    
    this->movementAngle = 0.1f;
    this->movementRotate = vec3(0.0f, 1.0f, 0.0f);
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
    delete lowerHat;
    delete upperHat;
    delete upperScarf;
    delete button;
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
    drawLowerHat();
    drawUpperHat();
    drawUpperScarf();
    drawLowerScarf();
    drawButton();
}

// each part is set with initial transformations 
// any additional transformations made in the main game loop will change here
// when initRotate, initTranslate and initScale change

void Olaf::drawLeftFoot() {
    leftFoot->createVAO();
    leftFoot->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    leftFoot->setInitTranslate(vec3(-1.0f, 0.25f, 0.0f));
    leftFoot->setTranslate(initTranslate);
    leftFoot->setInitScale(vec3(0.75f, 0.25f, 0.5f));
    leftFoot->setScale(initScale);
    
    // only rotate if it is walking
      if (leftFoot->getIsMovingSelf()) {
          leftFoot->setMoveRotate(movementAngle, movementRotate);
      } else {
          leftFoot->setRotate(initRotateAngle, initRotate);

      }
    
    leftFoot->draw(renderMode);
}

void Olaf::drawRightFoot() {
    rightFoot->createVAO();
    rightFoot->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    rightFoot->setRotate(initRotateAngle, initRotate);
    rightFoot->setInitTranslate(vec3(1.0f, 0.25f, 0.0f));
    rightFoot->setTranslate(initTranslate);
    rightFoot->setInitScale(vec3(0.75f, 0.25f, 0.5f));
    rightFoot->setScale(initScale);
    rightFoot->draw(renderMode);
}

void Olaf::drawLowerBody() {
    lowerBody->createVAO();
    lowerBody->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    lowerBody->setRotate(initRotateAngle, initRotate);
    lowerBody->setInitTranslate(vec3(0.0f, 1.60f, 0.0f));
    lowerBody->setTranslate(initTranslate);
    lowerBody->setInitScale(vec3(1.5f, 1.5f, 1.5f));
    lowerBody->setScale(initScale);
    lowerBody->draw(renderMode);
}

void Olaf::drawUpperBody() {
    upperBody->createVAO();
    upperBody->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    upperBody->setRotate(initRotateAngle, initRotate);
    upperBody->setInitTranslate(vec3(0.0f, 3.50f, 0.0f));
    upperBody->setTranslate(initTranslate);
    upperBody->setInitScale(vec3(1.15f, 1.15f, 1.15f));
    upperBody->setScale(initScale);
    upperBody->draw(renderMode);
}

void Olaf::drawHead() {
    head->createVAO();
    head->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    head->setRotate(initRotateAngle, initRotate);
    head->setInitTranslate(vec3(0.0f, 5.00f, 0.0f));
    head->setTranslate(initTranslate);
    head->setInitScale(vec3(1.0f, 1.0f, 1.0f));
    head->setScale(initScale);
    head->draw(renderMode);
}
 
void Olaf::drawLeftHand() {
    leftHand->createVAO();
    leftHand->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    leftHand->setRotate(initRotateAngle, initRotate);
    leftHand->setInitTranslate(vec3(-1.5f, 3.75f, 0.0f));
    leftHand->setTranslate(initTranslate);
    leftHand->setInitScale(vec3(2.0f, 0.25f, 0.25f));
    leftHand->setScale(initScale);
    leftHand->draw(renderMode);
}

void Olaf::drawRightHand() {
    rightHand->createVAO();
    rightHand->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    rightHand->setRotate(initRotateAngle, initRotate);
    rightHand->setInitTranslate(vec3(1.5f, 3.75f, 0.0f));
    rightHand->setTranslate(initTranslate);
    rightHand->setInitScale(vec3(2.0f, 0.25f, 0.25f));
    rightHand->setScale(initScale);
    rightHand->draw(renderMode);
}

void Olaf::drawNose() {
    nose->createVAO();
    nose->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    nose->setRotate(initRotateAngle, initRotate);
    nose->setInitTranslate(vec3(0.0f, 5.00f, 1.0f));
    nose->setTranslate(initTranslate);
    nose->setInitScale(vec3(0.15f, 0.15f, 0.35f));
    nose->setScale(initScale);
    nose->draw(renderMode);
}

void Olaf::drawLeftEye() {
    leftEye->createVAO();
    leftEye->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    leftEye->setRotate(initRotateAngle, initRotate);
    leftEye->setInitTranslate(vec3(-0.4f, 5.25f, 0.9f));
    leftEye->setTranslate(initTranslate);
    leftEye->setInitScale(vec3(0.10f, 0.10f, 0.10f));
    leftEye->setScale(initScale);
    leftEye->draw(renderMode);
}

void Olaf::drawRightEye() {
    rightEye->createVAO();
    rightEye->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    rightEye->setRotate(initRotateAngle, initRotate);
    rightEye->setInitTranslate(vec3(0.4f, 5.25f, 0.9f));
    rightEye->setTranslate(initTranslate);
    rightEye->setInitScale(vec3(0.10f, 0.10f, 0.10f));
    rightEye->setScale(initScale);
    rightEye->draw(renderMode);
}

void Olaf::drawLowerHat() {
    lowerHat->createVAO();
    lowerHat->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    lowerHat->setRotate(initRotateAngle, initRotate);
    lowerHat->setInitTranslate(vec3(0.0f, 5.75f, 0.0f));
    lowerHat->setTranslate(initTranslate);
    lowerHat->setInitScale(vec3(1.1f, 0.25f, 1.1f));
    lowerHat->setScale(initScale);
    lowerHat->draw(renderMode);
}

void Olaf::drawUpperHat() {
    upperHat->createVAO();
    upperHat->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    upperHat->setRotate(initRotateAngle, initRotate);
    upperHat->setInitTranslate(vec3(0.0f, 6.25f, 0.0f));
    upperHat->setTranslate(initTranslate);
    upperHat->setInitScale(vec3(0.75f, 0.55f, 0.75f));
    upperHat->setScale(initScale);
    upperHat->draw(renderMode);
}

void Olaf::drawUpperScarf() {
    upperScarf->createVAO();
    upperScarf->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    upperScarf->setRotate(initRotateAngle, initRotate);
    upperScarf->setInitTranslate(vec3(0.0f, 4.5f, 0.0f));
    upperScarf->setTranslate(initTranslate);
    upperScarf->setInitScale(vec3(1.25f, 0.25f, 1.25f));
    upperScarf->setScale(initScale);
    upperScarf->draw(renderMode);
}

void Olaf::drawLowerScarf() {
    lowerScarf->createVAO();
    lowerScarf->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    lowerScarf->setRotate(initRotateAngle, initRotate);
    lowerScarf->setInitTranslate(vec3(-0.45f, 4.0f, 0.9f));
    lowerScarf->setTranslate(initTranslate);
    lowerScarf->setInitScale(vec3(0.20f, 0.55f, 0.20f));
    lowerScarf->setScale(initScale);
    lowerScarf->draw(renderMode);
}

void Olaf::drawButton() {
    button->createVAO();
    
    // top button
    button->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    button->setRotate(initRotateAngle, initRotate);
    button->setInitTranslate(vec3(0.0f, 3.8f, 1.1f));
    button->setTranslate(initTranslate);
    button->setInitScale(vec3(0.10f, 0.10f, 0.10f));
    button->setScale(initScale);
    button->draw(renderMode);
    
    // bottom button
    button->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    button->setRotate(initRotateAngle, initRotate);
    button->setInitTranslate(vec3(0.0f, 3.25f, 1.1f));
    button->setTranslate(initTranslate);
    button->setInitScale(vec3(0.10f, 0.10f, 0.10f));
    button->setScale(initScale);
    button->draw(renderMode);
}

// these transformations each correspond to a group matrix (initRotate, initTranslate and initScale)

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

// toggles texture on/off for models that use textures
void Olaf::toggleTexture() {
    this->nose->toggleTexture();
    this->lowerHat->toggleTexture();
    this->upperHat->toggleTexture();
}

// olaf animation movements when walking forward and backward
// legs and arms move for each type of movement
void Olaf::walk() {
    this->leftFoot->moveSelf();
    this->rightFoot->moveSelf();
}

