#ifndef ModalLayerBase_h
#define ModalLayerBase_h

#include "cocos2d.h"

class ModalLayerBase : public cocos2d::Layer
{
private:
	//touchを使えるように
	cocos2d::EventListenerTouchOneByOne* touchListener;

public:
	ModalLayerBase();
	~ModalLayerBase();
	
private:
	//これがないとエラーがでる
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
};

#endif
