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
    void LinkAttrib(VBO& VBO, GLuint size, GLuint layout, GLenum type, GLsizei stride, void* offset);
    void Bind();
    void Unbind();
    void Delete();
};

#endif // VAO_HPP
