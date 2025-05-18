#version 330 core
layout (location = 0) in vec4 circleData;
layout (location = 1) in vec3 circleColor;
out vec4 fragCircleData;
out vec3 fragCircleColor;

void main()
{
  fragCircleData = circleData;
  fragCircleColor = circleColor;
  gl_Position = vec4(circleData.xy, 0.0f, 1.0f);
}
