#include <exception>
#include <cstdio>

#include "GLCommon.h"
#include "ShapeApp.h"
#include "Shape.h"

void ErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
	std::exit(error);
}

ShapeApp& ShapeApp::Instance()
{
	static ShapeApp sApp;
	return sApp;
}

void ShapeApp::SetWindowSize(uint32_t w, uint32_t h)
{
	mWidth = w;
	mHeight = h;
}

void ShapeApp::SetTitle(std::string title)
{
	mTitle.swap(title);
}

void ShapeApp::Run()
{	
	constexpr int swapBufferCount = 1;

	//create main window
	mPtrWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), NULL, NULL);
	if (!mPtrWindow)
		ErrorCallback(EXIT_FAILURE, "failed to create Window.");

	glfwMakeContextCurrent(mPtrWindow);

	glfwSwapInterval(swapBufferCount);

	if (!gladLoadGL(glfwGetProcAddress))
		ErrorCallback(EXIT_FAILURE, "failed to initialize OpenGL context.");

	//define vertex data
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), mVertices, GL_STATIC_DRAW);

	GLuint vertex_array;
	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);

	//compile shaders and program for each figure
	for (auto& sh : mShapes)
		sh->Compile();

	//render loop
	while (!glfwWindowShouldClose(mPtrWindow))
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glBindVertexArray(vertex_array);
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for (auto& sh : mShapes) 
		{
			sh->Draw();
			glDrawArrays(GL_TRIANGLES, 0, sizeof(mVertices) / sizeof(Vertex));
		}

		glfwSwapBuffers(mPtrWindow);
		glfwPollEvents();
	}
}

void ShapeApp::AddShape(std::unique_ptr<Shape>&& shape)
{
	mShapes.push_back(std::move(shape));
}

ShapeApp::ShapeApp():
	mWidth { 640 },
	mHeight{ 480 },
	mPtrWindow{ nullptr },
	mTitle{"MainWindow"}
{
	mVertices[0] = { { -1.f, -1.f }, { 1.f, 1.f, 0.f } };
	mVertices[1] = { { -1.f,  1.f }, { 1.f, 1.f, 0.f } };
	mVertices[2] = { {  1.f,  1.f }, { 1.f, 1.f, 0.f } };
	mVertices[3] = { { -1.f, -1.f }, { 1.f, 1.f, 0.f } };
	mVertices[4] = { {  1.f,  1.f }, { 1.f, 1.f, 0.f } };
	mVertices[5] = { {  1.f, -1.f }, { 1.f, 1.f, 0.f } };
	Init();
}

ShapeApp::~ShapeApp()
{
	if (mPtrWindow)
		glfwDestroyWindow(mPtrWindow);
    glfwTerminate();
}

void ShapeApp::Init()
{
	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
		ErrorCallback(EXIT_FAILURE, "failed OpenGL initialization");

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
