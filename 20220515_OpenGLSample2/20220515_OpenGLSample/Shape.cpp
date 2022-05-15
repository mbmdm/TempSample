#include "Shape.h"
#include <glad/gl.h>

const char* Shape::vertex_shader =
"#version 330\n"
"in vec3 vCol;\n"
"in vec2 vPos;\n"
"out vec3 color;\n"
"out vec2 pos;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(vPos, 0.0, 1.0);\n"
"    pos = vPos;\n"
"    color = vCol;\n"
"}\n";

Shape::~Shape()
{
	if (mProgram)
		glDeleteProgram(mProgram);
};