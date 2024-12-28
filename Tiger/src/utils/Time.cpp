#include "pch.h"
#include "Time.h"

namespace tiger {

	Time::Time() {
		lastFrame = glfwGetTime();
		delta = 0.0;
	}

	void Time::update() {
		GLdouble currentFrame = glfwGetTime();
		delta = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
}