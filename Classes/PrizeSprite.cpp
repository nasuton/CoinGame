#include "PrizeSprite.h"

USING_NS_CC;

PrizeSprite::PrizeSprite()
	:timeToRun(3.0f)
{

}

PrizeSprite::~PrizeSprite()
{

}

bool PrizeSprite::init(std::string imageFileName)
{
	if (Sprite::initWithFile(imageFileName))
	{
		//剛体をつける
		PhysicsBody* giftPhysics = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.6f, 0.3f, 6.0f));
		giftPhysics->setMass(1.0f);
		giftPhysics->setMoment(10.0f);
		giftPhysics->setCategoryBitmask(2);
		giftPhysics->setCollisionBitmask(2);
		giftPhysics->setContactTestBitmask(2);
		this->setPhysicsBody(giftPhysics);

		//一定時間後に実行
		scheduleOnce(schedule_selector(PrizeSprite::Disappear), timeToRun);

		return true;
	}
	else
	{
		return false;
	}
}

void PrizeSprite::Disappear(float delta)
{
	//自身を削除
	this->removeFromParentAndCleanup(true);
}