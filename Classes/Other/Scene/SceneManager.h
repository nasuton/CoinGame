#ifndef SceneManager_h
#define SceneManager_h

#include "cocos2d.h"

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	//タイトルシーン
	static void CreateTitleScene();

	//選択シーン
	static void CreateChoiceScene();

	//ゲームシーン
	static void CreateTenYenStageScene(int num);

	//ガチャシーン
	static void CreateCapsuleToyScene();

	//コレクションシーン
	static void CreateCollectionScene();

private:
	//シーンの作成
	template<class Scene>
	static cocos2d::Scene* SceneCreate();

	//ゲームシーンの作成
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
