﻿#include "CapsuleToysModalLayer.h"
#include "BackButton.h"
#include "UserData.h"

USING_NS_CC;

CapsuleToysModalLayer::CapsuleToysModalLayer()
{

}

CapsuleToysModalLayer::~CapsuleToysModalLayer()
{

}

bool CapsuleToysModalLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = UserData::GetInstance()->GetResolutionSize();

	Sprite* maskSprite = Sprite::create("modal/modalMask.png");
	maskSprite->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
	this->addChild(maskSprite);

	return true;
}

void CapsuleToysModalLayer::CanNotDraw()
{
	Sprite* notTextBack = Sprite::create("modal/canNotDraw.png");
	notTextBack->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
	this->addChild(notTextBack);

	Label* notText = Label::createWithTTF(UserData::GetInstance()->DefaultTTF(40.0f), "たりないよ？");
	notText->setPosition(Vec2(notText->getContentSize().width * 0.5f, notText->getContentSize().height * 0.5f));
	notTextBack->addChild(notText);

	BackButton* backButton = BackButton::ButtonCreate("returnButton.png");
	backButton->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.3f));
	backButton->setScale(1.5f);
	backButton->addTouchEventListener(CC_CALLBACK_2(CapsuleToysModalLayer::PushUiButton, this));
	this->addChild(backButton);
}

void CapsuleToysModalLayer::DrawingResult(std::string name, std::string imageFileName)
{
	Sprite* resultBack = Sprite::create("modal/resultBackground.png");
	resultBack->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
	this->addChild(resultBack);

	Sprite* textBack = Sprite::create("modal/characterBackground.png");
	textBack->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.3f));
	this->addChild(textBack);

	Label* resultText = Label::createWithTTF(UserData::GetInstance()->DefaultTTF(26.0f), name + " を\nてに入れた");
	resultText->setPosition(Vec2(textBack->getContentSize().width * 0.5f, textBack->getContentSize().height * 0.5f));
	resultText->setHorizontalAlignment(TextHAlignment::CENTER);
	textBack->addChild(resultText);

	Sprite* resultSprite = Sprite::create(imageFileName);
	resultSprite->setPosition(Vec2(resultBack->getContentSize().width * 0.5f, resultBack->getContentSize().height * 0.5f));
	resultBack->addChild(resultSprite);

	BackButton* backButton = BackButton::ButtonCreate("returnButton.png");
	backButton->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.2f));
	backButton->setScale(1.5f);
	backButton->addTouchEventListener(CC_CALLBACK_2(CapsuleToysModalLayer::PushUiButton, this));
	this->addChild(backButton);
}

void CapsuleToysModalLayer::PushUiButton(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		this->removeFromParentAndCleanup(true);
	}
}