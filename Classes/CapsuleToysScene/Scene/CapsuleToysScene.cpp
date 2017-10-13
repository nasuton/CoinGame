#include "CapsuleToysScene/Scene/CapsuleToysScene.h"
#include "CapsuleToysScene/Layer/CapsuleToysLayer.h"

USING_NS_CC;

CapsuleToysScene::CapsuleToysScene()
{
	this->autorelease();
}

CapsuleToysScene::~CapsuleToysScene()
{

}

Scene* CapsuleToysScene::SceneCreate()
{
	Scene* scene = Scene::create();

	//Layerをシーンの子として追加する
	scene->addChild(CreateLayer<CapsuleToysLayer>());

	return scene;
}