#ifndef __TextureManager__
#define __TextureManager__


class TextureManager
{
public:
	bool load(std::string,std::string, SDL_Renderer*);
	void draw(std::string, int, int, int, int, SDL_Renderer*, SDL_RendererFlip);
	void drawFrame(std::string, int, int, int, int, int, int, SDL_Renderer*, SDL_RendererFlip);

	std::map<std::string, SDL_Texture*> m_textureMap;

private:
	TextureManager(){}
	TextureManager * s_pInstance;

};


#endif
