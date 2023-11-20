#version 440 core
out vec4 Color;

in vec4 Base_Color;
in vec2 TexCoord;

uniform sampler2D MyTexture; 

void main()
{
	Color = texture(MyTexture, TexCoord) + vec4(85/255, 1, 1, 1);
}
