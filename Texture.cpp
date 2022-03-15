//#include "Texture.h"
//#include <glad/glad.h>
//
//void Texture::load(const std::string& name)
//{
//	auto i = ResourceManager::get().images.get(name);
//
//	//glGenBuffers(1, &ID);
//	//glActiveTexture(GL_TEXTURE0);
//	//glBindTexture(GL_TEXTURE_2D, ID);
//
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, i.getSize().x, i.getSize().y, 0,
//		GL_RGBA, GL_UNSIGNED_BYTE, i.getPixelsPtr());
//
//	//glGenerateMipmap(GL_TEXTURE_2D);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//	//	GL_NEAREST_MIPMAP_NEAREST);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);
//}
//
//const unsigned int& Texture::getID() const
//{
//	return ID;
//}
