#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
  -0.5f,  -0.5f, -0.5f,  1.f, 0.f, 0.f,
   0.0f,  -0.5f, -0.5f,  0.f, 1.f, 0.f,
   0.5f,  -0.5f, -0.5f,  0.f, 0.f, 1.f,
  -0.5f,  -0.5f,  0.0f,  1.f, 1.f, 0.f,
   0.0f,  -0.5f,  0.0f,  0.f, 1.f, 1.f,
   0.5f,  -0.5f,  0.0f,  1.f, 0.f, 1.f,
  -0.5f,  -0.5f,  0.5f,  1.f, 0.f, 0.f,
   0.0f,  -0.5f,  0.5f,  0.f, 1.f, 0.f,
   0.5f,  -0.5f,  0.5f,  0.f, 0.f, 1.f,
  -0.25f,  0.0f, -0.25f, 1.f, 1.f, 0.f,
   0.25f,  0.0f, -0.25f, 0.f, 1.f, 1.f,
  -0.25f,  0.0f,  0.25f, 1.f, 0.f, 1.f,
   0.25f,  0.0f,  0.25f, 1.f, 1.f, 0.f,
   0.0f,   0.5f,  0.f,   1.f, 1.f, 1.f,
};
GLuint indices[] = {
  0, 1, 9,
  1, 4, 9,
  4, 3, 9,
  3, 0, 9,
  0, 1, 4,
  4, 3, 0,
  1, 2, 10,
  2, 5, 10,
  5, 4, 10,
  4, 1, 10,
  1, 2, 5,
  5, 4, 1,
  4, 5, 12,
  5, 8, 12,
  8, 7, 12,
  7, 4, 12,
  4, 5, 8,
  8, 7, 4,
  3, 4, 11,
  4, 7, 11,
  7, 6, 11,
  6, 3, 11,
  3, 4, 7,
  7, 6, 3,
  9, 10, 13,
  10, 12, 13,
  12, 11, 13,
  11, 9, 13,
  9, 10, 12,
  12, 11, 9,
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
  Shader shaderProgram("src/Shaders/default.vert", "src/Shaders/default.frag");

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

  // Depth Test
  glEnable(GL_DEPTH_TEST);

  // Rotation
  float rotation = 0.f;
  double prevTime = glfwGetTime();

  // Main Loop
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderProgram.Activate();

    double currentTime = glfwGetTime();
    if (currentTime - prevTime >= 1/60)
    {
      rotation += 0.5f;
      prevTime = currentTime;
    }

    // Matrices
    glm::mat4 model = glm::mat4(1.f);
    glm::mat4 view = glm::mat4(1.f);
    glm::mat4 proj = glm::mat4(1.f);

    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f, 1.f, 0.f));
    view = glm::translate(view, glm::vec3(0.f, 0.f, -4.f));
    proj = glm::perspective(glm::radians(45.f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.f);

    int modelLocation = glGetUniformLocation(shaderProgram.ID, "model");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
    int viewLocation = glGetUniformLocation(shaderProgram.ID, "view");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    int projLocation = glGetUniformLocation(shaderProgram.ID, "proj");
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(proj));

    VAO1.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(vertices) / sizeof(GLfloat), GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
  }

  // Terminating the Program
  glfwTerminate();
  shaderProgram.Delete();
  VAO1.Delete();
  VBO1.Delete();
  EBO1.Delete();
  return 0;
}

void framebufferSizeCallback(GLFWwindow* window, GLint width, GLint height)
{
  glViewport(0, 0, width, height);
}
