#include "GameScene/Stage/TenYenStage/Scene/TenYenStageScene.h"
#include "GameScene/Stage/TenYenStage/Layer/TenYenStageLayer.h"

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

	//速度の倍率
	world->setSpeed(3.0f);

	//この次のフレームまでの計算速度(数値が高いほど精度が高くなる)
	world->setSubsteps(5);

	//デバックように剛体を表示する
	//world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//シーンLayerを子として追加する
	scene->addChild(CreateLayer<TenYenStageLayer>(num));

	return scene;
}