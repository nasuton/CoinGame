#ifndef ScrollViewLayer_h
#define ScrollViewLayer_h

#include "LayerBase.h"
#include "ui/CocosGUI.h"

class ScrollViewLayer : public LayerBase
{
private:
	cocos2d::Size visibleSize;

	cocos2d::EventListenerTouchOneByOne* touchListener;

	cocos2d::Vec2 touchLocation;

	float magnificationHeight;

	float interval;

	bool isMove;
public:
	ScrollViewLayer();
	virtual ~ScrollViewLayer();

	float GetMagnification();

	bool GetMove();

	void AddScrollLayer(const std::vector<cocos2d::ui::Button*>& collectionButton);

	CREATE_FUNC(ScrollViewLayer);
private:
	bool init();

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
};

#endif