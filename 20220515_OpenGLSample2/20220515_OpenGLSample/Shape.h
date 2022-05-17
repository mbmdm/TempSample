#pragma once
#include <stdint.h>
#include "ShapeApp.h"

/// <summary>
/// Base class for drawing shapes in the context of OpenGL
/// </summary>
class Shape
{
public:
	Shape(int w, int h, int x, int y) noexcept:
		mWidth{ w }, mHeight{ h },
		mStartX{ x }, mStartY{ y },
		mIsBuild{ false }, mProgram{ 0 },
		mFragmentShader{ nullptr }
	{
		mVertexShader = 
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
	};

	Shape(const Shape&)            = delete;
	Shape(Shape&&)                 = delete;
	Shape& operator=(const Shape&) = delete;
	Shape& operator=(Shape&&)      = delete;

	virtual ~Shape() = 0;

	friend class ShapeApp;

protected:

	const char* mFragmentShader; // unique fragment shader for each derived type
	int mWidth, mHeight;
	int mStartX, mStartY;
	uint32_t mProgram;
	bool mIsBuild;

private:

	const char* mVertexShader;   // the same vertex shader for each derived type

	/// <summary>
	/// Sets OpenGL objects to draw a paticula shape: fragment shader, program, etc
	/// </summary>
	virtual void Compile();

	/// <summary>
	/// Draws the particular shape. To set the location of the figure invokes glViewport() 
	/// </summary>
	virtual void Draw();
};

