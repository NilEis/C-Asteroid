#version 100

precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec2 fragTexCoord;
varying vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// NOTE: Add here your custom variables

void main() {
    vec4 texelColor = texture2D(texture0, fragTexCoord);
    texelColor += texture2D(texture0, fragTexCoord + vec2(0, 1.0));
    texelColor += texture2D(texture0, fragTexCoord + vec2(0, -1.0));
    texelColor += texture2D(texture0, fragTexCoord + vec2(1.0, 0));
    texelColor += texture2D(texture0, fragTexCoord + vec2(-1.0, 0));
    gl_FragColor = texelColor / 5.0;
    gl_FragColor = texture2D(texture0, fragTexCoord);
}