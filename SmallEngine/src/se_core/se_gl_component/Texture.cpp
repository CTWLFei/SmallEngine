#include <se_core/se_gl_component/Texture.h>
#include <freeImage/FreeImage.h>

float max(float v1, float v2) {
	return v1 > v2 ? v1 : v2;
}

Texture::Texture() :
	id_(0), width_(0), height_(0), internalFormat_(0), key_(""), use_(0), flip_(false)
{

}

Texture::Texture(string fileName)
{
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(fileName.c_str());
	FIBITMAP* dib = FreeImage_Load(fif, fileName.c_str(), 0);
	FreeImage_FlipVertical(dib);
	if (dib == NULL)
		LOGGER_ERROR("load picture failed!");
	dib = FreeImage_ConvertTo32Bits(dib);

	BYTE* pixel;
	width_ = FreeImage_GetWidth(dib);
	height_ = FreeImage_GetHeight(dib);
	pixel = FreeImage_GetBits(dib);

	glGenTextures(1, &id_);
	glBindTexture(GL_TEXTURE_2D, id_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixel);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	FreeImage_Unload(dib);
}

Texture::Texture(unsigned width, unsigned height, unsigned internal_format, bool mipmap = false, int multisample_level) :
	id_(0), width_(width), height_(height),
	internalFormat_(internal_format), key_(""), use_(0), flip_(false), mipmap_(mipmap),
	multisampleLevel_(multisample_level), textureTarget_(GL_TEXTURE_2D)
{
	create();
}

Texture::Texture(unsigned width, unsigned height, unsigned depth, unsigned internal_format, bool mipmap = false) :
	id_(0), width_(width), height_(height), depth_(depth),
	internalFormat_(internal_format), key_(""), use_(0), flip_(false), mipmap_(mipmap), multisampleLevel_(0),
	textureTarget_(GL_TEXTURE_3D)
{
	glEnable(GL_TEXTURE_3D);

	glGenTextures(1, &id_);
	glBindTexture(GL_TEXTURE_3D, id_);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

	glTexStorage3D(GL_TEXTURE_3D, 1, GL_RGB8, width, height, depth);
	glBindTexture(GL_TEXTURE_3D, 0);
	glDisable(GL_TEXTURE_3D);
}

Texture::~Texture()
{
	//dtor
	GLuint tex_id = (GLuint)id_;
	if (glIsTexture(tex_id))
	{
		glDeleteTextures(1, &tex_id);
	}
	LogCheckGlErrors();
}

void Texture::updateMipmap(GLuint texture_unit)
{
	glActiveTexture(GL_TEXTURE0 + texture_unit);
	glBindTexture(GL_TEXTURE_2D, id_);
	glGenerateMipmap(GL_TEXTURE_2D);
	LogCheckGlErrors();
}

void Texture::create()
{
	if (internalFormat_ == GL_DEPTH_COMPONENT)
	{
		glGenTextures(1, &id_);
		glBindTexture(GL_TEXTURE_2D, id_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width_, height_, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else {
		glGenTextures(1, &id_);
		if (multisampleLevel_ == 0) {
			glEnable(GL_TEXTURE_2D);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glBindTexture(GL_TEXTURE_2D, id_);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			if (mipmap_) {
				glTexStorage2D(GL_TEXTURE_2D, floor(log2(max(width_, height_))) + 1, GL_RGBA8, width_, height_);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else {
				glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width_, height_);
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else {
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, id_);
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, multisampleLevel_, GL_RGBA, width_, height_, GL_TRUE);
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
		}
	}
	LogCheckGlErrors();
}

void Texture::loadData(unsigned w, unsigned h, unsigned char *data, unsigned format)
{
	if (data == NULL)
	{
		LOGGER_WARN("data === NULL");
		return;
	}

	glBindTexture(GL_TEXTURE_2D, id_);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, format, GL_UNSIGNED_BYTE, data);
	if (mipmap_)
	{
		glEnable(GL_TEXTURE_2D);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	LogCheckGlErrors();
}

void Texture::bind(unsigned texture_unit = 0)
{
	if (id_ <= 0)
	{
		LOGGER_ERROR("texture is null");
		exit(-1);
	}
	glActiveTexture(GL_TEXTURE0 + texture_unit);
	glBindTexture(GL_TEXTURE_2D, id_);
	LogCheckGlErrors();
}

void Texture::setBorder(const bool has_border)
{
	glBindTexture(GL_TEXTURE_2D, id_);
	if (has_border)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float border_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	LogCheckGlErrors();
}

void Texture::reset()
{
	flip_ = false;
}

void Texture::cleanup()
{
	glDeleteTextures(1, &id_);
}