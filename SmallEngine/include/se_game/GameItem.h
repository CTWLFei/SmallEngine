#ifndef __GAMEITEM_H__
#define __GAMEITEM_H__
#include <vmath.h>
#include <se_core/se_graph/Mesh.h>

using namespace vmath;
class GameItem {
public:
	GameItem() {};
	GameItem(Mesh* mesh)
	{
		this->mesh = mesh;
		scale = 1;
	}
	~GameItem(){ }

	vec3 getPosition() { return position; }

	void setPosition(float x, float y, float z) {
		this->position[0] = x;
		this->position[1] = y;
		this->position[2] = z;
	}
	float getScale() {return scale;}

	void setScale(float scale) { this->scale = scale; }

	vec3 getRotation() {return rotation;}

	void setRotation(float x, float y, float z) {
		this->rotation[0] = x;
		this->rotation[1] = y;
		this->rotation[2] = z;
	}

	Mesh* getMesh() { return mesh; }
	void setMesh(Mesh* mesh) { this->mesh = mesh; }
private:
	Mesh* mesh;
	vec3 position;
	float scale;
	vec3 rotation;
};

#endif
