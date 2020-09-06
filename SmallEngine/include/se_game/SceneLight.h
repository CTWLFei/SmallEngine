#ifndef __SCENELIGHT_H__
#define __SCENELIGHT_H__

#include "../se_core/se_graph/se_light/DirectionalLight.h"
#include "../se_core/se_graph/se_light/SpotLight.h"
#include <vector>
class SceneLight {
public:
	vec3 getAmbientLight() {
		return ambientLight;
	}

	void setAmbientLight(vec3& ambientLight) {
		this->ambientLight = ambientLight;
	}

	void setAmbientLight(float r, float g, float b) {
		this->ambientLight = vec3(r, g, b);
	}

	std::vector<PointLight*>& getPointLightList() {
		return pointLightList;
	}

	void setPointLightList(std::vector<PointLight*> pointLightList) {
		this->pointLightList = pointLightList;
	}

	std::vector<SpotLight*>& getSpotLightList() {
		return spotLightList;
	}

	void setSpotLightList(std::vector<SpotLight*>& spotLightList) {
		this->spotLightList = spotLightList;
	}

	DirectionalLight* getDirectionalLight() {
		return directionalLight;
	}

	void setDirectionalLight(DirectionalLight* directionalLight) {
		this->directionalLight = directionalLight;
	}

private:
	vec3 ambientLight;
	std::vector<PointLight*> pointLightList;
	std::vector<SpotLight*> spotLightList;
	DirectionalLight* directionalLight;
};

#endif
