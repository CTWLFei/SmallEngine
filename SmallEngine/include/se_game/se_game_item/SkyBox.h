#ifndef __SKYBOX_H__
#define __SKYBOX_H__
#include "../GameItem.h"
#include "../../se_core/se_graph/se_loader/OBJLoader.h"

class SkyBox : public GameItem
{
public:
	SkyBox(std::string objPath, std::string texturePath) {
		Mesh* skyBoxMesh = OBJLoader::loadMesh(objPath);
		Texture* skyBoxtexture = new Texture(texturePath);
		skyBoxMesh->setMaterial(new Material(skyBoxtexture, 0.0f));
		setMesh(skyBoxMesh);
		setPosition(0, 0, 0);
	}
};

#endif