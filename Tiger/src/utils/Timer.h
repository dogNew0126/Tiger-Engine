#pragma once

namespace tiger {

	class Timer {
	private:
		double startTime;
	public:

		Timer();

		void reset();

		// Getter
		inline double elapsed() const { return glfwGetTime() - startTime; }
	};
}