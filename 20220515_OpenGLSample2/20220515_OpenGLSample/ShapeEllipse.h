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
	{}
private:

	void Draw() override;
	void Compile() override;

	static const char* fragment_shader;
};
