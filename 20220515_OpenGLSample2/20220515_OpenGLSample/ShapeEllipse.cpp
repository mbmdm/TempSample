#include <glad/gl.h>
#include <stddef.h>

#include "ShapeEllipse.h"
#include "Vertex.h"

const char* ShapeEllipse::fragment_shader =
"#version 330\n"
"in vec3 color;\n"
"in vec2 pos;"
"const float top_left_x = 0.0;\n"
"const float top_left_y = -1.0;\n"
"const float max_radius = 0.5;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(1.f, 1.f, 1.f, -1.0);\n"
"    float r_sq =  pos.x*pos.x+pos.y*pos.y;\n"
"    if (r_sq<1)\n"
"    {\n"
"        gl_FragColor = vec4(color, 1.0);\n"
"    }\n"
"}\n";

void ShapeEllipse::Draw()
{
	if (!mIsBuild)
		return;

	glViewport(mStartX, mStartY, mWidth, mHeight);
	glUseProgram(mProgram);
}

void ShapeEllipse::Compile()
{
	const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &ShapeEllipse::vertex_shader, NULL);
	glCompileShader(vertex_shader);

	const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &ShapeEllipse::fragment_shader, NULL);
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