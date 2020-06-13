#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;

void main()
{
    gl_Position =view * model * vec4(aPos, 1.0f);
    TexCoord = aTexCoord + 0.5f;
}



#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;


void main()
{
    FragColor = texture(texture1, TexCoord);
}