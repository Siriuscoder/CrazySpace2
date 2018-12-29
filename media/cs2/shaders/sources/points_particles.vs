#version 330

layout(location = 0) in vec4 vertex;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out float color_intensity;

void main()
{
    color_intensity = vertex.z;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex.xy, 0.0, 1.0);
}