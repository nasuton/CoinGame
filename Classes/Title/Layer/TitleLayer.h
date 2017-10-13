#ifndef TitleLayer_h
#define TitleLayer_h

#include "Other/LayerBase/LayerBase.h"

class TitleLayer : public LayerBase
{
private:
	//タッチイベントを有効にするためのリスナー
	cocos2d::EventListenerTouchOneByOne* touchListener;

public:
	TitleLayer();
	virtual ~TitleLayer();

	CREATE_FUNC(TitleLayer);

private:
	bool init();

	//タッチイベント
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
};

#endif