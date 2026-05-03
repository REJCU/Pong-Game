#version 330

// Input vertex attributes (from Raylib)
in vec2 fragTexCoord;
in vec4 fragColor;

// Output color
out vec4 finalColor;

// Custom variables (Uniforms)
uniform vec2 resolution;
uniform float time;

void main() {
    // Calculate distance from the center of the texcoord (0.5, 0.5)
    float dist = distance(fragTexCoord, vec2(0.5));

    // Create a soft glow effect using a smoothstep or power function
    // The closer to the center, the brighter it is.
    float glow = 0.05 / (dist * dist); 

    // Pulse the glow slightly using the time uniform
    float pulse = 0.8 + 0.2 * sin(time * 5.0);
    
    // Final color: Base color * intensity * pulse
    vec3 color = fragColor.rgb * glow * pulse;

    finalColor = vec4(color, 1.0);
}
