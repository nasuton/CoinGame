#ifndef SceneManager_h
#define SceneManager_h

#include "cocos2d.h"

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	static void CreateTitleScene();

	static void CreateChoiceScene();

	static void CreateTenYenStageScene(int num);

	static void CreateCapsuleToyScene();

	static void CreateCollectionScene();

private:
	template<class Scene>
	static cocos2d::Scene* SceneCreate();

	template<class Scene>
	static cocos2d::Scene* PhysicsSceneCreate(int num);
};

template<class Scene>
inline cocos2d::Scene* SceneManager::SceneCreate()
{
	cocos2d::Scene* scene = Scene::SceneCreate();

	return scene;
}

template<class PhysicsScene>
inline cocos2d::Scene* SceneManager::PhysicsSceneCreate(int num)
{
	cocos2d::Scene* scene = PhysicsScene::SceneCreate(num);

	return scene;
}

#endif
