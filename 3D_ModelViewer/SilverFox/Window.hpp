#pragma once

//#define GLFW_INCLUDE_VULKAN
//#include <GL/glew.h>
//#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

//#pragma comment(lib, "glew32")
//#pragma comment(lib, "vulkan-1")
#pragma comment(lib, "glfw3")

#include <memory>

class alignas(sizeof(float_t)) Window final{
private:
	static constexpr const char* const TITLE_NAME_ = u8"3D Model Viewer - Copyright: loser4dim, 2020";
	static constexpr const float OPACITY_ = 0.9f;

public:
	Window() = delete;
	Window(const GLFWvidmode video_mode, const bool is_supported_vulkan) noexcept(false);
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;
	~Window() noexcept(false);

private:
	//Window Callback Functions
	static void callbackClose(GLFWwindow* const window) noexcept;
	static void callbackRefresh(GLFWwindow* const window) noexcept;
	static void callbackSize(GLFWwindow* const window, const int width, const int height) noexcept;
	static void callbackFramebuffer(GLFWwindow* const window, const int width, const int height) noexcept;
	static void callbackContentScale(GLFWwindow* const window,  const float scale_x, const float scale_y) noexcept;
	static void callbackPosition(GLFWwindow* const window, const int pos_x, const int pos_y) noexcept;
	static void callbackIconfy(GLFWwindow* const window, const int iconfied_status) noexcept;
	static void callbackMaximum(GLFWwindow* const window, const int maximum_status) noexcept;
	static void callbackFocus(GLFWwindow* const window, const int focus_status) noexcept;

private:
	GLFWwindow* main_window_ = nullptr;
	GLFWimage	icon_;

public:
	GLFWwindow* const getWindow() const noexcept{
		return main_window_;
	}
	const bool isOpen() const noexcept{
		return glfwWindowShouldClose(main_window_) != GLFW_TRUE;
	}

	void destroy() noexcept(false);

private:
	void setupWindowHint(const GLFWvidmode& video_mode, const bool is_supported_vulkan) const noexcept(false);
	void setupCallback() const noexcept(false);

	void loadIconImage() noexcept(false);
};