#ifndef LeverRight_h
#define LeverRight_h

#include "LeverBase.h"

class LeverRight : public LeverBase, public LeverCreator<LeverRight>
{
private:
	cocos2d::Vec2 touchLocation;

	bool isTouchLever;

public:
	LeverRight();
	virtual ~LeverRight();

private:
	virtual void TouchBegan(cocos2d::Touch* touch);
	virtual void TouchMoved(cocos2d::Touch* touch);
	virtual void TouchEnded(cocos2d::Touch* touch);
};

#endif
