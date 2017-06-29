#include "CollectionModalLayer.h"
#include "BackButton.h"
#include "UserData.h"

USING_NS_CC;

CollectionModalLayer::CollectionModalLayer()
{

}

CollectionModalLayer::~CollectionModalLayer()
{

}

bool CollectionModalLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = UserData::GetInstance()->GetResolutionSize();

	Sprite* maskSprite = Sprite::create("modal/modalMask.png");
	maskSprite->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
	this->addChild(maskSprite);

	BackButton* backButton = BackButton::ButtonCreate("backButton.png");
	backButton->setScale(1.5f);
	backButton->setPosition(Vec2(visibleSize.width * 0.5f, backButton->getContentSize().height * 0.5f));
	backButton->addTouchEventListener(CC_CALLBACK_2(CollectionModalLayer::PushUiButton, this));
	this->addChild(backButton);

	return true;
}

void CollectionModalLayer::HaveIt(std::string filePath, std::string name, std::string sentenceText)
{
	Sprite* backGround = Sprite::create("modal/collectionModalBack.png");
	backGround->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height - (backGround->getContentSize().height * 0.5f)));
	this->addChild(backGround);

	Sprite* selectedSprite = Sprite::create(filePath);
	selectedSprite->setPosition(Vec2(backGround->getContentSize().width * 0.5f, backGround->getContentSize().height * 0.5f));
	backGround->addChild(selectedSprite);

	Sprite* textBack = Sprite::create("modal/textBack.png");
	textBack->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.3f));
	this->addChild(textBack);

	Label* textName = Label::createWithTTF(UserData::GetInstance()->DefaultTTF(30.0f), name);
	textName->setPosition(Vec2(textBack->getContentSize().width * 0.5f, textBack->getContentSize().height* 0.8f));
	textName->setTextColor(Color4B::BLACK);
	textBack->addChild(textName);

	Label* text = Label::createWithTTF(UserData::GetInstance()->DefaultTTF(32.0f), sentenceText);
	text->setPosition(Vec2(textBack->getContentSize().width * 0.5f, textBack->getContentSize().height * 0.4f));
	text->setTextColor(Color4B::BLACK);
	textBack->addChild(text);
}

void CollectionModalLayer::DoNotHave(std::string filePath, std::string name)
{
	Sprite* backGround = Sprite::create("modal/collectionModalBack.png");
	backGround->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height - (backGround->getContentSize().height * 0.5f)));
	this->addChild(backGround);

	Sprite* selectedSprite = Sprite::create(filePath);
	selectedSprite->setPosition(Vec2(backGround->getContentSize().width * 0.5f, backGround->getContentSize().height * 0.5f));
	backGround->addChild(selectedSprite);

	Sprite* textBack = Sprite::create("modal/textBack.png");
	textBack->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.3f));
	this->addChild(textBack);

	Label* textName = Label::createWithTTF(UserData::GetInstance()->DefaultTTF(30.0f), name);
	textName->setPosition(Vec2(textBack->getContentSize().width * 0.5f, textBack->getContentSize().height* 0.8f));
	textName->setTextColor(Color4B::BLACK);
	textBack->addChild(textName);

	Label* sentence = Label::createWithTTF(UserData::GetInstance()->DefaultTTF(32.0f), "まだ手に入れていません");
	sentence->setPosition(Vec2(textBack->getContentSize().width * 0.5f, textBack->getContentSize().height * 0.4f));
	sentence->setTextColor(Color4B::RED);
	textBack->addChild(sentence);
}

void CollectionModalLayer::PushUiButton(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		this->removeFromParentAndCleanup(true);
	}
}