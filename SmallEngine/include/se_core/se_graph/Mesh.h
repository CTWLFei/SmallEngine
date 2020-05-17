#ifndef __MESH_H__
#define __MESH_H__
#include "../se_gl_component/Texture.h"
#include <vector>
#include <vmath.h>
#include "se_material/Material.h"
using namespace std;
using namespace vmath;
class Mesh {
public:
	Mesh() { }
	Mesh(float* positions, int positionCount, float* textCoords, int textCoordCount, int* indices, int indexCount);
	Mesh(vector<float> positions, vector<float> textCoords, vector<float> normals, vector<int> indices);
	~Mesh();
	int getVaoId() { return this->vaoId; }
	int getVertexCount() { return this->vertexCount; }
	void render();
	void cleanup();
	void setMaterial(Material* material) { this->material = material; }
	Material* getMaterial() { return material; }
private:
	static vec3 DEFAULT_COLOUR;
	GLuint vaoId;
	vector<GLuint> vboIdList;
	int vertexCount;
	Material* material;
};

#endif