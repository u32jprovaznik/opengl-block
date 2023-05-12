#include "../Headers/Shader.hpp"

// Constructor

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
  // Info Log
  int success;
  char infoLog[512];

  // Shaders
  const char* vertexShaderSource = mrq::file::getContents(vertexPath);
  const char* fragmentShaderSource = mrq::file::getContents(fragmentPath);

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  // Vertex Shader Checking
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cerr << "Failed to compile the vertex shader!" << std::endl;
    std::cerr << "Error: " << infoLog << std::endl;
  }

  // Fragment Shader Checking
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cerr << "Failed to compile the fragment shader!" << std::endl;
    std::cerr << "Error: " << infoLog << std::endl;
  }

  // Shader Program
  this->ID = glCreateProgram();
  glAttachShader(this->ID, vertexShader);
  glAttachShader(this->ID, fragmentShader);
  glLinkProgram(this->ID);
  
  // Shader Program Checking
  glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
    std::cerr << "Failed to link the shader program!" << std::endl;
    std::cerr << "Error: " << infoLog << std::endl;
  }

  // Deleting the Shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

// Functions

void Shader::Activate()
{
  glUseProgram(this->ID);
}

void Shader::Delete()
{
  glDeleteProgram(this->ID);
}
