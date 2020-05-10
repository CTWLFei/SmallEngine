#ifndef __OBJLOADER_H__
#define __OBJLOADER_H__
#include <vmath.h>
#include "../Mesh.h"
using namespace vmath;

class IdxGroup {
public:
	static const int NO_VALUE = -1;

	int idxPos;

	int idxTextCoord;

	int idxVecNormal;

	IdxGroup() {
		idxPos = NO_VALUE;
		idxTextCoord = NO_VALUE;
		idxVecNormal = NO_VALUE;
	}
};

class Face {
public:
	Face(string v1, string v2, string v3);
	IdxGroup getFaceVertexIndex(int index) { return idxGroup[index]; }
private:
	IdxGroup parseLine(string line);
private:
	IdxGroup idxGroup[3];
};

class OBJLoader {
public:
	static Mesh* loadMesh(string fileName);
protected:
	
private:
	static Mesh* reorderLists(vector<vec3>& posList, vector<vec2>& texCoordList,
		vector<vec3>& normalList, vector<Face>& faceList);
	
	static void processFaceVertex(const IdxGroup& indices, const vector<vec2>& textCoordList,
		const vector<vec3>& normList, vector<int>& indicesList,
		vector<float>& texCoordArr, vector<float>& normArr);
};

#endif