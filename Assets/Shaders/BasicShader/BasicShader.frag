#version 460

in vec2 v_TexCoords;

out vec4 fragColor;

uniform sampler2D u_Texture;

float Circle(float radius, vec2 position)
{
    return 1 - smoothstep(radius - 1.5, radius + 1.5, length(gl_FragCoord.xy - position));
}

float Rectangle(vec2 topLeft, vec2 bottomRight)
{
    float temp = smoothstep(topLeft.x - 1.5, topLeft.x + 1.5, gl_FragCoord.x);
    temp *= 1.0 - smoothstep(topLeft.y - 1.5, topLeft.y + 1.5, gl_FragCoord.y);
    temp *= 1.0 - smoothstep(bottomRight.x - 1.5, bottomRight.x + 1.5, gl_FragCoord.x);
    temp *= smoothstep(bottomRight.y - 1.5, bottomRight.y + 1.5, gl_FragCoord.y);
    return temp;
}

void main()
{
    // fragColor = vec4(v_TexCoords, 0.0, 1.0);
    fragColor = texture2D(u_Texture, v_TexCoords);
}
