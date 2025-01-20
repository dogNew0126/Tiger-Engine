#pragma once

#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include "input/InputManager.h"

namespace tiger {

	static InputManager s_InputManager;

	class Window {

	public:

		Window(const char* title, int width, int height);
		~Window();

		void update();
		bool closed() const;
		static void clear();
		static void bind();

		static inline bool getHideCursor() { return s_HideCursor; }
		static inline int getWidth() { return s_Width; }
		static inline int getHeight() { return s_Height; }
		static inline int getRenderResolutionWidth() { return (int)(s_Width * SUPERSAMPLING_FACTOR); }
		static inline int getRenderResolutionHeight() { return (int)(s_Height * SUPERSAMPLING_FACTOR); }

	private:
		bool init();

		void setFullScreenResolution();

	private:
		const char* m_Title;
		GLFWwindow* m_Window;
		static bool s_HideCursor;
		static int s_Width, s_Height;

	};

}