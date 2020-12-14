#ifndef __FOG_H__
#define __FOG_H__
#include <vmath.h>
using namespace vmath;
class Fog
{
public:
	Fog() {
		active = false;
		this->colour = vec3(0.0);
		this->density = 0;
	}

	Fog(bool active, vec3 colour, float density) {
		this->colour = colour;
		this->density = density;
		this->active = active;
	}

	/**
	 * @return the active
	 */
	bool IsActive() {
		return active;
	}

	/**
	 * @param active the active to set
	 */
	void SetActive(bool active) {
		this->active = active;
	}

	/**
	 * @return the color
	 */
	vec3 GetColour() {
		return colour;
	}

	/**
	 * @param colour the color to set
	 */
	void SetColour(vec3 colour) {
		this->colour = colour;
	}

	/**
	 * @return the density
	 */
	float GetDensity() {
		return density;
	}

	/**
	 * @param density the density to set
	 */
	void SetDensity(float density) {
		this->density = density;
	}
private:
	bool active;
	vec3 colour;
	float density;
};

#endif