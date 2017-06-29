#include "LeverRight.h"

USING_NS_CC;

LeverRight::LeverRight()
{
	touchLocation = Vec2(0.0f, 0.0f);
}

LeverRight::~LeverRight()
{

}

void LeverRight::TouchBegan(cocos2d::Touch *touch)
{
	touchLocation = touch->getLocation();

	isTouchLever = true;
}

void LeverRight::TouchMoved(cocos2d::Touch *touch)
{
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

		isTouchLever = false;
	}
}