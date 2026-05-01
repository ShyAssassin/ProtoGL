#version 410 core

#ifdef VERTEX
out vec3 v_color;

void main() {
    float x = float(1 - int(gl_VertexID)) * 0.5;
    float y = float(int(gl_VertexID & int(1u)) * 2 - 1) * 0.5;
    gl_Position = vec4(x, y, 0.0, 1.0);

    switch(gl_VertexID) {
        case 0: v_color = vec3(1.0, 0.0, 0.0); break;
        case 1: v_color = vec3(0.0, 1.0, 0.0); break;
        case 2: v_color = vec3(0.0, 0.0, 1.0); break;
        default: v_color = vec3(1.0, 1.0, 1.0); break;
    }
}
#endif

#ifdef FRAGMENT
in vec3 v_color;
out vec4 f_color;

void main() {
    f_color = vec4(v_color, 1.0);
}
#endif
