#ifndef __SCENE_H__
#define __SCENE_H__

#include "se_game_item/SkyBox.h"
#include "SceneLight.h"
#include "../se_core/se_graph/se_weather/Fog.h"
#include <map>
#include <vector>

class Scene {
public:
	Scene() 
	{
		fog = nullptr;
	}
	map<Mesh*, vector<GameItem*>> getGameMeshes() {
		return meshMap;
	}

	void setGameItem(GameItem* gameItem) {
		if (gameItem)
		{
			Mesh* mesh = gameItem->getMesh();
			meshMap[mesh].push_back(gameItem);
		}
	}

	void setGameItems(vector<GameItem*> gameItems) {
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

	/**
	 * @return the fog
	 */
	Fog* getFog() {
		return fog;
	}

	/**
	 * @param fog the fog to set
	 */
	void setFog(Fog* fog) {
		this->fog = fog;
	}

	void cleanup() {
		for (auto iter = meshMap.begin(); iter != meshMap.end(); iter++)
		{
			iter->first->cleanUp();
		}
	}

private:
	map<Mesh*, vector<GameItem*>> meshMap;
	SkyBox* skyBox;
	SceneLight* sceneLight;
	Fog* fog;
};

#endif