#ifndef VBO_HPP
#define VBO_HPP

#include <GL/glew.h>

class VBO
{
  public:
    // Constructor
    VBO(GLfloat vertices[], GLintptr size);

    GLuint ID;

    // Functions
    void Bind();
    void Unbind();
    void Delete();
};

#endif // VBO_HPP
