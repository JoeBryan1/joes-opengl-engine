#version 330

#ifdef GL_ES
precision mediump float;
#endif

in vec4 gl_FragCoord;

out vec4 color;

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float circle(in vec2 _st, in float _radius)
{
    vec2 dist = _st-vec2(0.5);
    return 1.-smoothstep(_radius-(_radius*0.01),
                         _radius+(_radius*0.01),
                         dot(dist, dist)*4.0);
}

void main() {
    vec2 st = (gl_FragCoord.xy/2)/u_resolution.xy;

    vec3 color1 = vec3(1.0,0.55,0);
    vec3 color2 = vec3(0.226,0.000,0.615);

    float time_scale = 1.0;

    float x = u_mouse.x/u_resolution.x;
    float y = (-u_mouse.y/u_resolution.y)+1;

    float mixValue = distance(st, vec2(x,y));

    float radius = 0.9;
    float borderThickness = 0.01;

    vec2 dist = st-vec2(0.5);

    float t1 = 1.0 - smoothstep(radius-borderThickness, radius,
                                dot(dist, dist)*4.0);
    float t2 = 1.0 - smoothstep(radius, radius+borderThickness,
                                dot(dist, dist)*4.0);

    vec4 baseColor = vec4(vec3(circle(st,0.9))*mix(color1,color2,mixValue), 1.0);

    float radius2 = 0.5;

    vec4 borderColor = baseColor*6.;

    vec4 frag_colour = mix(borderColor, baseColor, t1);

    color = frag_colour;
}