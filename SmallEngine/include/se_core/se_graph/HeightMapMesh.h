#ifndef __HEIGHTMAPMESH_H__
#define __HEIGHTMAPMESH_H__

#include "Mesh.h"
#include <vector>
#include <string>

class HeightMapMesh
{
public:
	HeightMapMesh(float mixY, float maxY, const unsigned char* heightMapImage,
		int width, int height, std::string textureFile, int texInc);

	Mesh* GetMesh() { return mesh; }

	float GetHeight(int row, int col);

public:
	static float GetXLength();
	static float GetZLength();
public:
	static float StartX;
	static float StartZ;

private:
	std::vector<float> CalcNormals(std::vector<float> posArr, int width, int height);
	float GetHeight(int x, int z, int width, const unsigned char* buffer);
private:
	static int MaxColour;
	float minY;
	float maxY;
	Mesh* mesh;
	std::vector<std::vector<float>> heightArray;
};

#endif