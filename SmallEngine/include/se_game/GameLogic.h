#ifndef __GAMELOGIC_H__
#define __GAMELOGIC_H__
#include <se_aux/Window.h>
#include <se_core/MouseInput.h>
class GameLogic
{
public:
	GameLogic() { }
	~GameLogic() { }

	virtual void init(Window* window) = 0;

	virtual void input(Window* window, MouseInput* mouseInput) = 0;

	virtual void update(float interval, MouseInput* mouseInput) = 0;

	virtual void render(Window* window) = 0;

	virtual void cleanup() = 0;
};

#endif