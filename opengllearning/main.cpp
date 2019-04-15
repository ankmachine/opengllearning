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

    // this our game loop, we are saying here when the window is open
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwSwapBuffers(window);
    }

    // we hit this part of the code only if window is closed
    glfwTerminate();
    
    return 0;
}
