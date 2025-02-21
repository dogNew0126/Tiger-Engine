#include "pch.h"
#include "Window.h"

namespace tiger {

	bool Window::s_HideCursor;
	bool Window::s_HideUI;
	int Window::s_Width, Window::s_Height;

	Window::Window(const char* title, int width, int height) 
		: m_Title(title)
	{
		s_Width = width;
		s_Height = height;
		s_HideCursor = true;
		s_HideUI = false;

		if (!init()) {
			Logger::getInstance().error("logged_files/window_creation.txt", "Window Initialization", "Could not initialize window class");
			glfwDestroyWindow(m_Window);
			glfwTerminate();
		}
	}

	Window::~Window() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	bool Window::init() {
		// Needed in order to establish the correct OpenGL context (also enabled the usage of RenderDoc along with the window hints)
		glewExperimental = true;

		if (!glfwInit()) {
			Logger::getInstance().error("logged_files/window_creation.txt", "Window Initialization", "Could not initialize the GLFW window");
			std::cout << "GLFW Failed To Initialize" << std::endl;
			return false;
		}

		// Context hints
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

		// Window hints
		glfwWindowHint(GLFW_DOUBLEBUFFER, true);

		// Create the window and OpenGL context
		if (FULLSCREEN_MODE) {
			setFullScreenResolution();
			m_Window = glfwCreateWindow(s_Width, s_Height, m_Title, glfwGetPrimaryMonitor(), NULL);
		}
		else {
			m_Window = glfwCreateWindow(s_Width, s_Height, m_Title, NULL, NULL);
		}

		if (!m_Window) {
			Logger::getInstance().error("logged_files/window_creation.txt", "Window Initialization", "Could not create the GLFW window");
			std::cout << "GLFW Window Couldn't Be Created" << std::endl;
			return false;
		}

		// Setup the mouse settings
		if (s_HideCursor)
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		double currMouseX, currMouseY;
		glfwGetCursorPos(m_Window, &currMouseX, &currMouseY);
		s_InputManager.setMousePos(currMouseX, currMouseY);

		// Set up contexts and callbacks
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetErrorCallback([](int error, const char* description) {
			std::cout << "Error:" << std::endl << description << std::endl;
		});
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			if (width == 0 || height == 0) {
				win->s_Width = WINDOW_X_RESOLUTION;
				win->s_Height = WINDOW_Y_RESOLUTION;
			}
			else {
				win->s_Width = width;
				win->s_Height = height;
			}
			glViewport(0, 0, win->s_Width, win->s_Height);
		});
		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
		});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			s_InputManager.keyCallback(key, scancode, action, mods);
			ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
#if DEBUG_ENABLED
			if (key == GLFW_KEY_P && action == GLFW_RELEASE) {
				win->s_HideCursor = !win->s_HideCursor;
				GLenum cursorOption = win->s_HideCursor ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
				glfwSetInputMode(win->m_Window, GLFW_CURSOR, cursorOption);
			}
			if (key == GLFW_KEY_U && action == GLFW_RELEASE)
			{
				win->s_HideUI = !win->s_HideUI;
			}
#endif
		});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			s_InputManager.mouseButtonCallback(button, action, mods);
			ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
		});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			s_InputManager.cursorPositionCallback(xpos, ypos);
		});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			s_InputManager.scrollCallback(xoffset, yoffset);
			ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
		});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int c) {
			ImGui_ImplGlfw_CharCallback(window, c);
		});
		glfwSetJoystickCallback([](int joystick, int event) {
			s_InputManager.joystickCallback(joystick, event);
		});
		// Check to see if v-sync was enabled and act accordingly
		if (V_SYNC) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		// Initialize GLEW (allows us to use newer versions of OpenGL)
		if (glewInit() != GLEW_OK) {
			std::cout << "Could not Initialize GLEW" << std::endl;
			Logger::getInstance().error("logged_files/window_creation.txt", "Window Initialization", "Could not initialize the GLEW");
			return 0;
		}
		std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

		// Setup default OpenGL viewport
		glViewport(0, 0, s_Width, s_Height);

		// Setup ImGui bindings
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(m_Window, false);
		ImGui_ImplOpenGL3_Init("#version 430");
		ImGui::StyleColorsDark();

		// Error callback setup
#if DEBUG_ENABLED
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
			fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
		}, 0);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_LOW, 0, nullptr, GL_FALSE);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_MEDIUM, 0, nullptr, GL_TRUE);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
#endif

		// Everything was successful so return true
		return 1;
	}

	void Window::update()
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::cout << "OpenGL Error: " << error << std::endl;
		}
		// Input handling
		s_InputManager.update();

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void Window::clear(){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void Window::bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	bool Window::closed() const {
		return glfwWindowShouldClose(m_Window);
	}

	// Sets the Window's Size to the Primary Monitor's Resolution
	void Window::setFullScreenResolution() {
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		s_Width = mode->width;
		s_Height = mode->height;
	}

}