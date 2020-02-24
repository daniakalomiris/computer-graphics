#define GLEW_STATIC 1 // this allows linking with Static Library on Windows without DLL
#include <GL/glew.h> // include GLEW (OpenGL Extension Wrangler)

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context, initializing OpenGL and binding inputs

#include <glm/glm.hpp> // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>

#include "Axis.h"
#include "Cube.h"

#include <iostream>

using namespace std;
using namespace glm;

Axis::Axis(int shaderProgram) {
    this->shaderProgram = shaderProgram;

    // initialize all three axis using cube model
    this->x = new Cube(vec3(1.0f, 0.0f, 0.0f), shaderProgram);
    this->y = new Cube(vec3(0.0f, 1.0f, 0.0f), shaderProgram);
    this->z = new Cube(vec3(0.0f, 0.0f, 1.0f), shaderProgram);
}

Axis::~Axis() {
    delete x;
    delete y;
    delete z;
}

// draws the entire axis model
void Axis::draw() {
    this->drawX();
    this->drawY();
    this->drawZ();
}

void Axis::drawX() {
    x->createVAO();
    x->setInitRotate(-90.0f, vec3(0.0f, 0.0f, 1.0f));
    x->setInitTranslate(vec3(-0.05f, 2.5f, 0.0f));
    x->setInitScale(vec3(0.1f, 5.0f, 0.1f));
    x->draw(GL_TRIANGLES);
}

void Axis::drawY() {
    y->createVAO();
    y->setInitRotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
    y->setInitTranslate(vec3(0.0f, 2.5f, 0.05f));
    y->setInitScale(vec3(0.1f, 5.0f, 0.1f));
    y->draw(GL_TRIANGLES);
}

void Axis::drawZ() {
    z->createVAO();
    z->setInitRotate(90.0f, vec3(0.0f, 1.0f, 0.0f));
    z->setRotate(90.0f, vec3(1.0f, 0.0f, 0.0f));
    z->setInitTranslate(vec3(0.05f, 2.5f, 0.0f));
    z->setInitScale(vec3(0.1f, 5.0f, 0.1f));
    z->draw(GL_TRIANGLES);
}

// set axis rotation when world orientation changes
void Axis::rotate(float angle, glm::vec3 rotate) {
    this->initRotateAngle = angle;
    this->initRotate = rotate;
}
