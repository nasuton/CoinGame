#include "TitleScene.h"
#include "TitleLayer.h"

USING_NS_CC;

TitleScene::TitleScene()
{
	this->autorelease();
}

TitleScene::~TitleScene()
{

}

Scene* TitleScene::SceneCreate()
{
	Scene* scene = Scene::create();

	scene->addChild(CreateLayer<TitleLayer>());

	return scene;
}