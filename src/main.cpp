#include <iostream>

#define GLEW_STATIC 1 // this allows linking with Static Library on Windows without DLL
#include <GL/glew.h> // include GLEW (OpenGL Extension Wrangler)

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context, initializing OpenGL and binding inputs

#include <glm/glm.hpp> // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>

#include "Grid.h"
#include "Axis.h"
#include "Olaf.h"

#include <string>
#include <fstream>
#include <random>

using namespace glm;
using namespace std;

// window settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
 
// this callback function executes when the window size changes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// callback function for key input
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

// this code is credited to www.opengl-tutorial.org
GLuint loadShaders(std::string vertex_shader_path, std::string fragment_shader_path) {
    // create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // read the vertex shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_shader_path, std::ios::in);
    if (VertexShaderStream.is_open()) {
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    } else {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_shader_path.c_str());
        getchar();
        exit(-1);
    }

    // read the fragment shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_shader_path, std::ios::in);
    if (FragmentShaderStream.is_open()) {
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // compile vertex shader
    printf("Compiling shader : %s\n", vertex_shader_path.c_str());
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
    glCompileShader(VertexShaderID);

    // check vertex shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // compile fragment shader
    printf("Compiling shader : %s\n", fragment_shader_path.c_str());
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
    glCompileShader(FragmentShaderID);

    // check fragment shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    // link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

int main () {
    
    // initialize and configure glfw
    glfwInit();
    
    #if defined(PLATFORM_OSX)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // specific version 3.2
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // specify use of core-profile
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // needed for macOS
    #else
        // on windows, we set OpenGL version to 2.1 to support more hardware
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    #endif
    
    // create window object
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "COMP 371 - Assignment 1", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // GLFW calls this function on every window resize
    
    // disable mouse cursor after creating window
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // initialize GLEW
    glewExperimental = true; // needed for core-profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glClearColor(0.14f, 0.21f, 0.21f, 0.0f); // background color

    // compile and link shaders here
    #if defined(PLATFORM_OSX)
        std::string shaderPathPrefix = "";
    #else
        std::string shaderPathPrefix = "../shaders/";
    #endif
    
    int commonShaderProgram = loadShaders(shaderPathPrefix + "common.vertexshader", shaderPathPrefix + "common.fragmentshader");
    
    glUseProgram(commonShaderProgram);

    // camera parameters for view transform at origin
    vec3 cameraPosition(0.0f, 5.0f, 20.0f);
    vec3 cameraLookAt(0.0f, 0.0f, 0.0f); // camera looks at world space origin
    vec3 cameraUp(0.0f, 10.0f, 0.0f);
    
    // other camera parameters
    float cameraHorizontalAngle = 90.0f;
    float cameraVerticalAngle =  -30.0f;
    float fov = 70.0f;
    
    // set projection matrix for shader
    mat4 projectionMatrix = glm::perspective(fov,               // field of view in degrees
                                             1024.0f / 768.0f,  // aspect ratio
                                             0.01f, 100.0f);    // near and far (near > 0)

    // set up the uniform
    GLuint projectionMatrixLocation = glGetUniformLocation(commonShaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

    // set initial view matrix
    mat4 viewMatrix = lookAt(cameraPosition,                // eye
                             cameraPosition + cameraLookAt, // center
                             cameraUp);                     // up

    GLuint viewMatrixLocation = glGetUniformLocation(commonShaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);

    // define and upload geometry to the GPU here
    Grid grid(commonShaderProgram);
    Axis axis(commonShaderProgram);
    Olaf olaf(commonShaderProgram);
    
    // frame time settings
    float lastFrameTime = glfwGetTime();
    double lastMousePosX, lastMousePosY;
    glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);
    
    // other OpenGL states to set once before the game loop
    // enable backface culling
    glEnable(GL_CULL_FACE);
    
    // enable depth test
    glEnable(GL_DEPTH_TEST);
    
    // set the gl depth function
    glDepthFunc(GL_LESS);
    
    // yaw and pitch settings for mouse rotations
    float yaw = 0.0f;
    float pitch = 0.0f;

    // main game loop
    // render loop (an iteration of the loop is a frame)
    while (!glfwWindowShouldClose(window)) {
        
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear depth buffer bit at the beginning of each frame

        // draw grid, axis and olaf
        grid.draw();
        axis.draw();
        olaf.draw();
        
        // initialize initial transformations for olaf
        vec3 initScale = olaf.getInitScale();
        vec3 initTranslate = olaf.getInitTranslate();
        float initRotateAngle = olaf.getInitRotateAngle();

        glfwSwapBuffers(window); // swaps the color buffer
        glfwPollEvents(); // checks if any events are triggered, updates window state and calls corresponding functions
        
        glfwSetKeyCallback(window, key_callback);
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

        // set pan and tilt matrix to be used as transformation matrices for view matrix
        glm::mat4 pan = glm::rotate(glm::mat4(1.0f), glm::radians(yaw), vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 tilt = glm::rotate(glm::mat4(1.0f), glm::radians(pitch), vec3(1.0f, 0.0f, 0.0f));
        
        viewMatrix = pan * tilt * lookAt(cameraPosition, cameraPosition + cameraLookAt, cameraUp);
        
        double mousePosX, mousePosY;
        glfwGetCursorPos(window, &mousePosX, &mousePosY); // gets current mouse position when mouse moves

        // calculating difference in x and y positions
        double dx = mousePosX - lastMousePosX;
        double dy = mousePosY - lastMousePosY;

        // last mouse positions are current new cursor positions
        lastMousePosX = mousePosX;
        lastMousePosY = mousePosY;

        const float cameraAngularSpeed = 70.0f; // sensitivity
        cameraHorizontalAngle -= dx * cameraAngularSpeed * dt; // position difference * sens * frame time
        cameraVerticalAngle -= dy * cameraAngularSpeed * dt;

        // clamp vertical angle to [-85, 85] degrees
        cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, cameraVerticalAngle));
        if (cameraHorizontalAngle > 360) {
            cameraHorizontalAngle -= 360;
        } else if (cameraHorizontalAngle < -360) {
            cameraHorizontalAngle += 360;
        }
        
        // locking mouse movements since they will be controlled when pressing down on mouse buttons
        float cameraLookAtX = 0.0f;
        float cameraLookAtY = 0.0f;
        float cameraLookAtZ = -20.0f; 
        
        cameraLookAt = vec3(cameraLookAtX, cameraLookAtY, cameraLookAtZ);
        vec3 cameraSideVector = glm::cross(cameraLookAt, vec3(0.0f, 1.0f, 0.0f));

        glm::normalize(cameraSideVector); // normalize camera vector
    
        // pressing spacebar repositions olaf at a random location
        if (glfwGetKey(window, GLFW_KEY_SPACE)) {
            srand((unsigned int)time(NULL)); // initialize random number generator for floats
            float x = 2;
            float z = 2;
            
            // generate random x and z
            float randomX = (float(rand())/float(RAND_MAX)) * x;
            float randomZ = (float(rand())/float(RAND_MAX)) * z;
            
            // randomly assign positive or negative values
            int sign = (rand() % 2);
            
            if (sign == 0) {
                randomX *= -1; // make X negative
            } else {
                randomZ *= -1; // make Z negative
            }
    
            olaf.translate(vec3(initTranslate.x + randomX, initTranslate.y, initTranslate.z + randomZ)); // position in y never changes since we only translate in x and z
        }
    
        float scaleValue = 0.001f;

        // pressing 'U' scales olaf up by scale value
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) ==  GLFW_PRESS) {
            olaf.scale(vec3(initScale.x + scaleValue, initScale.y + scaleValue, initScale.z + scaleValue)); 
        }

        // pressing 'J' scales olaf down by scale value
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) ==  GLFW_PRESS) {
           olaf.scale(vec3(initScale.x - scaleValue, initScale.y - scaleValue, initScale.z - scaleValue));
        }
        
        float movement = 0.05f;
        
        // the following olaf movements are based from the camera's perspective and not the axis (i.e.: moving left corresponds to moving towards the negatvie x axis)
        // pressing 'A' moves olaf to the left
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) ==  GLFW_PRESS) {
             olaf.translate(vec3(initTranslate.x - movement, initTranslate.y, initTranslate.z)); // position in y never changes since we only translate in x and z
        }
        
        // pressing 'D' moves olaf to the right
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) ==  GLFW_PRESS) {
             olaf.translate(vec3(initTranslate.x + movement, initTranslate.y, initTranslate.z)); // position in y never changes since we only translate in x and z
        }
        
        // pressing 'W' moves olaf up
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) ==  GLFW_PRESS) {
             olaf.translate(vec3(initTranslate.x, initTranslate.y, initTranslate.z - movement)); // position in y never changes since we only translate in x and z
        }
        
        // pressing 'S' moves olaf down
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) ==  GLFW_PRESS) {
             olaf.translate(vec3(initTranslate.x, initTranslate.y, initTranslate.z + movement)); // position in y never changes since we only translate in x and z
        }
        
        // pressing 'a' rotates left 5 degress about olaf's y axis
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS) {
            olaf.rotateSelf(true); // set boolean to true so olaf can rotate about its own y axis
            olaf.rotate(initRotateAngle + 5.0f, vec3(0.0f, 1.0f, 0.0f));
        }
        
        // pressing 'd' rotates right 5 degress about olaf's y axis
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS) {
            olaf.rotateSelf(true); // set boolean to true so olaf can rotate about its own y axis
            olaf.rotate(initRotateAngle - 5.0f, vec3(0.0f, 1.0f, 0.0f));
        }
        
        // pressing left arrow moves anticlockwise rotation about positive x axis
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            olaf.rotateSelf(false); // reset boolean so olaf can rotate around world x axis and not its own x axis
            axis.rotate(initRotateAngle + 5.0f, vec3(1.0f, 0.0f, 0.0f));
            olaf.rotate(initRotateAngle + 5.0f, vec3(1.0f, 0.0f, 0.0f));
            grid.rotate(initRotateAngle + 5.0f, vec3(1.0f, 0.0f, 0.0f));
        }
        
        // pressing right arrow moves clock rotation about negative x axis
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            olaf.rotateSelf(false);
            axis.rotate(initRotateAngle - 5.0f, vec3(1.0f, 0.0f, 0.0f));
            olaf.rotate(initRotateAngle - 5.0f, vec3(1.0f, 0.0f, 0.0f));
            grid.rotate(initRotateAngle - 5.0f, vec3(1.0f, 0.0f, 0.0f));
        }
        
        // pressing up arrow moves anticlockwise rotation about positive y axis
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            olaf.rotateSelf(false);
            olaf.rotate(initRotateAngle - 5.0f, vec3(1.0f, 0.0f, 0.0f));
            axis.rotate(initRotateAngle + 5.0f, vec3(0.0f, 1.0f, 0.0f));
            olaf.rotate(initRotateAngle + 5.0f, vec3(0.0f, 1.0f, 0.0f));
            grid.rotate(initRotateAngle + 5.0f, vec3(0.0f, 1.0f, 0.0f));
        }
        
        // pressing down arrow moves anticlockwise rotation about negative y axis
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            olaf.rotateSelf(false);
            axis.rotate(initRotateAngle - 5.0f, vec3(0.0f, 1.0f, 0.0f));
            olaf.rotate(initRotateAngle - 5.0f, vec3(0.0f, 1.0f, 0.0f));
            grid.rotate(initRotateAngle - 5.0f, vec3(0.0f, 1.0f, 0.0f));
        }
        
        // pressing home button resets to initial world position and orientation (olaf's position on grid does not change)
        if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
            olaf.rotateSelf(false);
            axis.rotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
            olaf.rotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
            grid.rotate(0.0f, vec3(1.0f, 1.0f, 1.0f));
        }
        
        // pressing 'P' renders points
        if (glfwGetKey(window, GLFW_KEY_P) && glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            olaf.setRenderMode(GL_POINTS);
        }

        // pressing 'L' renders lines
        if (glfwGetKey(window, GLFW_KEY_L) && glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            olaf.setRenderMode(GL_LINES);
        }
        
        // pressing 'T' renders triangles
        if (glfwGetKey(window, GLFW_KEY_T) && glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            olaf.setRenderMode(GL_TRIANGLES);
        }
        
        // pressing right mouse button moves mouse in x to pan
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            
            // pan in
            if (cameraHorizontalAngle > -5.0f) {
                yaw -= 0.5;
            }
             
            // pan out
            if (cameraHorizontalAngle < -5.0f) {
                yaw += 0.5;
            }
        }
             
        // pressing middle mouse button moves mouse in y to tilt
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
            
            // tilt up
            if (cameraVerticalAngle > -5.0f) {
                pitch -= 0.5;
            }
             
            // tilt down
            if (cameraVerticalAngle < -5.0f) {
                pitch += 0.5;
            }
        }

        float zoomSpeed = 1.0f;

        // pressing left mouse button and moving mouse zoom in/out
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            
            // zooms in if mouse is vertically dragged up
            if (cameraVerticalAngle > -5.0f) {
                cameraPosition += cameraLookAt * dt * zoomSpeed;
            }
             
            // zooms out if mouse is vertically dragged down
            if (cameraVerticalAngle < -5.0f) {
                cameraPosition -= cameraLookAt * dt * zoomSpeed;
            }
        }

        GLuint viewMatrixLocation = glGetUniformLocation(commonShaderProgram, "viewMatrix");
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    }
    
    glfwTerminate(); // delete all GLFW resources
    
    return 0;
}
