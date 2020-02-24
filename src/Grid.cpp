#define GLEW_STATIC 1 // this allows linking with Static Library on Windows without DLL
#include <GL/glew.h> // include GLEW (OpenGL Extension Wrangler)

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context, initializing OpenGL and binding inputs

#include <glm/glm.hpp> // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>

#include "Grid.h"

#include <iostream>

using namespace std;
using namespace glm;

Grid::Grid(int shaderProgram) {
    this->shaderProgram = shaderProgram;
    this->initRotate = vec3(1.0f, 1.0f, 1.0f);
    this->initRotateAngle = 0.0f;
}

void Grid::draw(){

    //grid model
	vec3 vertexArray[] = {
        vec3(1,0,0), vec3(1.0f, 1.0f, 0.0f), // yellow
        vec3(-1,0,0), vec3(1.0f, 1.0f, 0.0f) // yellow
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
		2*sizeof(vec3), 	 // stride - each vertex contain 2 vec3 (position, color)
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
    
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
    glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
    glBindVertexArray(vertexArrayObject);
 
    GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");

    mat4 gridWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &gridWorldMatrix[0][0]);

    // becasue camera will be pointing to world space origin, we must render 50 lines in both directions on one side of +z axis and 50 lines in both directions on one side of -z axis
    for (int i = 0; i <= 50; i++) {
		gridWorldMatrix = glm::rotate(mat4(1.0f), radians(initRotateAngle), initRotate) * translate(mat4(1.0f), vec3(0.0f, 0.0f, i * 1.0f)) * scale(mat4(1.0f), vec3(50.0f, 0.0f, 0.0f)); // scaling to 50 since we are
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &gridWorldMatrix[0][0]);
		glDrawArrays(GL_LINES, 0, 2);
    }
    
    for (int i = 0; i <= 50; i++) {
		gridWorldMatrix = glm::rotate(mat4(1.0f), radians(initRotateAngle), initRotate) * translate(mat4(1.0f), vec3(0.0f, 0.0f, -i * 1.0f)) * scale(mat4(1.0f), vec3(50.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &gridWorldMatrix[0][0]);
		glDrawArrays(GL_LINES, 0, 2);
    }
    
    // rotate vertices 90 degrees
    gridWorldMatrix = glm::rotate(mat4(1.0f), radians(initRotateAngle), initRotate) * glm::rotate(mat4(1.0f), radians(90.0f), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(50.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &gridWorldMatrix[0][0]);

    for (int i = 0; i <= 50; i++) {
		gridWorldMatrix = glm::rotate(mat4(1.0f), radians(initRotateAngle), initRotate) * glm::rotate(mat4(1.0f), radians(90.0f), vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), vec3(0.0, 0.0f, i * 1.0f)) * scale(mat4(1.0f), vec3(50.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &gridWorldMatrix[0][0]);
		glDrawArrays(GL_LINES, 0, 2);
    }
    
    for (int i = 0; i <= 50; i++) {
		gridWorldMatrix = glm::rotate(mat4(1.0f), radians(initRotateAngle), initRotate) * glm::rotate(mat4(1.0f), radians(90.0f), vec3(0.0, 1.0, 0.0)) * translate(mat4(1.0f), vec3(0.0, 0.0f, -i * 1.0f)) * scale(mat4(1.0f), vec3(50.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &gridWorldMatrix[0][0]);
		glDrawArrays(GL_LINES, 0, 2);
    }
}

void Grid::rotate(float angle, glm::vec3 rotate) {
    this->initRotateAngle = angle;
    this->initRotate = rotate;
}
