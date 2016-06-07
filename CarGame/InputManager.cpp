#include "InputManager.h"


InputManager::InputManager()
	:vertical(0),
	horizontal(0)
{

}


InputManager::~InputManager()
{

}

InputManager* InputManager::m_pInstance = 0;

InputManager* InputManager::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new InputManager();
	}
	return m_pInstance;
}