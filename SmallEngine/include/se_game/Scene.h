#ifndef __SCENE_H__
#define __SCENE_H__

#include "se_game_item/SkyBox.h"
#include "SceneLight.h"
#include <map>
#include <vector>

class Scene {
public:
	Scene() {};
	map<Mesh*, vector<GameItem*>> getGameMeshes() {
		return meshMap;
	}

	void setGameItems(vector<GameItem*>& gameItems) {
		int numGameItems = gameItems.size();
		for (int i = 0; i < numGameItems; i++) {
			GameItem* gameItem = gameItems[i];
			Mesh* mesh = gameItem->getMesh();
			meshMap[mesh].push_back(gameItem);
		}
	}

	SkyBox* getSkyBox() {
		return skyBox;
	}

	void setSkyBox(SkyBox* skyBox) {
		this->skyBox = skyBox;
	}

	SceneLight* getSceneLight() {
		return sceneLight;
	}

	void setSceneLight(SceneLight* sceneLight) {
		this->sceneLight = sceneLight;
	}

private:
	map<Mesh*, vector<GameItem*>> meshMap;
	SkyBox* skyBox;
	SceneLight* sceneLight;
};

#endif