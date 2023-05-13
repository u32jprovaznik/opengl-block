#ifndef VAO_HPP
#define VAO_HPP

#include <GL/glew.h>

#include "VBO.hpp"

class VAO
{
  public:
    // Constructor
    VAO();

    GLuint ID;

    // Functions
    void LinkVBO(VBO& VBO, GLuint layout);
    void Bind();
    void Unbind();
    void Delete();
};

#endif // VAO_HPP
