#pragma once
#include "Shape.h"

class ShapeEllipse : public Shape
{
public:
	/// <summary>
	/// Create ellipse shape in OpenGl context
	/// </summary>
	/// <param name="w">Width</param>
	/// <param name="h">Height</param>
	/// <param name="x">Start x position of figure render frame</param>
	/// <param name="y">Start y position of figure render frame</param>
	ShapeEllipse(int w, int h, int x, int y) noexcept :
		Shape(w, h, x, y)
	{
		// color value -1.0 is used for transparency 
		mFragmentShader =
			"#version 330\n"
			"in vec3 color;\n"
			"in vec2 pos;"
			"void main()\n"
			"{\n"
			"    gl_FragColor = vec4(1.f, 1.f, 1.f, -1.0);\n" 
			"    float r_sq =  pos.x*pos.x+pos.y*pos.y;\n"
			"    if (r_sq<1)\n"
			"    {\n"
			"        gl_FragColor = vec4(color, 1.0);\n"
			"    }\n"
			"}\n";
	}

	~ShapeEllipse() = default;
};
