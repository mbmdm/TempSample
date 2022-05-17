#pragma once
#include <stdint.h>
#include <memory>
#include <string>
#include <vector>

#include "Vertex.h"

class GLFWwindow;
class Shape;

class ShapeApp
{
public:
	static ShapeApp& Instance();

	ShapeApp(const ShapeApp&)            = delete;
	ShapeApp(ShapeApp&&)                 = delete;
	ShapeApp& operator=(const ShapeApp&) = delete;
	ShapeApp& operator=(ShapeApp&&)      = delete;

	~ShapeApp();

	/// <summary>
	/// Set width and height of the main window
	/// </summary>
	/// <param name="w">Width</param>
	/// <param name="h">Height</param>
	void SetWindowSize(uint32_t w, uint32_t h);
	
	/// <summary>
	/// Set a title of main window
	/// </summary>
	void SetTitle(std::string title);
	
	/// <summary>
	/// Start render loop
	/// </summary>
	void Run();
	
	/// <summary>
	/// Add shape instance for rendering.
	/// </summary>
	void AddShape(std::unique_ptr<Shape>&& shape);
	
	/// <summary>
	/// Emplace shape for rendering.
	/// Pass to the function a number of arguments suitable for the corresponding class constructor
	/// The function does not accept types that are not derrivative of Shape
	/// </summary>
	template <typename T, typename = typename std::enable_if_t<std::is_base_of<Shape, T>::value, T>, class... Args>
	void EmplaceShape(Args&&... args)
	{
		mShapes.emplace_back(new T{ std::forward<Args>(args)... });
	}	

private:
	ShapeApp();

	void Init();
	
	uint32_t mWidth, mHeight; //Width and height of the main window
	GLFWwindow* mPtrWindow;
	std::vector<std::unique_ptr<Shape>> mShapes;
	/*
		The same vertices buffer is used for drawing shapes.
		Each time a rectangle is drawed on the scene using mVertices buffer.
		The appropriate figure uses its fragment shader (depending on a type) to draw itself.
	*/
	Vertex mVertices[6];
	std::string mTitle;
};