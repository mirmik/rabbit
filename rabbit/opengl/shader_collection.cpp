#include <rabbit/opengl/shader_collection.h>

const char * rabbit::mesh_vertex_shader = R"""(
#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
}
)""";

const char * rabbit::mesh_fragment_shader = R"""(
#version 330 core

uniform vec4 vertexColor;
out vec4 color;

void main()
{
    color = vertexColor;
} 
)""";

const char * rabbit::simple_vertex_shader = R"""(
#version 300 es
layout (location = 0) in vec3 position;

void main()
{
    gl_Position = vec4(position, 1.0f);
}
)""";

const char * rabbit::simple_fragment_shader = R"""(
#version 300 es

out lowp vec4 color;

void main()
{
    color = vec4(1,1,1,1);
} 
)""";