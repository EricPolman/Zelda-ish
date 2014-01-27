#include "TextureManager.h"

TextureManager::~TextureManager(void)
{
	instanceFlag = false;
	for(std::map<std::string, Tmpl8::Surface*>::iterator i = m_Textures.begin(); i != m_Textures.end(); ++i)
	{
		m_Textures.erase(i);
	}
}

bool TextureManager::instanceFlag = false;
TextureManager* TextureManager::single = NULL;
TextureManager* TextureManager::getInstance()
{
    if(! instanceFlag)
    {
        single = new TextureManager();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}

void TextureManager::Add(std::string name, std::string path)
{
	Tmpl8::Surface* tex = new Tmpl8::Surface(const_cast<char*>(path.c_str()));
	TextureManager::getInstance()->m_Textures[name] = tex;
}