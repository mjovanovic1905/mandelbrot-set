#version 450 core

#define THRESHOLD 4.0

out vec4 FragColor;

uniform vec2 u_screenSize;
uniform int u_maxIterations;
uniform float u_zoom;
uniform vec2 u_offset;

int findIterations(vec2 number)
{
    int i;
    vec2 zn = vec2(0.0);
    
    for (i = 0; i < u_maxIterations; i++)
    {
        vec2 zn1;
        zn1.x = (zn.x * zn.x - zn.y * zn.y) + number.x;
        zn1.y = 2.0 * zn.x * zn.y + number.y;

        float c = (zn1.x * zn1.x + zn1.y * zn1.y);
        if (c > THRESHOLD)
        {
            break;
        }

        zn = zn1;
    }

    return i;
}

vec3 hsv2rgb(float h, float s, float v)
{
    h = mod(h, 360.0); // max angle of h is 360 degrees

    float c = v * s;
    float h1 = h / 60.0;

    float x = c * (1 - abs(mod(h1, 2) - 1));

    vec3 rgb;
    
    if (x >= 0.0 && x < 1.0)
    {
        rgb = vec3(c, x, 0.0);
    }
    else if (x >= 1.0 && x < 2.0)
    {
        rgb = vec3(x, c, 0.0);
    }
    else if (x >= 2.0 && x < 3.0)
    {
        rgb = vec3(0.0, c, x);
    }
    else if (x >= 3.0 && x < 4.0)
    {
        rgb = vec3(0.0, x, c);
    }
    else if (x >= 4.0 && x < 5.0)
    {
        rgb = vec3(x, 0.0, c);
    }
    else if (x >= 5.0 && x < 6.0)
    {
        rgb = vec3(c, 0.0, x);
    }

    return rgb;
}

void main()
{
    vec2 pos = ((gl_FragCoord.xy - u_screenSize / 2) / u_zoom) - u_offset;
    int iterations = findIterations(pos);

    if (iterations < u_maxIterations)
    {
        FragColor = vec4(hsv2rgb(iterations, 1.0, 1.0), 1.0);
    }
    else
    {
        FragColor = vec4(0.0);
    }

}