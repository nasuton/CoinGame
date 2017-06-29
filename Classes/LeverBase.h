#ifndef LeverBase_h
#define LeverBase_h

#include "cocos2d.h"

template <class LeverType>
class LeverCreator
{
public:
	static LeverType* CreateLever(std::string imageFileName, cocos2d::Node* target)
	{
		auto ret = new LeverType();
		if (ret && ret->init(imageFileName))
		{
			ret->autorelease();
			ret->setTarget(target);

			return ret;
		}
		else
		{
			CC_SAFE_DELETE(ret);
			return ret;
		}
	}
};

class LeverBase : public cocos2d::Sprite
{
public:
	CC_SYNTHESIZE(cocos2d::Node*, target, Target);
	CC_SYNTHESIZE(cocos2d::Rect, area, Area);

private:
	cocos2d::EventListenerTouchOneByOne* touchListener;


public:
	LeverBase();
	virtual ~LeverBase();

	bool init(std::string imageFileName);

protected:
	virtual void TouchBegan(cocos2d::Touch* touch) = 0;
	virtual void TouchMoved(cocos2d::Touch* touch) = 0;
	virtual void TouchEnded(cocos2d::Touch* touch) = 0;

private:
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
};

#endif