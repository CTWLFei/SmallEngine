#include <se_core/se_gl_component/ShaderProgram.h>
#include <se_aux/GLCommon.h>
#include <se_aux/Logger.h>

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string loadShader(const std::string& fileName);
static int createShader(const std::string& text, GLenum shaderType);

ShaderProgram::ShaderProgram(const std::string& vs, const std::string& fs)
{
	programId = glCreateProgram();
	shaderIds[0] = createShader(loadShader(vs), GL_VERTEX_SHADER);
	shaderIds[1] = createShader(loadShader(fs), GL_FRAGMENT_SHADER);
	_shader_num = 2;
	for (unsigned int i = 0; i < _shader_num; ++i)
	{
		glAttachShader(programId, shaderIds[i]);
	}

	glLinkProgram(programId);
	checkShaderError(programId, GL_LINK_STATUS, true, "Error: Program linking failed!");

	glValidateProgram(programId);
	checkShaderError(programId, GL_VALIDATE_STATUS, true, "Error: Program linking failed!");
}

ShaderProgram::ShaderProgram(const std::string& vs, const std::string& fs, const std::string& gs)
{
	programId = glCreateProgram();
	shaderIds[0] = createShader(loadShader(vs), GL_VERTEX_SHADER);
	shaderIds[1] = createShader(loadShader(fs), GL_FRAGMENT_SHADER);
	shaderIds[2] = createShader(loadShader(gs), GL_GEOMETRY_SHADER);
	_shader_num = 3;
	for (unsigned int i = 0; i < _shader_num; ++i)
	{
		glAttachShader(programId, shaderIds[i]);
	}

	glLinkProgram(programId);
	checkShaderError(programId, GL_LINK_STATUS, true, "Error: Program linking failed!");

	glValidateProgram(programId);
	checkShaderError(programId, GL_VALIDATE_STATUS, true, "Error: Program linking failed!");
}

ShaderProgram::~ShaderProgram()
{
	for (unsigned int i = 0; i < _shader_num; i++)
	{
		glDetachShader(programId, shaderIds[i]);
		glDeleteShader(shaderIds[i]);
	}

	glDeleteProgram(programId);
}

void ShaderProgram::bind()
{
	glUseProgram(programId);
}

void ShaderProgram::unbind()
{
	glUseProgram(0);
}

void ShaderProgram::cleanup()
{
	unbind();
	if (programId != 0) {
		glDeleteProgram(programId);
	}
}

void ShaderProgram::createUniform(std::string uniformName)
{
	int location = glGetUniformLocation(programId, uniformName.c_str());
	if (location < 0)
	{
		std::string info = "There is no uniform name " + uniformName;
		LOGGER_ERROR(info);
		return;
	}
	uniforms[uniformName] = location;
}

void ShaderProgram::createPointLightUniform(std::string uniformName)
{
	createUniform(uniformName + ".colour");
	createUniform(uniformName + ".position");
	createUniform(uniformName + ".intensity");
	createUniform(uniformName + ".att.constant");
	createUniform(uniformName + ".att.linear");
	createUniform(uniformName + ".att.exponent");
}
void ShaderProgram::createMaterialUniform(std::string uniformName)
{
	createUniform(uniformName + ".ambient");
	createUniform(uniformName + ".diffuse");
	createUniform(uniformName + ".specular");
	createUniform(uniformName + ".hasTexture");
	createUniform(uniformName + ".reflectance");
}

void ShaderProgram::setFloatUniform(const char* name, float* values, int vec_size, int vec_num)
{
	int location = uniforms[name];
	
	switch (vec_size)
	{
	case 1:
		glUniform1fv(location, vec_num, values);
		break;
	case 2:
		glUniform2fv(location, vec_num, values);
		break;
	case 3:
		glUniform3fv(location, vec_num, values);
		break;
	case 4:
		glUniform4fv(location, vec_num, values);
		break;
	default:
		break;
	}
}
void ShaderProgram::setMat4Uniform(const char* name, float* values, int size)
{
	int location = uniforms[name];
	glUniformMatrix4fv(location, size, GL_FALSE, values);
}
void ShaderProgram::setIntUniform(const char* name, int* values, int vec_size, int vec_num)
{
	int location = uniforms[name];
	switch (vec_size)
	{
	case 1:
		glUniform1iv(location, vec_num, values);
		break;
	case 2:
		glUniform2iv(location, vec_num, values);
		break;
	case 3:
		glUniform3iv(location, vec_num, values);
		break;
	case 4:
		glUniform4iv(location, vec_num, values);
		break;
	default:
		break;
	}
}

void ShaderProgram::setTextureUniform(GLint texture_id, const char* name, GLenum texture_target)
{
	glActiveTexture(GL_TEXTURE0 + texture_id);
	glBindTexture(texture_target, texture_id);
	setIntUniform(name, &texture_id, 1, 1);
	glActiveTexture(GL_TEXTURE0);
}

void ShaderProgram::setPointLightUniform(std::string uniformName, PointLight* pointLight)
{
	float lightIntensity = pointLight->getIntensity();
	float attConstant = pointLight->getAttenuation()->getConstant();
	float attLinear = pointLight->getAttenuation()->getLinear();
	float attExponent = pointLight->getAttenuation()->getExponent();
	setFloatUniform((uniformName + ".colour").c_str(), &(pointLight->getColor()[0]), 3, 1);
	setFloatUniform((uniformName + ".position").c_str(), &(pointLight->getPosition()[0]), 3, 1);
	setFloatUniform((uniformName + ".intensity").c_str(), &lightIntensity, 1, 1);
	setFloatUniform((uniformName + ".att.constant").c_str(), &attConstant, 1, 1);
	setFloatUniform((uniformName + ".att.linear").c_str(), &attLinear, 1, 1);
	setFloatUniform((uniformName + ".att.exponent").c_str(), &attExponent, 1, 1);
}
void ShaderProgram::setMaterialUniform(std::string uniformName, Material* material)
{
	float reflectance = material->getReflectance();
	int hasTexture = material->getTexture() ? 1 : 0;
	setFloatUniform((uniformName + ".ambient").c_str(), &(material->getAmbientColour()[0]), 4, 1);
	setFloatUniform((uniformName + ".diffuse").c_str(), &(material->getDiffuseColour()[0]), 4, 1);
	setFloatUniform((uniformName + ".specular").c_str(), &(material->getSpecularColour()[0]), 4, 1);
	setIntUniform((uniformName + ".hasTexture").c_str(), &hasTexture, 1, 1);
	setFloatUniform((uniformName + ".reflectance").c_str(), &reflectance, 1, 1);
}

int ShaderProgram::getProgram()
{
	return programId;
}

static int createShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{
		std::cerr << "Error: Failed Creating Shader!" << std::endl;
	}

	const GLchar* shaderSourceString[1];
	GLint shaderSourceStringLength[1];

	shaderSourceString[0] = text.c_str();

	glShaderSource(shader, 1, shaderSourceString, shaderSourceStringLength);
	glCompileShader(shader);

	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Failed Compiling Shader!");

	return shader;
}

static std::string loadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName);

	std::string output;
	char* line = (char*)malloc(255);
	
	if (file.is_open())
	{
		while (file.good())
		{
			file.getline(line, 250);
			std::string media = line;
			output.append(media + "\n");
		}
		return output;
	}
	return "";
}

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}