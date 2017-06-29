#include "TitleLayer.h"
#include "ManagingSound.h"
#include "UserData.h"
#include "SceneManager.h"

USING_NS_CC;

TitleLayer::TitleLayer()
{
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(TitleLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(TitleLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(TitleLayer::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(TitleLayer::onTouchCancelled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

TitleLayer::~TitleLayer()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
}

bool TitleLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();
	log(u8"winSizeは%f, %f", winSize.width, winSize.height);

	Size visibleSize = UserData::GetInstance()->GetResolutionSize();

	Sprite* titleSprite = Sprite::create("title/titlebackground.png");
	titleSprite->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
	this->addChild(titleSprite);

	ManagingSound::GetInstance()->PlayBgm("sound/BGM/titleSceneBGM", 0.3f, true, 0.5f);

	return true;
}

bool TitleLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	return true;
}

void TitleLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void TitleLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	ManagingSound::GetInstance()->StopBgm(2.0f, true);
	SceneManager::CreateChoiceScene();
}

void TitleLayer::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}