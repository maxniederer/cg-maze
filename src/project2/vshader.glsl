#version 120

attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec2 vTexCoord;
varying vec2 texCoord;
varying vec4 color;

uniform mat4 ctm;
uniform mat4 model_view;
uniform mat4 projection_matrix; // Projection matrix (ortho() for now)

void main()
{
	texCoord = vTexCoord;
	gl_Position = projection_matrix * model_view * ctm * vPosition;
	color = vColor;
}