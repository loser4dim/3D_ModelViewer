#include "Window.hpp"
#include <iostream>
#include <array>

using namespace std;

Window::Window(const GLFWvidmode video_mode, const bool is_supported_vulkan) noexcept(false){
	//Set Window Hint
	setupWindowHint(video_mode, is_supported_vulkan);

	//Create Window
	main_window_ = glfwCreateWindow(video_mode.width * 3 / 4, video_mode.height * 3 / 4, TITLE_NAME_, nullptr, nullptr);
	if(main_window_ == nullptr){
		throw(runtime_error("Fail to Create Main Window!"));
	}

	//Set Window Icon
	loadIconImage();
	glfwSetWindowIcon(main_window_, 1, &icon_);

	//Set Window Limit
	glfwSetWindowSizeLimits(main_window_, video_mode.width / 2, video_mode.height / 2, video_mode.width, video_mode.height);
	glfwSetWindowAspectRatio(main_window_, GLFW_DONT_CARE, GLFW_DONT_CARE);
	
	glfwSetWindowOpacity(main_window_, OPACITY_);
	
	glfwSetWindowUserPointer(main_window_, nullptr);

	setupCallback();
}

Window::~Window() noexcept(false){
}

void Window::destroy() noexcept(false){
	glfwDestroyWindow(main_window_);
	return;
}

void Window::callbackClose(GLFWwindow* const window) noexcept{
	if(window != nullptr){
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	return;
}
void Window::callbackRefresh(GLFWwindow* const window) noexcept{
	if(window != nullptr){
		cout << "Refresh!" << endl;
	}
	return;
}

void Window::callbackSize(GLFWwindow* const window, const int width, const int height) noexcept{
	if(window != nullptr){
		cout << "Window Size: (" << width << ", " << height << ")" << endl;
	}
	return;
}
void Window::callbackFramebuffer(GLFWwindow* const window, const int width, const int height) noexcept{
	if(window != nullptr){
		cout << "Framebuffer Size: (" << width << ", " << height << ")" << endl;
	}
	return;
}
void Window::callbackContentScale(GLFWwindow* const window, const float scale_x, const float scale_y) noexcept{
	if(window != nullptr){
		cout << "Window Content Scale: (" << scale_x << ", " << scale_y << ")" << endl;
	}
	return;
}
void Window::callbackPosition(GLFWwindow* const window, const int pos_x, const int pos_y) noexcept{
	if(window != nullptr){
		cout << "Window Position: (" << pos_x << ", " << pos_y << ")" << endl;
	}
	return;
}
void Window::callbackIconfy(GLFWwindow* const window, const int iconfied_status) noexcept{
	if(window != nullptr){
		if(iconfied_status == GLFW_TRUE){
			cout << "Iconfied Event!" << endl;
		}
		if(iconfied_status == GLFW_FALSE){
			cout << "Iconfied Restore Event!" << endl;
		}
	}
	return;
}
void Window::callbackMaximum(GLFWwindow* const window, const int maximum_status) noexcept{
	if(window != nullptr){
		if(maximum_status == GLFW_TRUE){
			cout << "Maximum Event!" << endl;
		}
		if(maximum_status == GLFW_FALSE){
			cout << "Maximum Restore Event!" << endl;
		}
	}
	return;
}
void Window::callbackFocus(GLFWwindow* const window, const int focus_status) noexcept{
	if(window != nullptr){
		if(focus_status == GLFW_TRUE){
			cout << "Get Focus!" << endl;
		}
		if(focus_status == GLFW_FALSE){
			cout << "Lost Focus!" << endl;
		}
	}
	return;
}

void Window::setupWindowHint(const GLFWvidmode& video_mode, const bool is_supported_vulkan) const noexcept(false){
	glfwWindowHint(GLFW_RESIZABLE,						GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE,						GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED,						GLFW_TRUE);
	glfwWindowHint(GLFW_FOCUSED,						GLFW_TRUE);
	glfwWindowHint(GLFW_AUTO_ICONIFY,					GLFW_TRUE);
	glfwWindowHint(GLFW_FLOATING,						GLFW_FALSE);
	glfwWindowHint(GLFW_MAXIMIZED,						GLFW_FALSE);
	glfwWindowHint(GLFW_CENTER_CURSOR,					GLFW_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER,		GLFW_TRUE);
	glfwWindowHint(GLFW_FOCUS_ON_SHOW,					GLFW_TRUE);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR,				GLFW_TRUE);

	glfwWindowHint(GLFW_RED_BITS,						video_mode.redBits);
	glfwWindowHint(GLFW_GREEN_BITS,						video_mode.greenBits);
	glfwWindowHint(GLFW_BLUE_BITS,						video_mode.blueBits);
	glfwWindowHint(GLFW_ALPHA_BITS,						GLFW_DONT_CARE);
	glfwWindowHint(GLFW_DEPTH_BITS,						GLFW_DONT_CARE);
	glfwWindowHint(GLFW_STENCIL_BITS,					GLFW_DONT_CARE);
	glfwWindowHint(GLFW_ACCUM_RED_BITS,					0);
	glfwWindowHint(GLFW_ACCUM_GREEN_BITS,				0);
	glfwWindowHint(GLFW_ACCUM_BLUE_BITS,				0);
	glfwWindowHint(GLFW_ACCUM_ALPHA_BITS,				0);
	glfwWindowHint(GLFW_AUX_BUFFERS,					0);

	//Hard Condition
	glfwWindowHint(GLFW_STEREO,							GLFW_FALSE);
	glfwWindowHint(GLFW_SAMPLES,						GLFW_DONT_CARE);
	glfwWindowHint(GLFW_SRGB_CAPABLE,					GLFW_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER,					GLFW_TRUE);

	glfwWindowHint(GLFW_REFRESH_RATE,					video_mode.refreshRate);

	if(is_supported_vulkan){
		//for Vulkan
		glfwWindowHint(GLFW_CLIENT_API,					GLFW_NO_API);
	}
	else{
		//for OpenGL
		glfwWindowHint(GLFW_CLIENT_API,					GLFW_OPENGL_API);
		glfwWindowHint(GLFW_CONTEXT_CREATION_API,		GLFW_NATIVE_CONTEXT_API);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,		4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,		3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,		GLFW_TRUE);
#ifdef _DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,		GLFW_TRUE);
#elif
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,		GLFW_FALSE;
#endif
		glfwWindowHint(GLFW_OPENGL_PROFILE,				GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS,			GLFW_LOSE_CONTEXT_ON_RESET);
		glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR,	GLFW_RELEASE_BEHAVIOR_FLUSH);
		glfwWindowHint(GLFW_CONTEXT_NO_ERROR,			GLFW_TRUE);
	}
	
	//for macOS
	glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER,		GLFW_TRUE);
	glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING,		GLFW_TRUE);

	return;
}

