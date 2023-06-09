# CMake Version
cmake_minimum_required(VERSION 3.0)

# Constants
set(PROJECT_NAME "block")
set(OpenGL_GL_PREFERENCE LEGACY)

# Project Name
project(${PROJECT_NAME})

# C++ Standard
set(CMAKE_CXX_STANDARD 11)

# Packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Executable
add_executable(
  ${PROJECT_NAME}
  src/Main.cpp
  src/Constants.hpp
  src/Classes/Shader.cpp
  src/Classes/VAO.cpp
  src/Classes/VBO.cpp
  src/Classes/EBO.cpp
  src/Classes/Camera.cpp
  src/Headers/Shader.hpp
  src/Headers/VAO.hpp
  src/Headers/VBO.hpp
  src/Headers/EBO.hpp
  src/Headers/Camera.hpp
  src/Utils/Macroneq.cpp
  src/Utils/Macroneq.hpp
)
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_link_libraries(${PROJECT_NAME} PUBLIC GL GLEW glfw glm)
