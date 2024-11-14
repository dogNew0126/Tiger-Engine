#pragma once

#include <GLFW/glfw3.h>

namespace tiger {

	class Timer {
	private:
		double startTime;
	public:
		Timer();

		void reset();

		double elapsed();
	};
}