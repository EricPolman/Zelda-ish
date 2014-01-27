#pragma once
#include "includes.h"

struct Rect{int x;int y; int width; int height;};

class AnimatedSprite
{
public:
	AnimatedSprite(void);
	virtual ~AnimatedSprite(void);

	virtual void LoadSpritesheet(std::string a_textureName, int a_framesizeX = 0,
		int a_framesizeY = 0, int a_framesX = 0, int a_framesY = 0);

	virtual void Update(float a_fDeltaTime);
	virtual void Draw(Tmpl8::Surface* a_target, Vector2 a_position);

	bool m_bIsVisible;
	bool m_bIsAnimated;
	bool m_bIsLooping;

	bool m_bNextFrame;
	float m_fAnimationSpeed;
	float m_fAnimationTimer;
	
	Vector2i m_frames;
	Vector2i m_frameSize;
	
	Vector2i m_currentFrame;
	std::string m_sCurrentAnimation;

	struct AnimationData {Vector2i begin; Vector2i end;};
	std::map<std::string, AnimationData> m_animations;

	void AddAnimation(std::string name, Vector2i beginFrame, Vector2i endFrame);
	void PlayAnimation(std::string name, bool loop = false);
	
	inline int GetWidth(){return m_frameSize.x;}
	inline int GetHeight(){return m_frameSize.y;}
	
	Rect m_textureRect;
private:
	Tmpl8::Surface* m_pTexture;
	void Animate();
	inline void SetFrame(Vector2i frame);
};

