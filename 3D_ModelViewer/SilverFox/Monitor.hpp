#pragma once

//#define GLFW_INCLUDE_VULKAN
//#include <GL/glew.h>
//#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

//#pragma comment(lib, "glew32")
//#pragma comment(lib, "vulkan-1")
#pragma comment(lib, "glfw3")

#include <memory>
#include <array>

class alignas(sizeof(float_t)) Monitor final{
public:
	Monitor() noexcept(false);
	Monitor(const Monitor&) = delete;
	Monitor(Monitor&&) = delete;
	Monitor& operator=(const Monitor&) = delete;
	Monitor& operator=(Monitor&&) = delete;
	~Monitor() noexcept(false);

private:
	static void callbackMonitor(GLFWmonitor* const monitor, const int event) noexcept;

private:
	GLFWmonitor* primary_monitor_ = nullptr;

	GLFWvidmode current_video_mode_;

	float_t physical_width_ = 0.0f;
	float_t physical_height_ = 0.0f;

	std::array<float, 2> content_scale_;
	std::array<std::array<int, 2>, 2> workarea_;

public:
	const GLFWvidmode& getVideoMode() const noexcept{
		return current_video_mode_;
	}
};