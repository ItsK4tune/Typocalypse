#version 330 core
layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_color;

uniform mat4 mvp;
out vec4 f_color;

void main() {
    gl_Position = mvp * vec4(a_pos, 1.0);
    f_color = vec4(a_color, 1.0);
}
