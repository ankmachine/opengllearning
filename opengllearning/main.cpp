//
//  main.cpp
//  opengllearning
//
//  Created by ankit sinha on 14/04/19.
//  Copyright © 2019 ankit sinha. All rights reserved.
//

#include <iostream>

// glew
#define GLEW_STATIC
#include <GL/glew.h>

// glfw
#include <GLFW/glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600;

// shader
#include "Shader.h"


int main(int argc, const char * argv[]) {
    // insert code here...
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGl", nullptr, nullptr);

    // following loines are for hight density screen like retina display on mac
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    // incase we fail to create window
    if(nullptr == window){
        std::cout<<"Failed to create GLFW window"<<std::endl;
        glfwTerminate();
        
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    
    if (GLEW_OK != glewInit()){
        std::cout<<"Failed to initialize Glew"<<std::endl;
        return -1;
    }
    
    glViewport(0, 0, screenWidth, screenHeight);
    
    // compile the shader here
    Shader ourShader("resources/shaders/core.vs", "resources/shaders/core.frag");
    // getting vertex data
    GLfloat vertices[] =
    {
        // Positions         // Colors
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // Bottom Right
        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // Bottom Left
        0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f   // Top
    };
    
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    
    //setup for triangle
    glBindVertexArray( VAO );
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // this is where i am telling opengl to how to use data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0); // unbind VAO
    
    // can setup another triangle here
    
    // this our game loop, we are saying here when the window is open
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        ourShader.Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
    }
    
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );
    // we hit this part of the code only if window is closed
    glfwTerminate();
    
    return 0;
}
