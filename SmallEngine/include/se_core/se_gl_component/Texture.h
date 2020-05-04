#ifndef __GLTEXTURE_H__
#define __GLTEXTURE_H__
#include <GLAD/glad.h>
#include <string>
#include <se_aux/GLCommon.h>
#include <se_aux/Logger.h>
using namespace std;
class Texture
{
public:
	Texture();
	Texture(string fileName);
	Texture(unsigned width, unsigned height, unsigned internal_format, bool mipmap, int multisample_level = 0);
	Texture(unsigned width, unsigned height, unsigned depth, unsigned internal_format, bool mipmap);
	~Texture();
	unsigned id() const { return id_; }
	unsigned width() const { return width_; }
	unsigned height() const { return height_; }
	unsigned depth() const { return depth_; }
	unsigned textureTarget() const { return textureTarget_; }
	bool mipmap() const { return mipmap_; }
	int multisampleLevel() const { return multisampleLevel_; }
	unsigned internalFormat() const { return internalFormat_; }
	unsigned use() const { return use_; }
	string key() const { return key_; }
	void setKey(string value) { key_ = value; }
	bool flip() { return flip_; }
	void setFlip(bool value) { flip_ = value; }
	void loadData(unsigned w, unsigned h, unsigned char *data, unsigned format = GL_RGBA);
	void bind(unsigned texture_unit);
	void setBorder(const bool has_border);
	void updateMipmap(GLuint texture_unit);
	void reset();
	void cleanup();
	//void saveToImage(string file);
private:
	void create();
private:
	unsigned id_;
	unsigned width_;
	unsigned height_;
	unsigned depth_;
	unsigned internalFormat_;
	unsigned textureTarget_;
	bool mipmap_;
	int multisampleLevel_;
	string key_;
	unsigned use_;
	bool flip_;
};

#endif // __PG_TEXTURE_H__

