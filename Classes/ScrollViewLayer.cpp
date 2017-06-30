#include "ScrollViewLayer.h"
#include "JsonHelper.h"
#include "UserData.h"

USING_NS_CC;

ScrollViewLayer::ScrollViewLayer()
	:touchLocation(0.0f, 0.0f)
	,magnificationHeight(0.0f)
	,interval(15.0f)
	,isMove(false)
{
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(ScrollViewLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(ScrollViewLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(ScrollViewLayer::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(ScrollViewLayer::onTouchCancelled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

ScrollViewLayer::~ScrollViewLayer()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
}

bool ScrollViewLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = UserData::GetInstance()->GetResolutionSize();

	return true;
}

float ScrollViewLayer::GetMagnification()
{
	return magnificationHeight;
}

bool ScrollViewLayer::GetMove()
{
	return isMove;
}

void ScrollViewLayer::AddScrollLayer(const std::vector<cocos2d::ui::Button*>& collectionButton)
{
	magnificationHeight = (((collectionButton[0]->getContentSize().height + interval) * (int)collectionButton.size()) + interval) / visibleSize.height;

	float temporary = (visibleSize.height * magnificationHeight) - (collectionButton[0]->getContentSize().height * 0.5f) - interval;

	for (int i = 0; i < collectionButton.size(); i++)
	{
		collectionButton[i]->setPosition(Vec2(visibleSize.width * 0.6f, temporary - ((collectionButton[i]->getContentSize().height + interval) * i)));
		this->addChild(collectionButton[i]);
	}
}

bool ScrollViewLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	if (isMove)
	{
		isMove = false;
	}

	touchLocation = touch->getLocation();

	return true;
}

void ScrollViewLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	Vec2 location = touch->getLocation();

	if (10.0f < location.distance(touchLocation))
	{
		isMove = true;
	}
}

void ScrollViewLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void ScrollViewLayer::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}