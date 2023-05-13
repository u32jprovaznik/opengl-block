#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec3 vertColor;

uniform mat4 cameraMatrix;

void main()
{
  gl_Position = cameraMatrix * vec4(aPos, 1.f);
  vertColor = aCol;
}
