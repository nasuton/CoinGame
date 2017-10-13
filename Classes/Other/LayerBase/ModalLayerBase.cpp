#include "Other/LayerBase/ModalLayerBase.h"

USING_NS_CC;

ModalLayerBase::ModalLayerBase()
{
	//ModalLayerにするための設定
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(ModalLayerBase::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

ModalLayerBase::~ModalLayerBase()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
}

bool ModalLayerBase::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	return true;
}