void Window::loadIconImage() noexcept(false){
	constexpr size_t ICON_WIDTH		= 128;
	constexpr size_t ICON_HEIGHT	= 128;

	icon_.width		= static_cast<int>(ICON_WIDTH);
	icon_.height	= static_cast<int>(ICON_HEIGHT);
	std::array<std::array<std::array<unsigned char, 4>, ICON_WIDTH>, ICON_HEIGHT> color;
	for(size_t i(0); i < ICON_WIDTH; ++i){
		for(size_t j(0); j < ICON_HEIGHT; ++j){
			color[i][j][0] = static_cast<unsigned char>(i);
			color[i][j][1] = static_cast<unsigned char>(j);
			color[i][j][2] = 0;
			color[i][j][3] = 255;
		}
	}

	icon_.pixels = move(color.front().front().data());

	return;
}

void Window::setupCallback() const noexcept(false){
	glfwSetWindowCloseCallback(			main_window_,	callbackClose			);
	glfwSetWindowRefreshCallback(		main_window_,	callbackRefresh			);
	glfwSetWindowSizeCallback(			main_window_,	callbackSize			);
	glfwSetFramebufferSizeCallback(		main_window_,	callbackFramebuffer		);
	glfwSetWindowContentScaleCallback(	main_window_,	callbackContentScale	);
	glfwSetWindowPosCallback(			main_window_,	callbackPosition		);
	glfwSetWindowIconifyCallback(		main_window_,	callbackIconfy			);
	glfwSetWindowMaximizeCallback(		main_window_,	callbackMaximum			);
	glfwSetWindowFocusCallback(			main_window_,	callbackFocus			);
	return;
}