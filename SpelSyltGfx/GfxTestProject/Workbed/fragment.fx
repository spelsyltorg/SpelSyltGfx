#version 460 core

uniform float Red;

out vec4 fragColor;

uniform sampler2D tex;

void main()
{
	fragColor = texture2D(tex, vec2(0,0));
}