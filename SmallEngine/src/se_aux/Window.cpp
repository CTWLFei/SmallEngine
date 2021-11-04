#include <se_aux/Window.h>

void error_callback(int error, const char* description) {
	cout << "Error:" << error + description << endl;
}

Window* Window::currentActiveWindow = NULL;

void Window::init()
{
	// Setup an error callback.
	glfwSetErrorCallback(error_callback);
	// Initialize GLFW. Most GLFW functions will not work before doing this.
	if (!glfwInit()) {
		cout << "glfwInit failed!" << endl;
	}

	glfwDefaultWindowHints(); // optional, the current window hints are already the default
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE); // the window will stay hidden after creation
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); // the window will be resizable
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	windowHandle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (windowHandle == NULL) {
		cout << "create window failed!" << endl;
	}

	auto SizeCallback = [](GLFWwindow* window, int width, int height) {
		currentActiveWindow->setWidth(width);
		currentActiveWindow->setHeight(height);
		currentActiveWindow->SetResize(true);
	};
	auto KeyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
			glfwSetWindowShouldClose(window, true);
		}
	};
	glfwSetFramebufferSizeCallback(windowHandle, SizeCallback);
	glfwSetKeyCallback(windowHandle, KeyCallback);

	// Get the resolution of the primary monitor
	const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	// Center our window
	glfwSetWindowPos(windowHandle, (vidmode->width - width) / 2, (vidmode->height - height) / 2);
	// Make the OpenGL context current
	glfwMakeContextCurrent(windowHandle);

	if (isvSync())
		glfwSwapInterval(1);

	glfwShowWindow(windowHandle);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
}