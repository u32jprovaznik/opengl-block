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

void Camera::Inputs(GLFWwindow* window, float dt)
{
  // WASD Movement
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    this->position += this->speed * dt * this->orientation;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    this->position -= this->speed * dt * glm::normalize(glm::cross(this->orientation, this->up));
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    this->position -= this->speed * dt * this->orientation;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    this->position += this->speed * dt * glm::normalize(glm::cross(this->orientation, this->up));
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
  {
    this->position += this->speed * dt * this->up;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
  {
    this->position -= this->speed * dt * this->up;
  }

  // Locking the Mouse
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
  {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    this->mouseLocked = true;
  }
  else if (glfwGetKey(window, GLFW_KEY_ESCAPE))
  {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    this->mouseLocked = false;
  }

  // Mouse Movement
  if (mouseLocked)
  {
    double mouseX;
    double mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    float rotX = this->sensitivity * (float)(mouseY - (this->height / 2)) / this->height;
    float rotY = this->sensitivity * (float)(mouseX - (this->width / 2)) / this->width;

    glm::vec3 newOrientation = glm::rotate(this->orientation, glm::radians(-rotX), glm::normalize(glm::cross(this->orientation, this->up)));
    if (abs(glm::angle(newOrientation, this->up) - glm::radians(90.0f)) <= glm::radians(85.0f))
    {
      this->orientation = newOrientation;
    }

    this->orientation = glm::rotate(this->orientation, glm::radians(-rotY), this->up);
    glfwSetCursorPos(window, (this->width / 2), (this->height / 2));
  }
}
