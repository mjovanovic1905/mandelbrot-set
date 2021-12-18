#version 450 core

#define ZOOM_CONSTANT 5.0 //at the start, the picture is too zoomed in, so we use this constant to zoom out

out vec4 FragColor;

uniform vec2 screenSize;

void main()
{
    vec2 screenSize = vec2(800.0, 600.0);

    vec2 pos = (gl_FragCoord.xy / screenSize - 0.5) * ZOOM_CONSTANT; 

    float c = 0;

    vec2 zn = vec2(0.0);

    for (int i = 0; i < 100; i++)
    {
        vec2 zn1 = vec2(0.0);
        zn1.x = (zn.x * zn.x - zn.y * zn.y) + pos.x;
        zn1.y = 2.0 * zn.x * zn.y + pos.y;

        c = (zn1.x * zn1.x + zn1.y * zn1.y);

        if (c > 4.0)
        {
            break;
        }
        zn = zn1;
    }

    if (c > 4.0)
    {
        FragColor = vec4(0.5, 0.5, 0.0, 0.0);
    }
    else
    {
        FragColor = vec4(0.0);
    }

}