#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in float t;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec2 tZero;
uniform vec2 tOne;
uniform vec2 tTwo;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);

    if(t == 0.0f)
    {
        TexCoord = tZero + 0.5f;
	}
        if(t == 1.0f)
    {
        TexCoord = tOne + 0.5f;
	}
        if(t == 2.0f)
    {
        TexCoord = tTwo + 0.5f;
	}
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