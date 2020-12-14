#ifndef _SHADER_H_
#define _SHADER_H_
#include <GLAD/glad.h>
#include <string>
#include <fstream>
#include <map>

#include "../se_graph/se_light/PointLight.h"
#include "../se_graph/se_light/DirectionalLight.h"
#include "../se_graph/se_light/SpotLight.h"
#include "../se_graph/se_weather/Fog.h"
#include "../se_graph/se_material/Material.h"

class ShaderProgram
{
public:
	ShaderProgram(const std::string& vs, const std::string& fs);
	ShaderProgram(const std::string& vs, const std::string& fs, const std::string& gs);
	void bind();
	void unbind();
	void cleanup();
	void createUniform(std::string uniformName);
	//create lights' uniform
	void createPointLightUniform(std::string uniformName);
	void createPointLightUniform(std::string uniformName, int size);
	void createSpotLightUniform(std::string uniformName);
	void createSpotLightUniform(std::string uniformName, int size);
	void createDirectionalLightUniform(std::string uniformName);

	void createMaterialUniform(std::string uniformName);
	void createMaterialUniform(std::string uniformName, int size);

	void createFogUniform(std::string uniformName);
	
	void setFloatUniform(const char* name, float* values, int vec_size, int vec_num);
	void setMat4Uniform(const char* name, float* values, int size);
	void setIntUniform(const char* name, int* values, int vec_size, int vec_num);
	//set lights' uniform
	void setPointLightUniform(std::string uniformName, PointLight* pointLight);
	void setPointLightUniform(std::string uniformName, PointLight* pointLight, int pos);
	void setSpotLightUniform(std::string uniformName, SpotLight* spotLight);
	void setSpotLightUniform(std::string uniformName, SpotLight* spotLight, int pos);
	void setDirectionalLightUniform(std::string uniformName, DirectionalLight* dirLight);

	void setMaterialUniform(std::string uniformName, Material* material);
	void setMaterialUniform(std::string uniformName, Material* material, int pos);
	
	void setTextureUniform(GLint texture_id, const char* name, GLenum texture_target);

	void setFogUniform(std::string uniformName, Fog* fog);

	int getProgram();
	virtual ~ShaderProgram();

private:
	ShaderProgram(const ShaderProgram& shader) {}
	void operator=(const ShaderProgram& shader) {}
	unsigned short _shader_num;
	int programId;
	int shaderIds[4];
	std::map<std::string, int> uniforms;
};

#endif