#include "../Headers/VBO.hpp"

// Constructor

VBO::VBO(GLfloat vertices[], GLintptr size)
{
  glGenBuffers(1, &this->ID);
  glBindBuffer(GL_ARRAY_BUFFER, this->ID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Functions

void VBO::Bind()
{
  glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void VBO::Unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
  glDeleteBuffers(1, &this->ID);
}
