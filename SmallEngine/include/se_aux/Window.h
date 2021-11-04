#ifndef __WINDOW2_H__
#define __WINDOW2_H__
#include <iostream>
#include <string>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
using namespace std;

class Window
{
public:
	static void SetActiveWindow(Window* window) { Window::currentActiveWindow = window; }

	Window(string title, int width, int height, bool vSync) 
	{
		this->title = title;
		this->width = width;
		this->height = height;
		this->vSync = vSync;
		this->resized = false;
	}
	~Window() { }

	void SetResize(bool resized) { this->resized = resized; }
	void setClearColor(float r, float g, float b, float alpha) { glClearColor(r, g, b, alpha); }
	bool isKeyPressed(int keyCode) {
		return glfwGetKey(windowHandle, keyCode) == GLFW_PRESS;
	}
	bool isKeyReleased(int keyCode) {
		return glfwGetKey(windowHandle, keyCode) == GLFW_RELEASE;
	}
	bool windowShouldClose() { return glfwWindowShouldClose(windowHandle); }
	string getTitle() { return title; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	void setWidth(int width) { this->width = width; }
	void setHeight(int height) { this->height = height; }
	bool isResized() { return resized; }
	void setResized(bool resized) { this->resized = resized; }
	bool isvSync() { return vSync; }
	void setvSync(bool vSync) { this->vSync = vSync; }
	void active() { Window::currentActiveWindow = this; }
	void update() {
		glfwSwapBuffers(windowHandle);
		glfwPollEvents();
		//glFlush();
	}
	GLFWwindow* getWindowHandle() { return windowHandle; }
	void init();

private:
	static Window* currentActiveWindow;
	string title;
	int width;
	int height;
	GLFWwindow* windowHandle;
	bool resized;
	bool vSync;
};

#endif