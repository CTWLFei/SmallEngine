#include <se_core/se_graph/se_loader/OBJLoader.h>
#include <fstream>
#include <se_aux/Utils.h>

Face::Face(string v1, string v2, string v3)
{
	idxGroup[0] = parseLine(v1);
	idxGroup[1] = parseLine(v2);
	idxGroup[2] = parseLine(v3);
}
IdxGroup Face::parseLine(string line)
{
	IdxGroup result;
	vector<string> tokens;
	Utils::SplitString(line, tokens, "/");
	result.idxPos = atoi(tokens[0].c_str()) - 1;
	if (tokens.size() > 1) {
		string texCoord = tokens[1];
		result.idxTextCoord = texCoord.size() > 0 ? atoi(tokens[1].c_str()) - 1 : IdxGroup::NO_VALUE; //texCoord is not necessory
		if(tokens.size() > 2)
			result.idxVecNormal = atoi(tokens[2].c_str()) - 1;
	}
	return result;
}

Mesh* OBJLoader::loadMesh(string fileName)
{
	vector<vec3> vertices;
	vector<vec2> textures;
	vector<vec3> normals;
	vector<Face> faces;
	vector<string> lines;

	ifstream readFile(fileName);
	if (readFile.is_open()) {
		string s;
		while (getline(readFile, s)) {
			vector<string> tokens1;
			//vector<string> tokens2;
			lines.push_back(s);
			Utils::SplitString(s, tokens1, " ");
			/*for (int i = 0; i < tokens1.size(); i++) {
				Utils::SplitString(tokens1[i], tokens2, "\\");
			}*/
			if (tokens1.size() == 0) continue;
			if (tokens1[0] == "v") {
				vec3 vertex;
				vertex[0] = atof(tokens1[1].c_str());
				vertex[1] = atof(tokens1[2].c_str());
				vertex[2] = atof(tokens1[3].c_str());
				vertices.push_back(vertex);
			}
			else if (tokens1[0] == "vt") {
				vec2 texCoord;
				texCoord[0] = atof(tokens1[1].c_str());
				texCoord[1] = atof(tokens1[2].c_str());
				textures.push_back(texCoord);
			}
			else if (tokens1[0] == "vn") {
				vec3 vertexNormal;
				vertexNormal[0] = atof(tokens1[1].c_str());
				vertexNormal[1] = atof(tokens1[2].c_str());
				vertexNormal[2] = atof(tokens1[3].c_str());
				normals.push_back(vertexNormal);
			}
			else if (tokens1[0] == "f") {
				faces.push_back(Face(tokens1[1], tokens1[2], tokens1[3]));
			}
		}
	}
	readFile.close();
	return reorderLists(vertices, textures, normals, faces);
}

Mesh* OBJLoader::reorderLists(vector<vec3>& posList, vector<vec2>& texCoordList,
	vector<vec3>& normalList, vector<Face>& faceList)
{
	vector<int> indices;
	vector<float> posArr;
	posArr.resize(posList.size() * 3);
	for (int i = 0; i < posList.size(); ++i) {
		posArr[i * 3] = posList[i][0];
		posArr[i * 3 + 1] = posList[i][1];
		posArr[i * 3 + 2] = posList[i][2];
	}
	vector<float> texCoordArr;
	texCoordArr.resize(posList.size() * 2);
	vector<float> normalArr;
	normalArr.resize(posList.size() * 3);

	for (int i = 0; i < faceList.size(); ++i) {
		for (int j = 0; j < 3; j++) {
			IdxGroup faceVertexIndex = faceList[i].getFaceVertexIndex(j);
			processFaceVertex(faceVertexIndex, texCoordList, normalList,
				indices, texCoordArr, normalArr);
		}
	}
	Mesh* mesh = new Mesh(posArr, texCoordArr, normalArr, indices);
	return mesh;
}

void OBJLoader::processFaceVertex(const IdxGroup& indices, const vector<vec2>& textCoordList,
	const vector<vec3>& normList, vector<int>& indicesList,
	vector<float>& texCoordArr, vector<float>& normArr)
{
	int posIndex = indices.idxPos;
	indicesList.push_back(posIndex);

	// Reorder texture coordinates
	if (indices.idxTextCoord >= 0) {
		vec2 textCoord = textCoordList[indices.idxTextCoord];
		texCoordArr[posIndex * 2] = textCoord[0];
		texCoordArr[posIndex * 2 + 1] = 1 - textCoord[1];
	}
	if (indices.idxVecNormal >= 0) {
		// Reorder vectornormals
		vec3 vecNorm = normList[indices.idxVecNormal];
		normArr[posIndex * 3] = vecNorm[0];
		normArr[posIndex * 3 + 1] = vecNorm[1];
		normArr[posIndex * 3 + 2] = vecNorm[2];
	}
}