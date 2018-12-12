#version 330

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec2 texcoord;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec2 uv;

void main()
{
    uv = texcoord;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vertex;
}