#ifndef _SHADER_H_
#define _SHADER_H_
#include <GLAD/glad.h>
#include <string>
#include <fstream>
#include <map>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& vs, const std::string& fs);
	ShaderProgram(const std::string& vs, const std::string& fs, const std::string& gs);
	void bind();
	void unbind();
	void cleanup();
	void createUniform(std::string uniformName) {}
	void setFloatUniform(const char* name, float* values, int vec_size, int vec_num);
	void setMat4Uniform(const char* name, float* values, int size);
	void setIntUniform(const char* name, int* values, int vec_size, int vec_num);
	void setTextureUniform(GLint texture_id, const char* name, GLenum texture_target);
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