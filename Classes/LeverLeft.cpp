#include "LeverLeft.h"

USING_NS_CC;

LeverLeft::LeverLeft()
{
	touchLocation = Vec2(0.0f, 0.0f);
}

LeverLeft::~LeverLeft()
{

}

void LeverLeft::TouchBegan(cocos2d::Touch *touch)
{
	touchLocation = touch->getLocation();

	isTouchLever = true;
}

void LeverLeft::TouchMoved(cocos2d::Touch *touch)
{
	Vec2 location = touch->getLocation();

	if (isTouchLever)
	{
		float distance = touchLocation.getDistance(location);

		if (100.0f <= distance)
		{
			distance = 100.0f;
		}

		this->setRotation(-90.0f * (distance / 100.0f));

	}
}

void LeverLeft::TouchEnded(cocos2d::Touch *touch)
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
			getTarget()->getPhysicsBody()->applyImpulse(Vec2(400.0f * (distance / 100.0f) * 1.0f, 0.0f));
		}

		isTouchLever = false;
	}
}