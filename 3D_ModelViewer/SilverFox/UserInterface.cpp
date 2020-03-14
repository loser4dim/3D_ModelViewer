#include "UserInterface.hpp"

#include <iostream>

using namespace std;

UserInterface::UserInterface() noexcept(false){
	//USER_INTERFACE_INSTANCE_GLOBAL_REFERENCE = make_shared<UserInterface>(this);

	//Get GLFW Version
	//I do NOT Use glfwGetVersionString() because of the Place where Pointer is Generated
	int glfw_major_ = 0;
	int glfw_minor_ = 0;
	int glfw_revision_ = 0;
	glfwGetVersion(&glfw_major_, &glfw_minor_, &glfw_revision_);
	clog << "GLFW Version: " << glfw_major_ << "." << glfw_minor_ << "." << glfw_revision_ << endl;

	glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_TRUE);
	glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
	glfwInitHint(GLFW_COCOA_MENUBAR, GLFW_FALSE);

	glfwSetErrorCallback(callbackError);

	if(glfwInit() != GLFW_TRUE){
		throw(runtime_error("Fail to Initialze GLFW!"));
	}

	//is_supported_vulkan_ = glfwVulkanSupported() == GLFW_TRUE;

	monitor_ = make_unique<Monitor>();

	window_ = make_unique<Window>(monitor_->getVideoMode(), is_supported_vulkan_);

	setupCallback(window_->getWindow());

	setupInputMode();
	cursor_ = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
	glfwSetCursor(window_->getWindow(), cursor_);

	glfwMakeContextCurrent(window_->getWindow());
	glfwSwapInterval(0);
}

UserInterface::~UserInterface() noexcept(false){
	glfwDestroyCursor(cursor_);
	window_->destroy();
	glfwTerminate();

	window_.release();
	//USER_INTERFACE_INSTANCE_GLOBAL_REFERENCE.reset();
}

void UserInterface::callbackError(const int code, const char* const message) noexcept{
	//TODO: (message) is UTF-8!
	cerr << "Error Code " << code << ": " << message << endl;
	return;
}

void UserInterface::callbackKey(GLFWwindow* const window, const int key, const int scan_code, const int action, const int modifier) noexcept{
	if(window != nullptr){
		if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
			glfwSetWindowShouldClose(window, GLFW_FALSE);
		}
		cout << "Key: " << key << ", Scan Code: " << scan_code << ", Action: " << action << ", Modifier: " << modifier << endl;
	}
	return;
}
void UserInterface::callbackCharacter(GLFWwindow* const window, const unsigned int code_point) noexcept{
	if(window != nullptr){
		cout << "Code Point: " << code_point << endl;
	}
	return;
}
void UserInterface::callbackCursorPosition(GLFWwindow* const window, const double pos_x, const double pos_y) noexcept{
	if(window != nullptr){
		cout << "Cursor Position: (" << pos_x << ", " << pos_y << ")" << endl;
	}
	return;
}
void UserInterface::callbackCursorEnter(GLFWwindow* const window, const int enter) noexcept{
	if(window != nullptr){
		if(enter == GLFW_TRUE){
			cout << "Cursor Enter!" << endl;
		}
		if(enter == GLFW_FALSE){
			cout << "Cursor Exit!" << endl;
		}
	}
	return;
}
void UserInterface::callbackMouseButton(GLFWwindow* const window, const int button, const int action, const int modifier) noexcept{
	if(window != nullptr){
		if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
			cout << "Clicked!" << endl;
		}
		cout << "Button: " << button <<  ", Action: " << action << ", Modifier: " << modifier << endl;
	}
	return;
}
void UserInterface::callbackScroll(GLFWwindow* const window, const double offset_x, const double offset_y) noexcept{
	if(window != nullptr){
		cout << "Scroll: (" << offset_x << ", " << offset_y << ")" << endl;
	}
	return;
}
void UserInterface::callbackJoystick(const int id, const int event) noexcept{
	if(event == GLFW_CONNECTED){
		clog << "Connected Joystick." << endl;
	}
	if(event == GLFW_DISCONNECTED){
		clog << "Disconnected Joystick." << endl;
	}
	return;
}
 void UserInterface::callbackDrop(GLFWwindow* const window, const int cnt, const char** const paths) noexcept{
	 if(window != nullptr){
		 for(size_t i(0), end(static_cast<size_t>(cnt)); i < end; ++i){
			 cout << "File " << i + 1 << ": " << paths[i] << endl;
		 }
	 }
	 return;
 }

void UserInterface::updateWindow() noexcept(false){
	glfwSwapBuffers(window_->getWindow());
	glfwPollEvents();
	return;
}

void UserInterface::setupInputMode() const noexcept(false){
	const auto current_window = window_->getWindow();

	glfwSetInputMode(current_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetInputMode(current_window, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetInputMode(current_window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
	glfwSetInputMode(current_window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
	glfwSetInputMode(current_window, GLFW_RAW_MOUSE_MOTION, glfwRawMouseMotionSupported());
	return;
}

void UserInterface::setupCallback(const GLFWwindow* const window) const noexcept{
	const auto current_window = window_->getWindow();

	glfwSetKeyCallback(current_window, callbackKey);
	glfwSetCharCallback(current_window, callbackCharacter);
	glfwSetCursorPosCallback(current_window, callbackCursorPosition);
	glfwSetCursorEnterCallback(current_window, callbackCursorEnter);
	glfwSetMouseButtonCallback(current_window, callbackMouseButton);
	glfwSetScrollCallback(current_window, callbackScroll);
	glfwSetJoystickCallback(callbackJoystick);
	glfwSetDropCallback(current_window, callbackDrop);

	return;
}