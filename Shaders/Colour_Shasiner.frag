#version 330 core

in vec2 tex;

out vec4 colour;

uniform sampler2D OurText;

void main( )
{
	colour = texture( OurText, tex );
};
