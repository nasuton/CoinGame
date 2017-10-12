#include "Title/Scene/TitleScene.h"
#include "Title/Layer/TitleLayer.h"

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

	//シーンにLayer追加する
	scene->addChild(CreateLayer<TitleLayer>());

	return scene;
}