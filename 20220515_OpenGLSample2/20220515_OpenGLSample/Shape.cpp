#include "Shape.h"
#include <glad/gl.h>

Shape::~Shape()
{
	if (mProgram)
		glDeleteProgram(mProgram);
}

void Shape::Compile()
{
	if (!mFragmentShader) return;

	constexpr int vertexShadersCount   = 1;
	constexpr int fragmentShadersCount = 1;
	constexpr int vPositionSize        = 2;
	constexpr int vColorSize           = 3;

	//compile vertex shader
	const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, vertexShadersCount, &mVertexShader, NULL);
	glCompileShader(vertex_shader);

	//compile fragment shader
	const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, fragmentShadersCount, &mFragmentShader, NULL);
	glCompileShader(fragment_shader);

	//define OpenGL program
	mProgram = glCreateProgram();
	glAttachShader(mProgram, vertex_shader);
	glAttachShader(mProgram, fragment_shader);
	glLinkProgram(mProgram);

	const GLint vpos_location = glGetAttribLocation(mProgram, "vPos");
	const GLint vcol_location = glGetAttribLocation(mProgram, "vCol");

	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, vPositionSize, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, vColorSize, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, col));

	mIsBuild = true;
}

void Shape::Draw()
{
	if (!mIsBuild)
		return;

	//Viewport is used to set start position 
	//of figure and specify its width and height
	glViewport(mStartX, mStartY, mWidth, mHeight);

	glUseProgram(mProgram);
}
