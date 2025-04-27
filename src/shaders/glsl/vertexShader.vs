#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
uniform float width;
uniform float height;
out vec2 texCoord;

void main()
{
  float ratio = height / width;
  gl_Position = vec4(aPos.x * ratio, aPos.y, aPos.z, 1.0f);
  texCoord = aTexCoord;
}
