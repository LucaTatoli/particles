#version 330 core

in vec2 texCoord;
out vec4 FragColor;

uniform sampler2D inTexture;
uniform bool drawTexture;
uniform vec4 color;
uniform float texOffset;

void main()
{
  if(drawTexture)
  {
    vec2 newTexCoord = texCoord;
    newTexCoord.x += texOffset;
    FragColor = texture(inTexture, newTexCoord);
  }
  else
    FragColor = vec4(color);
}
