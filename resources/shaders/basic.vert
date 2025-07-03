#version 460 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_color;
layout (location = 2) in vec3 a_normal;
layout (location = 3) in vec2 a_uv;

uniform mat4 mvp;

out vec3 f_color;

void main() {
    gl_Position = mvp * vec4(a_pos, 1.0);
    f_color = a_color;
}