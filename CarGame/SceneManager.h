#pragma once
#include "Scene.h"

class Scene;
class SceneManager
{
private:
	SceneManager();
	static SceneManager* m_pInstance;
	Scene* m_oCurrentScene;
public:
	~SceneManager();

	static SceneManager* GetInstance();

	void SetCurrentScene(Scene* scene);
	void Update(GLfloat deltaTime);
};

