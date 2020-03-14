#include "Monitor.hpp"
#include <iostream>

using namespace std;

Monitor::Monitor() noexcept(false){
	//Create Monitor Reference
	primary_monitor_ = glfwGetPrimaryMonitor();
	if(primary_monitor_ == nullptr){
		throw(runtime_error("Fail to Get Primary Monitor!"));
	}

	glfwSetMonitorCallback(callbackMonitor);

	current_video_mode_ = *glfwGetVideoMode(primary_monitor_);

	//Calculate Physical Monitor Size
	int physical_width_mm = 0;
	int physical_height_mm = 0;
	glfwGetMonitorPhysicalSize(primary_monitor_, &physical_width_mm, &physical_height_mm);
	physical_width_ = static_cast<float_t>(physical_width_mm) / 1000.0f;
	physical_height_ = static_cast<float_t>(physical_height_mm) / 1000.0f;

	glfwGetMonitorContentScale(primary_monitor_, &content_scale_[0], &content_scale_[1]);

	glfwGetMonitorWorkarea(primary_monitor_, &workarea_[0][0], &workarea_[0][1], &workarea_[1][0], &workarea_[1][1]);

	glfwSetMonitorUserPointer(primary_monitor_, nullptr);

	glfwSetGamma(primary_monitor_, 1.0f);
}

Monitor::~Monitor() noexcept(false){
}

void Monitor::callbackMonitor(GLFWmonitor* const monitor, const int event) noexcept{
	if(monitor != nullptr){
		if(event == GLFW_CONNECTED){
			clog << "Connected Monitor." << endl;
		}
		if(event == GLFW_DISCONNECTED){
			clog << "Disconnected Monitor." << endl;
		}
	}
	
	return;
}