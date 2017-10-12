#ifndef LeverLeft_h
#define LeverLeft_h

#include "GameScene/Lever/LeverBase.h"

class LeverLeft : public LeverBase, public LeverCreator<LeverLeft>
{
private:
	//touchし始めた場所を保存
	cocos2d::Vec2 touchLocation;

	//レバー触っているかどうか
	bool isTouchLever;

public:
	LeverLeft();
	virtual ~LeverLeft();

private:
	//touchイベント
	virtual void TouchBegan(cocos2d::Touch* touch);
	virtual void TouchMoved(cocos2d::Touch* touch);
	virtual void TouchEnded(cocos2d::Touch* touch);

};
#endif