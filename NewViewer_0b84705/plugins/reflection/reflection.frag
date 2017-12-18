
#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform bool useTexture = false;
uniform sampler2D colorMap;
uniform float SIZE;

void main()
{
    if (useTexture) 
    {
      vec2 st = (gl_FragCoord.xy - vec2(0.5)) / SIZE;
      fragColor = texture(colorMap, st) * vec4(0.6,0.6,0.6,1);
    }
    else fragColor = frontColor;
}