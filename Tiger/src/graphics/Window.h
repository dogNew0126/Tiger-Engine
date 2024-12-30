#pragma once

#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include "input/InputManager.h"

namespace tiger {

	static InputManager g_InputManager;

	class Window {
	private:
		const char* m_Title;
		GLFWwindow* m_Window;
		bool m_HideCursor;

		static int s_Width, s_Height;

	public:

		Window(const char* title, int width, int height);
		~Window();

		void update();
		static void clear();
		bool closed() const;

		static inline int getWidth() { return s_Width; }
		static inline int getHeight() { return s_Height; }

	private:
		bool init();

		void setFullScreenResolution();

	};

}