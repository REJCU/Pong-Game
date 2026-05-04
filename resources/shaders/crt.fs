#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

uniform sampler2D texture0;

uniform vec2 renderResolution; 
uniform float time;         

const float curvature = 0.1; 
const float scanlineIntensity = 0.75; 
const float vignetteIntensity = 0.9; 

vec2 curveUV(vec2 uv) {
    uv = uv * 2.0 - 1.0; 
    
    vec2 offset = abs(uv.yx) * curvature;
    uv = uv + uv * offset * offset;
    
    uv = uv * 0.5 + 0.5; 
    return uv;
}

void main() {
    vec2 uv = curveUV(fragTexCoord);
    
    if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0) {
        finalColor = vec4(0.0, 0.0, 0.0, 1.0); // Black borders
        return;
    }

    float distortion = 0.003;
    float r = texture(texture0, uv + vec2(distortion, 0.0)).r;
    float g = texture(texture0, uv).g;
    float b = texture(texture0, uv - vec2(distortion, 0.0)).b;
    vec3 color = vec3(r, g, b);

    float count = renderResolution.y * 1.5; // Number of lines depends on resolution
    float scanline = sin(uv.y * count) * scanlineIntensity;
    color -= scanline; // Darken the lines

    float flicker = 0.01 * sin(time * 50.0);
    color += flicker;

    float vignette = uv.x * uv.y * (1.0 - uv.x) * (1.0 - uv.y);
    vignette = pow(vignette * 16.0, vignetteIntensity);
    color *= vignette;

    finalColor = vec4(color, 1.0);
}
