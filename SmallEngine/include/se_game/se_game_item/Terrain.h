#ifndef __TERRAIN_H__
#define __TERRAIN_H__
#include "../GameItem.h"
#include "../../se_core/se_graph/se_default_mesh/HeightMapMesh.h"

class Box2D 
{
public:
	Box2D(float x, float y, float width, float height) 
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
	bool contains(float x2, float y2) 
	{
		return x2 >= x
			&& y2 >= y
			&& x2 < x + width
			&& y2 < y + height;
	}
	float x;
	float y;
	float width;
	float height;
};

class Terrain
{
public:
	Terrain(int terrainSize, float scale, float minY, float maxY,
		std::string heightMapFile, std::string textureFile, int texInc);
	
	float GetHeight(vec3 position);
	std::vector<GameItem*> GetGameItems();

protected:
	std::vector<vec3> GetTriangle(vec3 position, Box2D* boundingBox, GameItem* terrainBlock);
	float GetDiagonalZCoord(float x1, float z1, float x2, float z2, float x);
	float GetWorldHeight(int row, int col, GameItem* gameItem);
	float InterpolateHeight(vec3 pA, vec3 pB, vec3 pC, float x, float z);
	Box2D* GetBoundingBox(GameItem* terrainBlock);
	
private:
	std::vector<GameItem*> gameItems;
	int terrainSize;
	int verticesPerCol;
	int verticesPerRow;
	HeightMapMesh* heightMapMesh;
	std::vector<std::vector<Box2D*>> boundingBoxes;
};	

#endif