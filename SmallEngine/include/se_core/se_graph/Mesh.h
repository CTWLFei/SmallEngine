#ifndef __MESH_H__
#define __MESH_H__
#include "../se_gl_component/Texture.h"
#include <vector>
#include <vmath.h>
using namespace std;
using namespace vmath;
class Mesh {
public:
	Mesh() { }
	Mesh(float* positions, int positionCount, float* textCoords, int textCoordCount, int* indices, int indexCount, Texture* texture);
	Mesh(vector<float> positions, vector<float> textCoords, vector<float> normals, vector<int> indices);
	~Mesh();
	int getVaoId() { return this->vaoId; }
	int getVertexCount() { return this->vertexCount; }
	void render();
	void cleanup();
	void setTexture(Texture* texture) { this->texture = texture; }
	int getTextureId() { return texture->id(); }
private:
	static vec3 DEFAULT_COLOUR;
	GLuint vaoId;
	vector<GLuint> vboIdList;
	int vertexCount;
	Texture* texture;
	vec3 colour;
};

#endif