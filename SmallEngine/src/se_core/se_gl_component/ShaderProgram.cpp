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

void ShaderProgram::setFloatUniform(const char* name, float* values, int vec_size, int vec_num)
{
	int location = glGetUniformLocation(programId, name);
	if (location < 0)
	{
		std::string info = "There is no uniform name " + std::string(name);
		LOGGER_ERROR(info);
		return;
	}
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
	uniforms[name] = location;
}
void ShaderProgram::setMat4Uniform(const char* name, float* values, int size)
{
	int location = glGetUniformLocation(programId, name);
	if (location < 0)
	{
		std::string info = "There is no uniform name " + std::string(name);
		LOGGER_ERROR(info);
		return;
	}
	glUniformMatrix4fv(location, size, GL_FALSE, values);
	uniforms[name] = location;
}
void ShaderProgram::setIntUniform(const char* name, int* values, int vec_size, int vec_num)
{
	int location = glGetUniformLocation(programId, name);
	if (location < 0)
	{
		std::string info = "There is no uniform name " + std::string(name);
		LOGGER_ERROR(info);
		return;
	}
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
	uniforms[name] = location;
}

void ShaderProgram::setTextureUniform(GLint texture_id, const char* name, GLenum texture_target)
{
	glActiveTexture(GL_TEXTURE0 + texture_id);
	glBindTexture(texture_target, texture_id);
	setIntUniform(name, &texture_id, 1, 1);
	glActiveTexture(GL_TEXTURE0);
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