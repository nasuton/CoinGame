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

	Size visibleSize = UserData::GetInstance()->GetResolutionSize();

	Sprite* titleBackSprite = Sprite::create("title/titlebackground.png");
	titleBackSprite->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
	this->addChild(titleBackSprite);

	Sprite* titleNameSprite = Sprite::create("title/titleName.png");
	titleNameSprite->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.9f));
	this->addChild(titleNameSprite);

	Sprite* titleTouchSprite = Sprite::create("title/touchSprite.png");
	titleTouchSprite->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.1f));
	this->addChild(titleTouchSprite);

	Sequence* flashing = Sequence::create(FadeOut::create(1.0f), FadeIn::create(1.0f), NULL);
	titleTouchSprite->runAction(RepeatForever::create(flashing));

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
	ManagingSound::GetInstance()->PlaySe("sound/SE/titleTap.m4a", false);
	SceneManager::CreateChoiceScene();
}

void TitleLayer::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}