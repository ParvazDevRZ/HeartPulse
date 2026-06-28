uniform sampler2D texture;

void main()
{
    vec2 uv = gl_TexCoord[0].xy;

    vec4 original = texture2D(texture, uv);

    vec4 blur = vec4(0.0);

    float offset = 0.006;

    blur += texture2D(texture, uv + vec2(offset, 0.0));
    blur += texture2D(texture, uv - vec2(offset, 0.0));

    blur += texture2D(texture, uv + vec2(0.0, offset));
    blur += texture2D(texture, uv - vec2(0.0, offset));

    blur += texture2D(texture, uv + vec2(offset, offset));
    blur += texture2D(texture, uv - vec2(offset, offset));

    blur += texture2D(texture, uv + vec2(-offset, offset));
    blur += texture2D(texture, uv + vec2(offset, -offset));

    blur /= 8.0;


    vec4 glow = blur * 1.8;


    gl_FragColor = original + glow;
}