#include "Application.h"
#include "ShapeRectangle.h"
#include "ShapeEllipse.h"
#include "ShapeTriangle.h"

int main()
{
	auto& app = ShapeApp::Instance();

	app.SetWindowSize(500, 650);
	app.SetTitle("Shape Demo");

	app.EmplaceShape<ShapeRectangle>(400, 100, 0, 0);
	app.EmplaceShape<ShapeTriangle>(400, 100, 0, 150);
	app.EmplaceShape<ShapeRectangle>(400, 100, 0, 300);
	app.EmplaceShape<ShapeEllipse>(400, 200, 0, 450);
	app.EmplaceShape<ShapeEllipse>(200, 650, 300, 0);

	app.Run();

	return EXIT_SUCCESS;
}