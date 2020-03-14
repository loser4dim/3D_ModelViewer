#pragma once

#include "Monitor.hpp"
#include "Window.hpp"

class alignas(sizeof(float_t)) UserInterface final{
public:
	UserInterface() noexcept(false);
	UserInterface(const UserInterface&) = delete;
	UserInterface(UserInterface&&) = delete;
	UserInterface& operator=(const UserInterface&) = delete;
	UserInterface& operator=(UserInterface&&) = delete;
	~UserInterface() noexcept(false);

private:
	static void callbackError(const int code, const char* const message) noexcept;

	static void callbackKey(GLFWwindow* const windowG, const int key, const int scan_code, const int action, const int modifier) noexcept;
	static void callbackCharacter(GLFWwindow* const window, const unsigned int code_point) noexcept;
	static void callbackCursorPosition(GLFWwindow* const window, const double pos_x, const double pos_y) noexcept;
	static void callbackCursorEnter(GLFWwindow* const window, const int enter) noexcept;
	static void callbackMouseButton(GLFWwindow* const window, const int button, const int action, const int modifier) noexcept;
	static void callbackScroll(GLFWwindow* const window, const double offset_x, const double offset_y) noexcept;
	static void callbackJoystick(const int id, const int event) noexcept;
	static void callbackDrop(GLFWwindow* const window, const int cnt, const char** const paths) noexcept;

private:
	std::unique_ptr<Monitor>	monitor_				= nullptr;
	std::unique_ptr<Window>		window_					= nullptr;
	GLFWcursor*					cursor_					= nullptr;
	bool						is_supported_vulkan_	= false;

public:
	const bool isEnable() const noexcept{
		return window_->isOpen();
	}
	void updateWindow() noexcept(false);

private:
	void setupInputMode() const noexcept(false);
	void setupCallback(const GLFWwindow* const window) const noexcept;
};