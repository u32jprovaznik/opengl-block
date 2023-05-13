#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Headers/Shader.hpp"
#include "Headers/VAO.hpp"
#include "Headers/VBO.hpp"
#include "Headers/EBO.hpp"
#include "Utils/Macroneq.hpp"

// Constants
const unsigned int WINDOW_WIDTH  = 800;
const unsigned int WINDOW_HEIGHT = 600;
const char*        WINDOW_TITLE  = "GLFW";

// Callbacks
void framebufferSizeCallback(GLFWwindow* window, GLint width, GLint height);

// Vertices and Indices
GLfloat vertices[] = {
  -0.5f,  -0.5f, 1.f, 1.f, 0.f, 0.f,
   0.0f,  -0.5f, 1.f, 0.f, 1.f, 0.f,
  -0.25f,  0.0f, 1.f, 0.f, 0.f, 1.f,
   0.5f,  -0.5f, 1.f, 1.f, 1.f, 0.f,
   0.25f,  0.0f, 1.f, 0.f, 1.f, 1.f,
   0.0f,   0.5f, 1.f, 1.f, 0.f, 1.f,
};
GLuint indices[] = {
  0, 1, 2,
  1, 3, 4,
  2, 4, 5,
};

int main()
{
  // Initializing GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Creating the Window
  GLFWwindow* window = glfwCreateWindow(
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    WINDOW_TITLE,
    NULL,
    NULL
  );
  if (window == NULL)
  {
    std::cerr << "Failed to initialize a GLFW Window!" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

  // Initializing GLEW
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    std::cerr << "Failed to initialze GLEW!" << std::endl;
    std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    glfwTerminate();
    return -1;
  }
  std::cout << "GLEW: " << glewGetString(GLEW_VERSION) << std::endl;

  // Clear Color
  GLclampf red   = 0.0f;
  GLclampf green = 0.3f;
  GLclampf blue  = 0.3f;
  GLclampf alpha = 1.0f;
  glClearColor(red, green, blue, alpha);

  // Callbacks
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  // Shaders
  Shader defaultShader("src/Shaders/default.vert", "src/Shaders/default.frag");

  // VAO, VBO, and EBO
  VAO VAO1;
  VAO1.Bind();

  VBO VBO1(vertices, sizeof(vertices));
  EBO EBO1(indices, sizeof(indices));

  VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
  VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  // Main Loop
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    defaultShader.Activate();
    VAO1.Bind();
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
  }

  // Terminating the Program
  glfwTerminate();
  defaultShader.Delete();
  VAO1.Delete();
  VBO1.Delete();
  EBO1.Delete();
  return 0;
}

void framebufferSizeCallback(GLFWwindow* window, GLint width, GLint height)
{
  glViewport(0, 0, width, height);
}
