#ifndef SHADER_H
#define SHADER_H

#define MAIN_SHADER_fs "#version 100\n"\
"\n"\
"precision mediump float;\n"\
"\n"\
"// Input vertex attributes (from vertex shader)\n"\
"varying vec2 fragTexCoord;\n"\
"varying vec4 fragColor;\n"\
"\n"\
"// Input uniform values\n"\
"uniform sampler2D texture0;\n"\
"uniform vec4 colDiffuse;\n"\
"\n"\
"// NOTE: Add here your custom variables\n"\
"\n"\
"void main()\n"\
"{\n"\
"    vec4 texelColor = texture2D(texture0, fragTexCoord);\n"\
"    gl_FragColor = texelColor;\n"\
"}"
const char basic_shader_fs[] = MAIN_SHADER_fs;
#undef MAIN_SHADER_fs

#define MAIN_SHADER_vs "#version 100\n"\
"\n"\
"// Input vertex attributes\n"\
"attribute vec3 vertexPosition;\n"\
"attribute vec2 vertexTexCoord;\n"\
"attribute vec3 vertexNormal;\n"\
"attribute vec4 vertexColor;\n"\
"\n"\
"// Input uniform values\n"\
"uniform mat4 mvp;\n"\
"\n"\
"// Output vertex attributes (to fragment shader)\n"\
"varying vec2 fragTexCoord;\n"\
"varying vec4 fragColor;\n"\
"\n"\
"// NOTE: Add here your custom variables\n"\
"\n"\
"void main()\n"\
"{\n"\
"    // Send vertex attributes to fragment shader\n"\
"    fragTexCoord = vertexTexCoord;\n"\
"    fragColor = vertexColor;\n"\
"\n"\
"    // Calculate final vertex position\n"\
"    gl_Position = mvp*vec4(vertexPosition, 1.0);\n"\
"}"
const char basic_shader_vs[] = MAIN_SHADER_vs;
#undef MAIN_SHADER_vs

#endif // SHADER_H
