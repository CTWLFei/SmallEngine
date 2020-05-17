#ifndef __MATERIAL_H__
#define __MATERIAL_H__
#include <vmath.h>
#include <se_core/se_gl_component/Texture.h>
using namespace vmath;
class Material {
public:
	Material() {
		this->ambientColour = DEFAULT_COLOUR;
		this->diffuseColour = DEFAULT_COLOUR;
		this->specularColour = DEFAULT_COLOUR;
		this->texture = NULL;
		this->reflectance = 0;
	}

	Material(vec4& colour, float reflectance) {
		this->ambientColour = colour;
		this->diffuseColour = colour;
		this->specularColour = colour;
		this->texture = NULL;
		this->reflectance = reflectance;
	}

	Material(Texture* texture) {
		this->ambientColour = DEFAULT_COLOUR;
		this->diffuseColour = DEFAULT_COLOUR;
		this->specularColour = DEFAULT_COLOUR;
		this->texture = texture;
		this->reflectance = 0;
	}

	Material(Texture* texture, float reflectance) {
		this->ambientColour = DEFAULT_COLOUR;
		this->diffuseColour = DEFAULT_COLOUR;
		this->specularColour = DEFAULT_COLOUR;
		this->texture = texture;
		this->reflectance = reflectance;
	}

	Material(vec4& ambientColour, vec4& diffuseColour, vec4& specularColour, Texture* texture, float reflectance) {
		this->ambientColour = ambientColour;
		this->diffuseColour = diffuseColour;
		this->specularColour = specularColour;
		this->texture = texture;
		this->reflectance = reflectance;
	}

	vec4 getAmbientColour() {
		return ambientColour;
	}

	void setAmbientColour(vec4& ambientColour) {
		this->ambientColour = ambientColour;
	}

	vec4 getDiffuseColour() {
		return diffuseColour;
	}

	void setDiffuseColour(vec4& diffuseColour) {
		this->diffuseColour = diffuseColour;
	}

	vec4 getSpecularColour() {
		return specularColour;
	}

	void setSpecularColour(vec4& specularColour) {
		this->specularColour = specularColour;
	}

	float getReflectance() {
		return reflectance;
	}

	void setReflectance(float reflectance) {
		this->reflectance = reflectance;
	}

	bool isTextured() {
		return this->texture != NULL;
	}

	Texture* getTexture() {
		return texture;
	}

	void setTexture(Texture* texture) {
		this->texture = texture;
	}
private:
	static vec4 DEFAULT_COLOUR;
	vec4 ambientColour;
	vec4 diffuseColour;
	vec4 specularColour;
	float reflectance;
	Texture* texture;
};

#endif