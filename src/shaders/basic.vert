#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform vec4 base_color;
uniform float iTime;

out vec4 Base_Color;
out vec2 TexCoord;

void main()
{
	gl_Position = model * vec4(aPos, 1.0);
	Base_Color = base_color;
	TexCoord = aTexCoord;
}
