#include "GameScene/Lever/LeverRight.h"
#include "Other/Audio/ManagingSound.h"

USING_NS_CC;

LeverRight::LeverRight()
	:touchLocation(0.0f, 0.0f)
	,isTouchLever(false)
{
	
}

LeverRight::~LeverRight()
{

}

void LeverRight::TouchBegan(cocos2d::Touch *touch)
{
	touchLocation = touch->getLocation();

	//触ってればtrueにする
	isTouchLever = true;
}

void LeverRight::TouchMoved(cocos2d::Touch *touch)
{
	//動かした分だけレバーを回転させる
	Vec2 location = touch->getLocation();

	if (isTouchLever)
	{
		float distance = touchLocation.getDistance(location);

		if (100.0f <= distance)
		{
			distance = 100.0f;
		}

		this->setRotation(90.0f * (distance / 100.0f));
	}
}

void LeverRight::TouchEnded(cocos2d::Touch *touch)
{
	//動かした分だけコインに力を加える
	Vec2 location = touch->getLocation();

	if (isTouchLever)
	{
		float distance = touchLocation.getDistance(location);

		if (100.0f <= distance)
		{
			distance = 100.0f;
		}

		this->setRotation(0.0f);

		if (getArea().containsPoint(getTarget()->getPosition()))
		{
			getTarget()->getPhysicsBody()->applyImpulse(Vec2(400.0f * (distance / 100.0f) * -1.0f, 0.0f));
		}

		ManagingSound::GetInstance()->PlaySe("sound/SE/lever.m4a", false);

		isTouchLever = false;
	}
}