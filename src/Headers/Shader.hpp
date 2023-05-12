#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>

#include "../Utils/Macroneq.hpp"

class Shader
{
  public:
    // Constructor
    Shader(const char* vertexPath, const char* fragmentPath);

    GLuint ID;

    // Functions
    void Activate();
    void Delete();
};

#endif // SHADER_HPP
