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
		PhysicsBody* giftPhysics = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.6f, 0.3f, 6.0f));
		giftPhysics->setMass(1.0f);
		giftPhysics->setMoment(10.0f);
		giftPhysics->setCategoryBitmask(2);
		giftPhysics->setCollisionBitmask(2);
		giftPhysics->setContactTestBitmask(2);
		this->setPhysicsBody(giftPhysics);

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
	auto removeSprite = RemoveSelf::create();
	this->runAction(removeSprite);
}