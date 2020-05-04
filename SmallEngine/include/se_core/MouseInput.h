#ifndef __MOUSEINPUT_H__
#define __MOUSEINPUT_H__
#include <vmath.h>
#include <se_aux/Window.h>
using namespace vmath;
class MouseInput {
public:
	MouseInput();
	~MouseInput() { }
	vec2 getDisplVec() { return displVec; }
	bool isLeftButtonPressed() {return leftButtonPressed;}
	bool isRightButtonPressed() {return rightButtonPressed;}
	void active(){ activeMouseInput = this; }

	void init(Window* window);
	void input(Window* window);
	void setCurrentPos(float posX, float posY);
protected:
	void setInWindowState(bool entered) { inWindow = entered; }
	void setLeftButtonPressed(bool state) { leftButtonPressed = state; }
	void setRightButtonPressed(bool state) { rightButtonPressed = state; }
private:
	static MouseInput* activeMouseInput;
	vec2 previousPos;
	vec2 currentPos;
	vec2 displVec;
	bool inWindow = false;
	bool leftButtonPressed = false;
	bool rightButtonPressed = false;
};

#endif