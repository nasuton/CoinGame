#include "CollectionScene/Layer/ScrollViewLayer.h"
#include "Other/Json/JsonHelper.h"
#include "Other/UserData/UserData.h"

USING_NS_CC;

ScrollViewLayer::ScrollViewLayer()
	:touchLocation(0.0f, 0.0f)
	,magnificationHeight(0.0f)
	,interval(15.0f)
	,isMove(false)
{
	//touchを追加
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(ScrollViewLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(ScrollViewLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(ScrollViewLayer::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(ScrollViewLayer::onTouchCancelled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

ScrollViewLayer::~ScrollViewLayer()
{
	//touchを削除
	Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
}

bool ScrollViewLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//解像度の取得
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
	//どれくらい伸ばすかを計算する
	magnificationHeight = (((collectionButton[0]->getContentSize().height + interval) * 
						  (int)collectionButton.size()) + interval) / visibleSize.height;

	//一番目のpositionY軸を計算で出す
	float temporary = (visibleSize.height * magnificationHeight) - 
					  (collectionButton[0]->getContentSize().height * 0.5f) - interval;

	//それぞれを設置
	for (int i = 0; i < collectionButton.size(); i++)
	{
		collectionButton[i]->setPosition(Vec2(visibleSize.width * 0.6f,
											  temporary - ((collectionButton[i]->getContentSize().height + interval) * i)));
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

	//微量の移動をはじくため
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