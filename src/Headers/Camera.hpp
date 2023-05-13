#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.hpp"
#include "../Constants.hpp"

class Camera
{
  public:
    glm::vec3 position;
    glm::vec3 orientation = glm::vec3(0.f, 0.f, -3.f);
    glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);

    int width;
    int height;

    float speed = 0.1f;
    float sensitivity = 100.f;

    // Constructor
    Camera(int width, int height, glm::vec3 position);

    // Functions
    void Matrix(float FOVdegrees, float nearPlane, float farPlane, Shader& shader, const char* uniform);
    void Inputs(GLFWwindow* window);
};

#endif // CAMERA_HPP
