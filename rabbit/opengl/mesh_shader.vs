#version 330 core
layout (location = 0) in vec3 position; // Устанавливаем позицию атрибута в 0

void main()
{
    gl_Position = vec4(position, 1.0); // Напрямую передаем vec3 в vec4
}