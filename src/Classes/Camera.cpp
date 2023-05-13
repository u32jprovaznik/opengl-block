#include "../Headers/Camera.hpp"

extern const unsigned int WINDOW_WIDTH;
extern const unsigned int WINDOW_HEIGHT;

// Constructor

Camera::Camera(int width, int height, glm::vec3 position)
{
  this->width = width;
  this->height = height;
  this->position = position;
}

// Functions

void Camera::Matrix(float FOVdegrees, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
  glm::mat4 view = glm::mat4(1.f);
  glm::mat4 projection = glm::mat4(1.f);

  view = glm::lookAt(this->position, this->position + this->orientation, this->up);
  projection = glm::perspective(glm::radians(FOVdegrees), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), nearPlane, farPlane);

  glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::Inputs(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    this->position += this->speed * this->orientation;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    this->position -= this->speed * glm::normalize(glm::cross(this->orientation, this->up));
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    this->position -= this->speed * this->orientation;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    this->position += this->speed * glm::normalize(glm::cross(this->orientation, this->up));
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
  {
    this->position += this->speed * this->up;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
  {
    this->position -= this->speed * this->up;
  }
}
