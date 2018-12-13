#ifndef __TEXTURE_H__
#define __TEXTURE_H__

class Texture
{
public:
	Texture(unsigned int shaderProgram, const char* textureFileName);
	bool init();
	bool render();
	void cleanup();

private:
	const char* m_textureFileName;
	unsigned int m_shaderProgram;
	unsigned int m_texture;
};
#endif
