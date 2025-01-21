#pragma once

namespace tiger {

	class Timer {

	public:

		Timer();

		void reset();
		void rewind(double time);

		double elapsed() const;
	private:
		double m_StartTime;
	};
}