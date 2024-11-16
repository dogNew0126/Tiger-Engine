#include "Timer.h"

namespace tiger {

	Timer::Timer() {
		startTime = glfwGetTime();
	}

	void Timer::reset() {
		startTime = glfwGetTime();
	}
};