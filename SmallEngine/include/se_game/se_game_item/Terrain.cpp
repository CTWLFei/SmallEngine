#include "Terrain.h"
#include <freeImage/FreeImage.h>

Terrain::Terrain(int terrainSize, float scale, float minY, float maxY,
	std::string heightMapFile, std::string textureFile, int texInc)
{
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(heightMapFile.c_str());
	FIBITMAP* dib = FreeImage_Load(fif, heightMapFile.c_str(), 0);
	FreeImage_FlipVertical(dib);
	if (dib == NULL)
		LOGGER_ERROR("load picture failed!");
	dib = FreeImage_ConvertTo32Bits(dib);

	BYTE* pixel;
	int width = FreeImage_GetWidth(dib);
	int height = FreeImage_GetHeight(dib);
	pixel = FreeImage_GetBits(dib);

	verticesPerCol = width - 1;
	verticesPerRow = height - 1;

	heightMapMesh = new HeightMapMesh(minY, maxY, pixel, width, height, textureFile, texInc);
	for (int row = 0; row < terrainSize; row++) {
		std::vector<Box2D*> colBoundingbox;
		for (int col = 0; col < terrainSize; col++) {
			float xDisplacement = (col - ((float)terrainSize - 1) / (float)2) * scale * HeightMapMesh::GetXLength();
			float zDisplacement = (row - ((float)terrainSize - 1) / (float)2) * scale * HeightMapMesh::GetZLength();

			GameItem* terrainBlock = new GameItem(heightMapMesh->GetMesh());
			terrainBlock->setScale(scale);
			terrainBlock->setPosition(xDisplacement, 0, zDisplacement);
			gameItems.push_back(terrainBlock);

			colBoundingbox.push_back(GetBoundingBox(terrainBlock));
		}
		boundingBoxes.push_back(colBoundingbox);
	}

	FreeImage_Unload(dib);
}
float Terrain::GetHeight(vec3 position)
{
	float result = FLT_MIN;
	Box2D* boundingBox = nullptr;
	bool found = false;
	GameItem* terrainBlock = nullptr;
	for (int row = 0; row < terrainSize && !found; row++)
	{
		for (int col = 0; col < terrainSize && !found; col++)
		{
			terrainBlock = gameItems[row * terrainSize + col];
			boundingBox = boundingBoxes[row][col];
			found = boundingBox->contains(position[0], position[2]);
		}
	}
	if (found)
	{
		std::vector<vec3> triangle = GetTriangle(position, boundingBox, terrainBlock);
		result = InterpolateHeight(triangle[0], triangle[1], triangle[2], position[0], position[2]);
	}
	return result;
}
std::vector<vec3> Terrain::GetTriangle(vec3 position, Box2D* boundingBox, GameItem* terrainBlock)
{
	float cellWidth = boundingBox->width / (float)verticesPerCol;
	float cellHeight = boundingBox->height / (float)verticesPerRow;
	int col = (int)((position[0] - boundingBox->x) / cellWidth);
	int row = (int)((position[2] - boundingBox->y) / cellHeight);

	std::vector<vec3> triangle;
	triangle.push_back(vec3());
	triangle.push_back(vec3(
		boundingBox->x + col * cellWidth,
		GetWorldHeight(row + 1, col, terrainBlock),
		boundingBox->y + (row + 1) * cellHeight));
	triangle.push_back(vec3(
		boundingBox->x + (col + 1) * cellWidth,
		GetWorldHeight(row, col + 1, terrainBlock),
		boundingBox->y + row * cellHeight));
	if (position[2] < GetDiagonalZCoord(triangle[1][0], triangle[1][2], triangle[2][0], triangle[2][2], position[0])) {
		triangle[0] = vec3(
			boundingBox->x + col * cellWidth,
			GetWorldHeight(row, col, terrainBlock),
			boundingBox->y + row * cellHeight);
	}
	else {
		triangle[0] = vec3(
			boundingBox->x + (col + 1) * cellWidth,
			GetWorldHeight(row + 2, col + 1, terrainBlock),
			boundingBox->y + (row + 1) * cellHeight);
	}
	return triangle;
}
float Terrain::GetDiagonalZCoord(float x1, float z1, float x2, float z2, float x)
{
	float z = ((z1 - z2) / (x1 - x2)) * (x - x1) + z1;
	return z;
}
float Terrain::GetWorldHeight(int row, int col, GameItem* gameItem)
{
	float y = heightMapMesh->GetHeight(row, col);
	return y * gameItem->getScale() + gameItem->getPosition()[1];
}
float Terrain::InterpolateHeight(vec3 pA, vec3 pB, vec3 pC, float x, float z)
{
	// Plane equation ax+by+cz+d=0
	float a = (pB[1] - pA[1]) * (pC[2] - pA[2]) - (pC[1] - pA[1]) * (pB[2] - pA[2]);
	float b = (pB[2] - pA[2]) * (pC[0] - pA[0]) - (pC[2] - pA[2]) * (pB[0] - pA[0]);
	float c = (pB[0] - pA[0]) * (pC[1] - pA[1]) - (pC[0] - pA[0]) * (pB[1] - pA[1]);
	float d = -(a * pA[0] + b * pA[1] + c * pA[2]);
	// y = (-d -ax -cz) / b
	float y = (-d - a * x - c * z) / b;
	return y;
}
Box2D* Terrain::GetBoundingBox(GameItem* terrainBlock)
{
	float scale = terrainBlock->getScale();
	vec3 position = terrainBlock->getPosition();

	float topLeftX = HeightMapMesh::StartX * scale + position[0];
	float topLeftZ = HeightMapMesh::StartZ * scale + position[2];
	float width = abs(HeightMapMesh::StartX * 2) * scale;
	float height = abs(HeightMapMesh::StartZ * 2) * scale;
	Box2D* boundingBox = new Box2D(topLeftX, topLeftZ, width, height);
	return boundingBox;
}
std::vector<GameItem*> Terrain::GetGameItems()
{
	return gameItems;
}