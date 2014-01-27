#pragma once
#include "includes.h"

class InputManager
{
public:
	~InputManager(void);
	static InputManager* getInstance(void);
	
	bool IsKeyPressed(SDLKey a_key);
	bool IsKeyDown(SDLKey a_key);
	bool IsKeyUp(SDLKey a_key);
	
	void SetKeyPressed(SDLKey a_key);
	void SetKeyUp(SDLKey a_key);

	bool IsMouseButtonPressed(Uint8 a_mouseButton);
	bool IsMouseButtonDown(Uint8 a_mouseButton);
	bool IsMouseButtonUp(Uint8 a_mouseButton);
	
	void SetMouseButtonPressed(Uint8 a_mouseButton);
	void SetMouseButtonUp(Uint8 a_mouseButton);
	
	void SetMousePosition(int x, int y);
	void SetMouseMovement(int x, int y);
	Vector2i GetMousePosition();

	void Update();
private:
	static bool instanceFlag;
	static InputManager *single;
	InputManager(void);
	
	Vector2i m_mousePosition;
	Vector2i m_mouseMovement;
	
	std::map<SDLKey, bool> m_keysDown;
	std::map<SDLKey, bool> m_keysPressed;
	std::map<SDLKey, bool> m_keysUp;
	
	std::map<Uint8, bool> m_mouseButtonDown;
	std::map<Uint8, bool> m_mouseButtonPressed;
	std::map<Uint8, bool> m_mouseButtonUp;
};

#define Input InputManager::getInstance()