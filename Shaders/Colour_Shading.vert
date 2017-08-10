#version 330 core

layout ( location = 0 )  in vec3 position;
layout ( location = 1 )  in vec2 texCoord;

out vec2 tex;

uniform mat4 model; // converts locall co-ordinates to camera co-ordinates
uniform mat4 projection; // converts camera co-ordinates to normalized co-ordinates ( 0 - 1 )
uniform mat4 view;	// converts normalized co-ordinates to window co-ordinates


void main( )
{
	gl_Position = projection * view * model * vec4( position, 1.0 );
	tex = vec2( texCoord.x, 1.0 - texCoord.y);
}
