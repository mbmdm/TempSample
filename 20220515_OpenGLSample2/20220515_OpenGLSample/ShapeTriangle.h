#pragma once
#include "Shape.h"

class ShapeTriangle : public Shape
{
public:
	/// <summary>
	/// Create triangle shape in OpenGl context
	/// </summary>
	/// <param name="w">Width</param>
	/// <param name="h">Height</param>
	/// <param name="x">Start x position of figure render frame</param>
	/// <param name="y">Start y position of figure render frame</param>
	ShapeTriangle(int w, int h, int x, int y) noexcept :
		Shape(w, h, x, y)
	{
		// color value -1.0 is used for transparency 
		mFragmentShader = 
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
	}

	~ShapeTriangle() = default;
};

