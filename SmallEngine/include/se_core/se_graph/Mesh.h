#ifndef __MESH_H__
#define __MESH_H__
#include "../se_gl_component/Texture.h"
#include <vector>
#include <vmath.h>
#include <functional>
#include "se_material/Material.h"
//#include <se_game/GameItem.h>
using namespace std;
using namespace vmath;

class GameItem;

typedef function<void(GameItem*)> SetupGameItemCallback;
class Mesh {
public:
	Mesh() { }
	Mesh(float* positions, int positionCount, float* textCoords, int textCoordCount, int* indices, int indexCount);
	Mesh(vector<float> positions, vector<float> textCoords, vector<float> normals, vector<int> indices);
	~Mesh();
	int getVaoId() { return this->vaoId; }
	int getVertexCount() { return this->vertexCount; }
	void render();
	void renderList(vector<GameItem*>& gameItems, SetupGameItemCallback callback);
	void cleanUp();
	void deleteBuffers();
	void setMaterial(Material* material) { this->material = material; }
	Material* getMaterial() { return material; }
private:
	void initRender();
	void endRender();

private:
	static vec3 DEFAULT_COLOUR;
	GLuint vaoId;
	vector<GLuint> vboIdList;
	int vertexCount;
	Material* material;
};

#endif