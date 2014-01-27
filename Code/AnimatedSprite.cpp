#include "AnimatedSprite.h"
#include "TextureManager.h"

AnimatedSprite::AnimatedSprite(void)
{
	m_bIsVisible = true;
	m_bIsAnimated = false;
	m_bNextFrame = false;
	m_bIsLooping = false;
	m_fAnimationSpeed = 8;
	m_fAnimationTimer = 0;
	m_textureRect.x = 0;
	m_textureRect.y = 0;
	m_textureRect.width = 0;
	m_textureRect.height = 0;
}

AnimatedSprite::~AnimatedSprite(void)
{
}

void AnimatedSprite::LoadSpritesheet(std::string textureName, 
	int framesizeX, int framesizeY, int framesX, int framesY)
{
	m_pTexture = Textures->m_Textures[textureName];

	m_frames.x = framesX;
	m_frames.y = framesY;
	m_frameSize.x = framesizeX;
	m_frameSize.y = framesizeY;

	AddAnimation("idle", Vector2i(), Vector2i());

	PlayAnimation("idle", true);
	m_bIsAnimated = true;
}

void AnimatedSprite::Update(float a_fDeltaTime){
	if(m_bIsVisible){
		if(m_bIsAnimated){
			m_fAnimationTimer += a_fDeltaTime;

			if(m_fAnimationTimer > 1 / m_fAnimationSpeed / 4){
				m_fAnimationTimer = 0;
				Animate();
			}
		}
	}
}

void AnimatedSprite::Draw(Tmpl8::Surface* a_target, Vector2 a_position){
	if(m_bIsVisible){
		m_pTexture->CopyPartTo(
			a_target, a_position.x, a_position.y, 
			m_textureRect.x, m_textureRect.y, 
			m_textureRect.width, m_textureRect.height,
			true);
	}
}

void AnimatedSprite::PlayAnimation(std::string name, bool loop){
	m_sCurrentAnimation = name;
	m_bIsLooping = loop;
	m_currentFrame = m_animations[m_sCurrentAnimation].begin;
	SetFrame(m_animations[m_sCurrentAnimation].begin);
}

void AnimatedSprite::AddAnimation(std::string name, Vector2i beginFrame, Vector2i endFrame){
	AnimationData data;
	data.begin = beginFrame;
	data.end = endFrame;
	m_animations[name] = data;
}

void AnimatedSprite::SetFrame(Vector2i frame){
	m_textureRect.x = frame.x * m_frameSize.x;
	m_textureRect.y = frame.y * m_frameSize.y;
	m_textureRect.width = m_frameSize.x;
	m_textureRect.height = m_frameSize.y;
}

void AnimatedSprite::Animate(){
	AnimationData data = m_animations[m_sCurrentAnimation];
	if(m_currentFrame.y == data.end.y && m_currentFrame.x == data.end.x){	
		if(m_bIsLooping){
			m_currentFrame = data.begin;
		}
		else{			
			PlayAnimation("idle", false);
		}
	}
	else{
		m_currentFrame.x++;
		if(m_currentFrame.x >= m_frames.x){
			m_currentFrame.x = 0;
			m_currentFrame.y++;
		}
	}
	SetFrame(m_currentFrame);
}