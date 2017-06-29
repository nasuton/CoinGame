#include "ChoiceLayer.h"
#include "ChoiceScene.h"

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

	scene->addChild(CreateLayer<ChoiceLayer>());

	return scene;
}