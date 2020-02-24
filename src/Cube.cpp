#define GLEW_STATIC 1 // this allows linking with Static Library on Windows without DLL
#include <GL/glew.h> // include GLEW (OpenGL Extension Wrangler)

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context, initializing OpenGL and binding inputs

#include <glm/glm.hpp> // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>

#include "Cube.h"

#include <iostream>

using namespace std;
using namespace glm;

Cube::Cube(vec3 rgb, int shaderProgram) {
    this->rgb = rgb;
    this->shaderProgram = shaderProgram;
    this->initRotateM = glm::mat4(1.0f);
    this->rotateSelf = false; // initialize rotations around world axis
}
 
int Cube::createVAO(){

    // positions are based off lab vertexArray
    // colors of each vertex is set when rgb value is assigned
    vec3 vertexArray[] = {  
        vec3(-0.5f,-0.5f,-0.5f), vec3(rgb.x, rgb.y, rgb.z), // left
        vec3(-0.5f,-0.5f, 0.5f), vec3(rgb.x, rgb.y, rgb.z),
        vec3(-0.5f, 0.5f, 0.5f), vec3(rgb.x, rgb.y, rgb.z),

        vec3(-0.5f,-0.5f,-0.5f), vec3(rgb.x, rgb.y, rgb.z),
        vec3(-0.5f, 0.5f, 0.5f), vec3(rgb.x, rgb.y, rgb.z),
        vec3(-0.5f, 0.5f,-0.5f), vec3(rgb.x, rgb.y, rgb.z),

        vec3( 0.5f, 0.5f,-0.5f), vec3(rgb.x, rgb.y, rgb.z), // far
        vec3(-0.5f,-0.5f,-0.5f), vec3(rgb.x, rgb.y, rgb.z),
        vec3(-0.5f, 0.5f,-0.5f), vec3(rgb.x, rgb.y, rgb.z),

        vec3( 0.5f, 0.5f,-0.5f), vec3(rgb.x, rgb.y, rgb.z),
        vec3( 0.5f,-0.5f,-0.5f), vec3(rgb.x, rgb.y, rgb.z),
        vec3(-0.5f,-0.5f,-0.5f), vec3(rgb.x, rgb.y, rgb.z),

        vec3( 0.5f,-0.5f, 0.5f), vec3(rgb.x, rgb.y, rgb.z), // bottom
        vec3(-0.5f,-0.5f,-0.5f), vec3(rgb.x, rgb.y, rgb.z),
        vec3( 0.5f,-0.5f,-0.5f), vec3(rgb.x, rgb.y, rgb.z),

        vec3( 0.5f,-0.5f, 0.5f), vec3(rgb.x, rgb.y, rgb.z),
        vec3(-0.5f,-0.5f, 0.5f), vec3(rgb.x, rgb.y, rgb.z),
        vec3(-0.5f,-0.5f,-0.5f), vec3(rgb.x, rgb.y, rgb.z),

        vec3(-0.5f, 0.5f, 0.5f), vec3(rgb.x, rgb.y, rgb.z), // near
        vec3(-0.5f,-0.5f, 0.5f), vec3(rgb.x, rgb.y, rgb.z),
        vec3( 0.5f,-0.5f, 0.5f), vec3(rgb.x, rgb.y, rgb.z),

        vec3( 0.5f, 0.5f, 0.5f), vec3(rgb.x, rgb.y, rgb.z),
        vec3(-0.5f, 0.5f, 0.5f), vec3(rgb.x, rgb.y, rgb.z),
        vec3( 0.5f,-0.5f, 0.5f), vec3(rgb.x, rgb.y, rgb.z),

        vec3( 0.5f, 0.5f, 0.5f), vec3(rgb.x, rgb.y, rgb.z), // right
        vec3( 0.5f,-0.5f,-0.5f), vec3(rgb.x, rgb.y, rgb.z),
        vec3( 0.5f, 0.5f,-0.5f), vec3(rgb.x, rgb.y, rgb.z),

        vec3( 0.5f,-0.5f,-0.5f), vec3(rgb.x, rgb.y, rgb.z),
        vec3( 0.5f, 0.5f, 0.5f), vec3(rgb.x, rgb.y, rgb.z),
        vec3( 0.5f,-0.5f, 0.5f), vec3(rgb.x, rgb.y, rgb.z),

        vec3( 0.5f, 0.5f, 0.5f), vec3(rgb.x, rgb.y, rgb.z), // top
        vec3( 0.5f, 0.5f,-0.5f), vec3(rgb.x, rgb.y, rgb.z),
        vec3(-0.5f, 0.5f,-0.5f), vec3(rgb.x, rgb.y, rgb.z),

        vec3( 0.5f, 0.5f, 0.5f), vec3(rgb.x, rgb.y, rgb.z),
        vec3(-0.5f, 0.5f,-0.5f), vec3(rgb.x, rgb.y, rgb.z),
        vec3(-0.5f, 0.5f, 0.5f), vec3(rgb.x, rgb.y, rgb.z)
    };

    // create a vertex array
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    // upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,                   // attribute 0 matches aPos in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        2*sizeof(vec3),      // stride - each vertex contain 2 vec3 (position, color)
        (void*)0             // array buffer offset
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,                   // attribute 1 matches aColor in Vertex Shader
        3,
        GL_FLOAT,
        GL_FALSE,
        2*sizeof(vec3),
        (void*)sizeof(vec3)  // color is offseted a vec3 (comes after position)
    );
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBindVertexArray(0);
    glBindVertexArray(vertexArrayObject);
    
    return vertexArrayObject;      
}

// draw cube model
void Cube::draw(int renderMode) {
    GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
    
    // order of transformations changes depending on if the rotation is happening around the world axis or object's axis
    if (rotateSelf) {
        modelWorldMatrix = initTranslateM * initRotateM * initScaleM;
    } 
    else {
        modelWorldMatrix = initRotateM * initTranslateM * initScaleM;
    }
    
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &modelWorldMatrix[0][0]);
    glDrawArrays(renderMode, 0, 36);
}

// initializing all transformation matrices
// each called once for each model
void Cube::setInitRotate(float angle, glm::vec3 rotate) {
    this->initRotateAngle = angle;
    this->initRotate = rotate;
    initRotateM = glm::rotate(glm::mat4(1.0f), radians(angle), rotate);
}

void Cube::setInitTranslate(glm::vec3 translate) {
    this->initTranslate = translate;
    initTranslateM = glm::translate(glm::mat4(1.0f), translate);
}

void Cube::setInitScale(glm::vec3 scale) {
    this->initScale = scale;
    initScaleM = glm::scale(glm::mat4(1.0f), scale);
}

// transformation multiply initial model world matrix
void Cube::setRotate(float angle, glm::vec3 rotate) {
    initRotateM = glm::rotate(glm::mat4(1.0f), radians(angle), rotate);
    this->initRotateAngle = angle;
    this->initRotate = rotate; 
}

void Cube::setTranslate(glm::vec3 translate) {
    initTranslateM = glm::translate(glm::mat4(1.0f), initTranslate + translate);
    this->initTranslate = translate;
}

void Cube::setScale(glm::vec3 scale) {
    initScaleM = glm::scale(glm::mat4(1.0f), initScale + scale);
    this->initScale = scale;
}

// get initial transformation vectors
vec3 Cube::getInitRotate() {
    return this->initRotate;
}

vec3 Cube::getInitTranslate() {
    return this->initTranslate;
}

vec3 Cube::getInitScale() {
    return this->initScale;
}

void Cube::setRotateSelf(bool rotateSelf) {
    this->rotateSelf = rotateSelf;
}