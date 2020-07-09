#ifndef __SPOTLIGHT_H__
#define __SPOTLIGHT_H__

#include "PointLight.h"
class SpotLight {
public:
	SpotLight(PointLight* pointLight, vec3 coneDir, float cutOffAngle) {
		this->pointLight = pointLight;
		this->coneDirection = coneDirection;
		setCutOffAngle(cutOffAngle);
	}
	SpotLight(SpotLight& spotLight)
	{
		this->pointLight = spotLight.getPointLight();
		this->coneDirection = spotLight.getConeDirection();
		this->cutOff = spotLight.getCutOff();
	}
	PointLight* getPointLight() { return pointLight; }
	vec3 getConeDirection() { return coneDirection; }
	float getCutOff() { return cutOff; }
	void setPointLight(PointLight* pointLight) { this->pointLight = pointLight; }
	void setConeDirection(vec3& coneDirection) { this->coneDirection = coneDirection; }
	void setCutOff(float cutOff) { this->cutOff = cutOff; }
	void setCutOffAngle(float cutOffAngle) {
		setCutOff(cos(cutOffAngle / 180.0 * PI));
	}
private:
	PointLight* pointLight;
	vec3 coneDirection;
	float cutOff;
};

#endif