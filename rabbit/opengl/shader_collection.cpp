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

const char * rabbit::onecolored_texture_vertex_shader = R"""(
#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 texcoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoords;

void main()
{
    gl_Position = model * view * projection * vec4(vertex, 1);
    TexCoords = texcoords;
}  
)""";

const char * rabbit::onecolored_texture_fragment_shader = R"""(
#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D ourTexture;
uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(ourTexture, TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
}  
)""";