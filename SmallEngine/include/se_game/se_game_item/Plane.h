#ifndef __PLANE_H__
#define __PLANE_H__

#include "../GameItem.h"

class Plane : public GameItem
{
public:
	Plane(vec2 size);
	virtual ~Plane();

private:
	vec2 m_size;
};

#endif