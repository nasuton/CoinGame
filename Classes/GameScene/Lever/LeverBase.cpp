#include "GameScene/Lever/LeverBase.h"

USING_NS_CC;

LeverBase::LeverBase()
{
	//touchイベントの追加
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(LeverBase::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(LeverBase::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(LeverBase::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(LeverBase::onTouchCancelled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

LeverBase::~LeverBase()
{
	//touchを削除
	Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
}

bool LeverBase::init(std::string imageFileName)
{
	if (Sprite::initWithFile(imageFileName))
	{
		this->setAnchorPoint(Vec2(0.5f, 0.28f));
		this->setScale(1.8f);
		return true;
	}
	else
	{
		return false;
	}
}

bool LeverBase::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	//レバーを触っているかどうか判定する
	Vec2 location = touch->getLocation();

	Rect rect = this->getBoundingBox();

	if (rect.containsPoint(location))
	{
		TouchBegan(touch);
	}

	return true;
}

void LeverBase::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	TouchMoved(touch);
}

void LeverBase::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	TouchEnded(touch);
}

void LeverBase::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	TouchEnded(touch);
}