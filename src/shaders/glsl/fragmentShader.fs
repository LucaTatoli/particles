#version 330 core

in vec4 fragCircleData;
in vec3 fragCircleColor;
uniform float radius;
out vec4 FragColor;

void main()
{
  float dx = fragCircleData.x - fragCircleData.z;
  float dy = fragCircleData.y - fragCircleData.w;
  float radiusSquared = radius * radius;
  if (dx * dx + dy * dy <= radiusSquared)
  {
    FragColor = vec4(fragCircleColor, 1.0f);
  }
  else
  {
    discard;
  }

}
