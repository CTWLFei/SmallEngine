#include <se_core/se_graph/se_shadow/ShadowMap.h>

int ShadowMap::SHADOW_MAP_WIDTH = 1024;
int ShadowMap::SHADOW_MAP_HEIGHT = 1024;

ShadowMap::ShadowMap()
{
	glGenFramebuffers(1, &m_depthMapFBO);

	m_depthMap = new Texture(SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT, GL_DEPTH_COMPONENT,false, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMap->id(), 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		LOGGER_ERROR("Could not create FrameBuffer");
	}

	// Unbind
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
ShadowMap::~ShadowMap()
{
	cleanup();
}


void ShadowMap::cleanup(){
	glDeleteFramebuffers(1, &m_depthMapFBO);
	m_depthMap->cleanup();
}

void ShadowMap::init()
{
	glViewport(0, 0, SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void ShadowMap::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
}
void ShadowMap::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}