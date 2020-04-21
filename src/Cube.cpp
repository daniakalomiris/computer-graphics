#define GLEW_STATIC 1 // this allows linking with Static Library on Windows without DLL
#include <GL/glew.h> // include GLEW (OpenGL Extension Wrangler)

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context, initializing OpenGL and binding inputs

#include <glm/glm.hpp> // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>

#include "Cube.h"

#include "stb_image.h"

#include <iostream>

using namespace std;
using namespace glm;


// credited to lab code
struct TexturedColoredVertex {
    TexturedColoredVertex(vec3 _position, vec3 _normal, vec2 _uv)
    : position(_position), normal(_normal), uv(_uv) {}
    
    vec3 position;
    vec3 normal;
    vec2 uv;
};

Cube::Cube(vec3 rgb, int shaderProgram) {
    this->rgb = rgb;
    this->shaderProgram = shaderProgram;
    this->initRotateM = glm::mat4(1.0f);
    this->modelWorldMatrix = glm::mat4(1.0f);
    this->isTextured = false; // initialize without texture
    this->vertexArrayObject = createVAO();
}

Cube::Cube(vec3 rgb, int shaderProgram, const char* fileName) {
    this->rgb = rgb;
    this->shaderProgram = shaderProgram;
    this->initRotateM = glm::mat4(1.0f);
    this->modelWorldMatrix = glm::mat4(1.0f);
    this->isTextured = true;
    this->textureID = createTexture(fileName);
    this->vertexArrayObject = createVAO();
}

int Cube::createVAO(){
    const TexturedColoredVertex texturedCubeVertexArray[] = {
        
        TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)), //left - red
        TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)),
        TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)),
        
        TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)),
        TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)),
        TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)),
        
        TexturedColoredVertex(vec3( 0.5f, 0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)), // far - blue
        TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)),
        TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)),
        
        TexturedColoredVertex(vec3( 0.5f, 0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)),
        TexturedColoredVertex(vec3( 0.5f,-0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)),
        TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)),
        
        TexturedColoredVertex(vec3( 0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)), // bottom - turquoise
        TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f)),
        TexturedColoredVertex(vec3( 0.5f,-0.5f,-0.5f), vec3(0.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f)),
        
        TexturedColoredVertex(vec3( 0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)),
        TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f)),
        TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f)),
        
        TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)), // near - green
        TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)),
        TexturedColoredVertex(vec3( 0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)),
        
        TexturedColoredVertex(vec3( 0.5f, 0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)),
        TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)),
        TexturedColoredVertex(vec3( 0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)),
        
        TexturedColoredVertex(vec3( 0.5f, 0.5f, 0.5f), vec3(1.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)), // right - purple
        TexturedColoredVertex(vec3( 0.5f,-0.5f,-0.5f), vec3(1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)),
        TexturedColoredVertex(vec3( 0.5f, 0.5f,-0.5f), vec3(1.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)),
        
        TexturedColoredVertex(vec3( 0.5f,-0.5f,-0.5f), vec3(1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)),
        TexturedColoredVertex(vec3( 0.5f, 0.5f, 0.5f), vec3(1.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)),
        TexturedColoredVertex(vec3( 0.5f,-0.5f, 0.5f), vec3(1.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)),
        
        TexturedColoredVertex(vec3( 0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)), // top - yellow
        TexturedColoredVertex(vec3( 0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)),
        TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)),
        
        TexturedColoredVertex(vec3( 0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)),
        TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)),
        TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f))
    };
        
    // create a vertex array
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
        

    // upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texturedCubeVertexArray), texturedCubeVertexArray, GL_STATIC_DRAW);
             
    glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
                          3,                   // size
                          GL_FLOAT,            // type
                          GL_FALSE,            // normalized?
                          sizeof(TexturedColoredVertex), // stride - each vertex contain 2 vec3 (position, color)
                          (void*)0             // array buffer offset
                          );
    glEnableVertexAttribArray(0);
    
    
    glVertexAttribPointer(2,                            // attribute 2 matches aUV in Vertex Shader
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(TexturedColoredVertex),
                          (void*)(2*sizeof(vec3))      // uv is offseted by 2 vec3 (comes after position and color)
                          );
    glEnableVertexAttribArray(2);
    
    glVertexAttribPointer(3,                   // attribute 0 matches aPos in Vertex Shader
                          3,                   // size
                          GL_FLOAT,            // type
                          GL_FALSE,            // normalized?
                          sizeof(TexturedColoredVertex), // stride - each vertex contain 2 vec3 (position, color)
                          (void*)0             // array buffer offset
                          );
    glEnableVertexAttribArray(3);
    
    return vertexArrayObject;      
}

GLuint Cube::createTexture(const char* fileName) {
     // Step1 Create and bind textures
      GLuint textureId = 0;
      glGenTextures(1, &textureId);
      assert(textureId != 0);

      glBindTexture(GL_TEXTURE_2D, textureId);

      // Step2 Set filter parameters
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      // Step3 Load Textures with dimension data
      int width, height, nrChannels;
      unsigned char *data = stbi_load(fileName, &width, &height, &nrChannels, 0);
      if (!data)
      {
        std::cerr << "Error::Texture could not load texture file:" << fileName << std::endl;
        return 0;
      }

      // Step4 Upload the texture to the PU
      GLenum format = 0;
      if (nrChannels == 1)
          format = GL_RED;
      else if (nrChannels == 3)
          format = GL_RGB;
      else if (nrChannels == 4)
          format = GL_RGBA;
      glTexImage2D(GL_TEXTURE_2D, 0, format, width, height,
                   0, format, GL_UNSIGNED_BYTE, data);

      // Step5 Free resources
      stbi_image_free(data);
      glBindTexture(GL_TEXTURE_2D, 0);
      return textureId;
}


void Cube::toggleTexture() {
    isTextured = !isTextured;
}

// draw cube model
void Cube::draw(int renderMode) {
    
    // load textures
    if (isTextured) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        GLuint textureLocation = glGetUniformLocation(shaderProgram, "textureSampler");
        glUniform1i(textureLocation, 0);                // Set our Texture sampler to user Texture Unit 0
        glUniform1i(textureLocation, true);
    }
    
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
    glUniform3f(vertexColorLocation, rgb.x, rgb.y, rgb.z);
 
    GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
    modelWorldMatrix = initRotateM * initTranslateM * initScaleM;
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
