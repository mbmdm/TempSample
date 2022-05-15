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
	{}
private:
	
	void Draw() override;
	void Compile() override;

	static const char* fragment_shader;
};

