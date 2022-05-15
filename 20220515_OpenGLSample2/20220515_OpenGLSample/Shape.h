#pragma once
#include <stdint.h>
#include "Application.h"

/// <summary>
/// Base class for drawing shapes in the context of OpenGL
/// </summary>
class Shape
{
public:
	Shape(int w, int h, int x, int y) noexcept:
		mWidth{ w }, mHeight{ h },
		mStartX{ x }, mStartY{ y },
		mIsBuild{ false }, 
		mProgram{ 0 }
	{};

	Shape(const Shape&)            = delete;
	Shape(Shape&&)                 = delete;
	Shape& operator=(const Shape&) = delete;
	Shape& operator=(Shape&&)      = delete;

	virtual ~Shape();

	friend class ShapeApp;

protected:

	static const char* vertex_shader; // the same vertex shader for each derived type
	int mWidth, mHeight;
	int mStartX, mStartY;
	uint32_t mProgram;
	bool mIsBuild;

private:

	/// <summary>
	/// Sets OpenGL objects to draw a paticula shape: fragment shader, program, etc
	/// </summary>
	virtual void Compile() = 0;
	/// <summary>
	/// Draws the particular shape. To set the location of the figure invokes glViewport() 
	/// </summary>
	virtual void Draw() = 0;
};

