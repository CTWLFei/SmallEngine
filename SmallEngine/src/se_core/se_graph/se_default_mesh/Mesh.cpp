#include <se_core/se_graph/se_default_mesh/Mesh.h>


vec3 Mesh::DEFAULT_COLOUR = vec3(1.0);
Mesh::Mesh(float* positions, int positionCount, float* textCoords, int textCoordCount, float* normals, int normalsCount, int* indices, int indexCount)
{
	this->vertexCount = indexCount;

	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	// Position VBO
	GLuint vboId = 0;
	glGenBuffers(1, &vboId);
	vboIdList.push_back(vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionCount * 3, positions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

	// Texture coordinates VBO
	glGenBuffers(1, &vboId);
	vboIdList.push_back(vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * textCoordCount * 2, textCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

	// Vertex normals VBO
	glGenBuffers(1, &vboId);
	vboIdList.push_back(vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normalsCount * 3, normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, 0);

	// Index VBO
	glGenBuffers(1, &vboId);
	vboIdList.push_back(vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indexCount, indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
Mesh::Mesh(vector<float> positions, vector<float> textCoords, vector<float> normals, vector<int> indices)
{
	vertexCount = indices.size();

	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	// Position VBO
	GLuint vboId;
	glGenBuffers(1, &vboId);
	vboIdList.push_back(vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions.size(), positions.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

	// Texture coordinates VBO
	glGenBuffers(1, &vboId);
	vboIdList.push_back(vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * textCoords.size(), textCoords.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

	// Vertex normals VBO
	glGenBuffers(1, &vboId);
	vboIdList.push_back(vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size(), normals.data(),GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, 0);

	// Index VBO
	glGenBuffers(1, &vboId);
	vboIdList.push_back(vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), indices.data(),GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
Mesh::~Mesh()
{
	
}
void Mesh::render()
{
	initRender();

	glDrawElements(GL_TRIANGLES, getVertexCount(), GL_UNSIGNED_INT, 0);

	endRender();
}

void Mesh::renderList(vector<GameItem*>& gameItems, SetupGameItemCallback callback)
{
	initRender();
	for (int i = 0; i < gameItems.size(); i++)
	{
		callback(gameItems[i]);

		glDrawElements(GL_TRIANGLES, getVertexCount(), GL_UNSIGNED_INT, 0);
	}
	endRender();
}

void Mesh::cleanUp()
{
	glDisableVertexAttribArray(0);

	// Delete the VBOs
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	for (GLuint vboId : vboIdList) {
		glDeleteBuffers(1, &vboId);
	}

	// Delete the texture
	Texture* texture = material->getTexture();
	if(texture)
		texture->cleanup();

	// Delete the VAO
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vaoId);
}

void Mesh::deleteBuffers()
{
	glDisableVertexAttribArray(0);

	// Delete the VBOs
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	for (GLuint vboId : vboIdList) {
		glDeleteBuffers(1, &vboId);
	}

	// Delete the VAO
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vaoId);
}

void Mesh::initRender()
{
	Texture* texture = material->getTexture();
	Texture* normalMap = material->getNormalMap();

	if (texture)
	{
		// Activate first texture bank
		glActiveTexture(GL_TEXTURE0);
		// Bind the texture
		glBindTexture(GL_TEXTURE_2D, texture->id());
	}
	if (normalMap)
	{
		// Activate second texture bank
		glActiveTexture(GL_TEXTURE1);
		// Bind the texture
		glBindTexture(GL_TEXTURE_2D, normalMap->id());
	}

	// Draw the mesh
	glBindVertexArray(getVaoId());
}

void Mesh::endRender()
{
	// Restore state
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
}