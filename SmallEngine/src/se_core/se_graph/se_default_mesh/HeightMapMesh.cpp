#include <se_core/se_graph/se_default_mesh/HeightMapMesh.h>

float HeightMapMesh::StartX = -0.5;
float HeightMapMesh::StartZ = -0.5;
int HeightMapMesh::MaxColour = 255 * 255 * 255;

HeightMapMesh::HeightMapMesh(float mixY, float maxY, const unsigned char* heightMapImage,
	int width, int height, std::string textureFile, int texInc)
{
	this->minY = minY;
	this->maxY = maxY;

	Texture* texture = new Texture(textureFile);

	float incx = GetXLength() / (width - 1);
	float incz = GetZLength() / (height - 1);

	std::vector<float> positions, textCoords;
	std::vector<int> indices;

	for (int row = 0; row < height; row++)
	{
		std::vector<float> colHeights;
		for (int col = 0; col < width; col++)
		{
			// Create vertex for current position
			positions.push_back(StartX + col * incx);
			float currentHeight = GetHeight(col, row, width, heightMapImage);
			colHeights.push_back(currentHeight);
			positions.push_back(currentHeight);
			positions.push_back(StartZ + row * incz);
			// Set texture coordinates
			textCoords.push_back((float)texInc * (float)col / (float)width);
			textCoords.push_back((float)texInc * (float)row / (float)height);

			// Create indices
			if (col < width - 1 && row < height - 1) {
				int leftTop = row * width + col;
				int leftBottom = (row + 1) * width + col;
				int rightBottom = (row + 1) * width + col + 1;
				int rightTop = row * width + col + 1;

				indices.push_back(rightTop);
				indices.push_back(leftBottom);
				indices.push_back(rightBottom);

				indices.push_back(leftTop);
				indices.push_back(leftBottom);
				indices.push_back(rightTop);
			}
		}
		heightArray.push_back(colHeights);
	}
	std::vector<float> normals = CalcNormals(positions, width, height);
	mesh = new Mesh(positions, textCoords, normals, indices);
	Material* material = new Material(texture, 0.0f);
	mesh->setMaterial(material);
}

float HeightMapMesh::GetHeight(int row, int col)
{
	float result = 0;
	if (row >= 0 && row < heightArray.size()) {
		if (col >= 0 && col < heightArray[row].size()) {
			result = heightArray[row][col];
		}
	}
	return result;
}

float HeightMapMesh::GetXLength()
{
	return abs(-StartX * 2);
}
float HeightMapMesh::GetZLength()
{
	return abs(-StartZ * 2);
}

std::vector<float> HeightMapMesh::CalcNormals(std::vector<float> posArr, int width, int height)
{
	vec3 v0, v1, v2, v3, v4, v12, v23, v34, v41;
	std::vector<float> normals;
	vec3 normal;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (row > 0 && row < height - 1 && col > 0 && col < width - 1) {
				int i0 = row * width * 3 + col * 3;
				v0[0] = posArr[i0];
				v0[1] = posArr[i0 + 1];
				v0[2] = posArr[i0 + 2];

				int i1 = row * width * 3 + (col - 1) * 3;
				v1[0] = posArr[i1];
				v1[1] = posArr[i1 + 1];
				v1[2] = posArr[i1 + 2];
				v1 = v1 - v0;

				int i2 = (row + 1)*width * 3 + col * 3;
				v2[0] = posArr[i2];
				v2[1] = posArr[i2 + 1];
				v2[2] = posArr[i2 + 2];
				v2 = v2 - v0;

				int i3 = (row)*width * 3 + (col + 1) * 3;
				v3[0] = posArr[i3];
				v3[1] = posArr[i3 + 1];
				v3[2] = posArr[i3 + 2];
				v3 = v3 - v0;

				int i4 = (row - 1)*width * 3 + col * 3;
				v4[0] = posArr[i4];
				v4[1] = posArr[i4 + 1];
				v4[2] = posArr[i4 + 2];
				v4 = v4 - v0;

				v1 = cross(v2, v12);
				v12 = normalize(v12);

				v2 = cross(v3, v23);
				v23 = normalize(v23);

				v3 = cross(v4, v34);
				v34 = normalize(v34);

				v4 = cross(v1, v41);
				v41 = normalize(v41);

				normal = v12 + v23 + v34 + v41;
				normal = normalize(normal);
			}
			else {
				normal[0] = 0;
				normal[1] = 1;
				normal[2] = 0;
			}
			normal = normalize(normal);
			normals.push_back(normal[0]);
			normals.push_back(normal[1]);
			normals.push_back(normal[2]);
		}
	}
	return normals;
}
float HeightMapMesh::GetHeight(int x, int z, int width, const unsigned char* buffer)
{
	unsigned char r = buffer[x * 4 + 0 + z * 4 * width];
	unsigned char g = buffer[x * 4 + 1 + z * 4 * width];
	unsigned char b = buffer[x * 4 + 2 + z * 4 * width];
	unsigned char a = buffer[x * 4 + 3 + z * 4 * width];
	int argb = ((0xFF & a) << 24) | ((0xFF & r) << 16)
		| ((0xFF & g) << 8) | (0xFF & b);
	return minY + abs(maxY - minY) * ((float)argb / (float)MaxColour);
}