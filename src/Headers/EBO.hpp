#ifndef EBO_HPP
#define EBO_HPP

#include <GL/glew.h>

class EBO
{
  public:
    // Constructor
    EBO(GLuint indices[], GLintptr size);

    GLuint ID;

    // Functions
    void Bind();
    void Unbind();
    void Delete();
};

#endif // EBO_HPP
