#pragma once
#include "includes.h"

class TextureManager
{
public:
	~TextureManager(void);
	static TextureManager* getInstance(void);
	void LoadTextures(void);
	std::map<std::string, Tmpl8::Surface*> m_Textures;
	void Add(std::string name, std::string path);

private:
	static bool instanceFlag;
	static TextureManager *single;
	TextureManager(void){}
};

#define Textures TextureManager::getInstance()