#include "TenYenStageScene.h"
#include "TenYenStageLayer.h"

USING_NS_CC;

TenYenStageScene::TenYenStageScene()
{
	this->autorelease();
}

TenYenStageScene::~TenYenStageScene()
{

}

Scene* TenYenStageScene::SceneCreate(int num)
{
	Scene* scene = Scene::createWithPhysics();

	PhysicsWorld* world = scene->getPhysicsWorld();

	world->setSpeed(3.0f);

	world->setSubsteps(5);

	scene->addChild(CreateLayer<TenYenStageLayer>(num));

	return scene;
}