#include "SceneManager.h"
#include "LayerBase.h"
#include "TitleScene.h"
#include "ChoiceScene.h"
#include "TenYenStageScene.h"
#include "CapsuleToysScene.h"
#include "CollectionScene.h"

USING_NS_CC;

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::CreateTitleScene()
{
	Scene* nextScene = SceneCreate<TitleScene>();

	Director::getInstance()->replaceScene(nextScene);
}

void SceneManager::CreateChoiceScene()
{
	Scene* nextScene = TransitionFade::create(2.0f, SceneCreate<ChoiceScene>(), Color3B::WHITE);
	Director::getInstance()->replaceScene(nextScene);
}

void SceneManager::CreateTenYenStageScene(int num)
{
	if (num == 0)
	{
		Scene* nextScene = TransitionTurnOffTiles::create(1.5f, PhysicsSceneCreate<TenYenStageScene>(num));
		Director::getInstance()->replaceScene(nextScene);
	}
	else if (num == 1)
	{
		Scene* nextScene = TransitionFadeTR::create(1.5f, PhysicsSceneCreate<TenYenStageScene>(num));
		Director::getInstance()->replaceScene(nextScene);
	}
	else
	{
		Scene* nextScene = PhysicsSceneCreate<TenYenStageScene>(num);
		Director::getInstance()->replaceScene(nextScene);
	}
}

void SceneManager::CreateCapsuleToyScene()
{
	Scene* nextScene = TransitionMoveInB::create(1.5f, SceneCreate<CapsuleToysScene>());
	Director::getInstance()->replaceScene(nextScene);
}

void SceneManager::CreateCollectionScene()
{
	Scene* nextScene = TransitionPageTurn::create(1.5f, SceneCreate<CollectionScene>(), false);
	Director::getInstance()->replaceScene(nextScene);
}