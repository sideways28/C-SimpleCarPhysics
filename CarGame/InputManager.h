#pragma once
class InputManager
{
private:
	InputManager();
	static InputManager* m_pInstance;
public:
	~InputManager();

	static InputManager* GetInstance();

	bool* keyStates = new bool[256];
	bool* specialKeyStates = new bool[256];

	float vertical;
	float horizontal;
};

