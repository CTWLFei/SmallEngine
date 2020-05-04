#ifndef __GLCOMMON_H__
#define __GLCOMMON_H__
#include <iostream>
#include <GLAD/glad.h>
#include <string>

static std::string GLErrorToString(int gle)
{
	if (gle == GL_NO_ERROR)
		return "No error!";

	switch (gle)
	{
	case GL_INVALID_ENUM:
		return "Invalid enum";
	case GL_INVALID_VALUE:
		return "Invalid value";
	case GL_INVALID_OPERATION:
		return "Invalid Operation";
	case GL_STACK_OVERFLOW:
		return "Stack overflow";
	case GL_STACK_UNDERFLOW:
		return "Stack underflow";
	case GL_OUT_OF_MEMORY:
		return  "Out of memory";
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		return "Framebuffer object is not complete";
	}
	return "Undecoded gl error";
}

#define LogCheckGlErrors() do{     \
  int ret_gl = glGetError();     \
  if (ret_gl != GL_NO_ERROR)     \
  {                              \
    std::cout << __FUNCTION__ <<"=============ret_gl=" << GLErrorToString(ret_gl) << std::endl; \
    exit(-1);                    \
  }                              \
  } \
  while(0) \

#endif