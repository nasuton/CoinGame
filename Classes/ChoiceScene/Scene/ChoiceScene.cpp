#include "ChoiceScene/Layer/ChoiceLayer.h"
#include "ChoiceScene/Scene/ChoiceScene.h"

USING_NS_CC;

ChoiceScene::ChoiceScene()
{
	this->autorelease();
}

ChoiceScene::~ChoiceScene()
{

}

Scene* ChoiceScene::SceneCreate()
{
	Scene* scene = Scene::create();

	//Layerを子として追加
	scene->addChild(CreateLayer<ChoiceLayer>());

	return scene;
}