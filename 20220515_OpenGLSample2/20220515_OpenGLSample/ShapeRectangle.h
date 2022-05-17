#pragma once
#include "Shape.h"

class ShapeRectangle : public Shape
{
public:
	/// <summary>
	/// Create rectangle shape in OpenGl context
	/// </summary>
	/// <param name="w">Width</param>
	/// <param name="h">Height</param>
	/// <param name="x">Start x position of figure render frame</param>
	/// <param name="y">Start y position of figure render frame</param>
	ShapeRectangle(int w, int h, int x, int y) noexcept :
		Shape(w, h, x, y)
	{
		mFragmentShader = 
			"#version 330\n"
			"in vec2 pos;"
			"in vec3 color;\n"
			"void main()\n"
			"{\n"
			"    gl_FragColor = vec4(color, 1.0);\n"
			"}\n";
	}

	~ShapeRectangle() = default;
};

