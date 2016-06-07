#include "SceneManager.h"


SceneManager::SceneManager()
{

}


SceneManager::~SceneManager()
{

}

SceneManager* SceneManager::m_pInstance = NULL;

SceneManager* SceneManager::GetInstance()
{
	if (!m_pInstance)
		m_pInstance = new SceneManager();

	return m_pInstance;
}


void SceneManager::SetCurrentScene(Scene* scene)
{
	m_oCurrentScene = scene;
}

void SceneManager::Update(GLfloat deltaTime)
{
	if (m_oCurrentScene)
	{
		m_oCurrentScene->Update(deltaTime);
	}
}