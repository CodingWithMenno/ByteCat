#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec2 texCoord;

uniform mat4 _modelMatrix;
uniform mat4 _viewMatrix;
uniform mat4 _projectionMatrix;

out vec2 passTexCoord;

void main()
{		
	passTexCoord = texCoord;
	gl_Position = _projectionMatrix * _viewMatrix * _modelMatrix * vec4(vertexPos, 1.0);
}