#include <glad/gl.h>
#include <stddef.h>

#include "ShapeTriangle.h"
#include "Vertex.h"

const char* ShapeTriangle::fragment_shader =
"#version 330\n"
"in vec2 pos;"
"in vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(1.f, 1.f, 1.f, -1.0);\n"
"    float x = pos.x;\n"
"    if (x > 0) {\n"
"        x = -x;\n"
"    }\n"
"    float ymax =  2*(x+0.5);\n"
"    if (pos.y <= ymax)\n"
"    {\n"
"        gl_FragColor = vec4(color, 1.0);\n"
"    }\n"
"}\n";

void ShapeTriangle::Draw()
{
	if (!mIsBuild)
		return;

	glViewport(mStartX, mStartY, mWidth, mHeight);
	glUseProgram(mProgram);
}

void ShapeTriangle::Compile()
{
	const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &ShapeTriangle::vertex_shader, NULL);
	glCompileShader(vertex_shader);

	const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &ShapeTriangle::fragment_shader, NULL);
	glCompileShader(fragment_shader);

	mProgram = glCreateProgram();
	glAttachShader(mProgram, vertex_shader);
	glAttachShader(mProgram, fragment_shader);
	glLinkProgram(mProgram);

	const GLint vpos_location = glGetAttribLocation(mProgram, "vPos");
	const GLint vcol_location = glGetAttribLocation(mProgram, "vCol");

	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, col));

	mIsBuild = true;
}
