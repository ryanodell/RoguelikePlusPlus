#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 ourColor;
out vec2 TexCoord;
uniform mat4 u_mvp;

void main()
{
    gl_Position = u_mvp * vec4(aPos, 1.0);
    ourColor = vec4(aColor.rgb, 1.0);
    TexCoord = aTexCoord;
}