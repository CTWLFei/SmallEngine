#ifndef __MESH_H__
#define __MESH_H__
#include "../se_gl_component/Texture.h"
#include <vector>

class Mesh {
public:
	Mesh() { }
	Mesh(float* positions, int positionCount, float* textCoords, int textCoordCount, int* indices, int indexCount, Texture* texture);
	~Mesh();
	int getVaoId() { return this->vaoId; }
	int getVertexCount() { return this->vertexCount; }
	void render();
	void cleanup();
	int getTextureId() { return texture->id(); }
private:
	GLuint vaoId;
	std::vector<GLuint> vboIdList;
	int vertexCount;
	Texture* texture;
};

#endif