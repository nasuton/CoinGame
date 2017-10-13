#ifndef LeverRight_h
#define LeverRight_h

#include "GameScene/Lever/LeverBase.h"

class LeverRight : public LeverBase, public LeverCreator<LeverRight>
{
private:
	//touchし始めた場所を保存する
	cocos2d::Vec2 touchLocation;

	//レバーを触っているかどうか
	bool isTouchLever;

public:
	LeverRight();
	virtual ~LeverRight();

private:
	//touchイベント
	virtual void TouchBegan(cocos2d::Touch* touch);
	virtual void TouchMoved(cocos2d::Touch* touch);
	virtual void TouchEnded(cocos2d::Touch* touch);
};

#endif
