#include "CollectionScene.h"
#include "CollectionLayer.h"

USING_NS_CC;

CollectionScene::CollectionScene()
{
	this->autorelease();
}

CollectionScene::~CollectionScene()
{

}

Scene* CollectionScene::SceneCreate()
{
	Scene* scene = Scene::create();

	scene->addChild(CreateLayer<CollectionLayer>());

	return scene;
}