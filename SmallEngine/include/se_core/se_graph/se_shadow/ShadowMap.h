#ifndef __SHADOW_H__
#define __SHADOW_H__

#include <se_core/se_gl_component/Texture.h>

class ShadowMap 
{
public:
	ShadowMap();
	~ShadowMap();

	Texture* getDepthMapTexture() { return m_depthMap; }
	int getDepthMapFBO() { return m_depthMapFBO; }
	void cleanup();

	void init();
	void bind();
	void unbind();
public:
	static int SHADOW_MAP_WIDTH;
	static int SHADOW_MAP_HEIGHT;
protected:
	GLuint m_depthMapFBO;
	Texture* m_depthMap;
};

#endif