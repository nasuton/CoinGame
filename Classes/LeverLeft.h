#ifndef LeverLeft_h
#define LeverLeft_h

#include "LeverBase.h"

class LeverLeft : public LeverBase, public LeverCreator<LeverLeft>
{
private:
	cocos2d::Vec2 touchLocation;

	bool isTouchLever;

public:
	LeverLeft();
	virtual ~LeverLeft();

private:
	virtual void TouchBegan(cocos2d::Touch* touch);
	virtual void TouchMoved(cocos2d::Touch* touch);
	virtual void TouchEnded(cocos2d::Touch* touch);

};
#endif