#include <se_core/MouseInput.h>

MouseInput* MouseInput::activeMouseInput = NULL;
MouseInput::MouseInput()
{
	previousPos = vec2(-1, -1);
	currentPos = vec2(0, 0);
	displVec = vec2(0, 0);
}
void MouseInput::init(Window* window)
{
	glfwSetCursorPosCallback(window->getWindowHandle(), [](GLFWwindow* windowHandle, double xpos, double ypos) {
		activeMouseInput->setCurrentPos(xpos, ypos);
	});
	glfwSetCursorEnterCallback(window->getWindowHandle(), [](GLFWwindow* windowHandle, int entered) {
		activeMouseInput->setInWindowState(entered);
	});
	glfwSetMouseButtonCallback(window->getWindowHandle(), [](GLFWwindow* windowHandle, int button, int action, int mode) {
		activeMouseInput->setLeftButtonPressed(button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS);
		activeMouseInput->setRightButtonPressed(button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS);
	});
}
void MouseInput::input(Window* window)
{
	displVec[0] = 0;
	displVec[1] = 0;
	if (previousPos[0] > 0 && previousPos[1] > 0 && inWindow) {
		double deltax = currentPos[0] - previousPos[0];
		double deltay = currentPos[1] - previousPos[1];
		bool rotateX = deltax != 0;
		bool rotateY = deltay != 0;
		if (rotateX) {
			displVec[1] = (float)deltax;
		}
		if (rotateY) {
			displVec[0] = (float)deltay;
		}
	}
	previousPos[0] = currentPos[0];
	previousPos[1] = currentPos[1];
}

void MouseInput::setCurrentPos(float posX, float posY)
{
	currentPos[0] = posX;
	currentPos[1] = posY;
}