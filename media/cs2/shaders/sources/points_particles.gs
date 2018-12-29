#version 330

layout(triangles) in;
layout(points, max_vertices = 3) out;

in float color_intensity[];
out vec3 point_color;

void main()
{
    for (int i = 0; i < 3; i++)
    {
        gl_Position = gl_in[i].gl_Position;
        point_color = vec3(color_intensity[i], color_intensity[i], color_intensity[i]);
        EmitVertex();
        EndPrimitive();
    }
}