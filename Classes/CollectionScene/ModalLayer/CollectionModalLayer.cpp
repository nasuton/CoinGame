#include "CollectionScene/ModalLayer/CollectionModalLayer.h"
#include "Other/BackButton.h"
#include "Other/UserData/UserData.h"

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

	//解像度の取得
	visibleSize = UserData::GetInstance()->GetResolutionSize();

	//背景をくらくするため
	Sprite* maskSprite = Sprite::create("modal/modalMask.png");
	maskSprite->setPosition(Vec2(visibleSize.width * 0.5f,
								 visibleSize.height * 0.5f));
	this->addChild(maskSprite);

	//もどるボタン
	BackButton* backButton = BackButton::ButtonCreate("backButton.png");
	backButton->setScale(1.5f);
	backButton->setPosition(Vec2(visibleSize.width * 0.5f, 
								 backButton->getContentSize().height * 0.5f));
	backButton->addTouchEventListener(CC_CALLBACK_2(CollectionModalLayer::PushUiButton, this));
	this->addChild(backButton);

	return true;
}

void CollectionModalLayer::HaveIt(std::string filePath, std::string name, std::string sentenceText)
{
	//背景
	Sprite* backGround = Sprite::create("modal/collectionModalBack.png");
	backGround->setPosition(Vec2(visibleSize.width * 0.5f,
								 visibleSize.height - (backGround->getContentSize().height * 0.5f)));
	this->addChild(backGround);

	//選んだもの
	Sprite* selectedSprite = Sprite::create(filePath);
	selectedSprite->setPosition(Vec2(backGround->getContentSize().width * 0.5f, 
									 backGround->getContentSize().height * 0.5f));
	backGround->addChild(selectedSprite);

	//テキストの背景
	Sprite* textBack = Sprite::create("modal/textBack.png");
	textBack->setPosition(Vec2(visibleSize.width * 0.5f, 
							   visibleSize.height * 0.3f));
	this->addChild(textBack);

	//選んだもの名前
	Label* textName = Label::createWithTTF(UserData::GetInstance()->DefaultTTF(30.0f), name);
	textName->setPosition(Vec2(textBack->getContentSize().width * 0.5f, 
							   textBack->getContentSize().height* 0.8f));
	textName->setTextColor(Color4B::BLACK);
	textBack->addChild(textName);

	//説明文
	Label* sentence = Label::createWithTTF(UserData::GetInstance()->DefaultTTF(32.0f), sentenceText);
	sentence->setPosition(Vec2(textBack->getContentSize().width * 0.5f,
						   textBack->getContentSize().height * 0.4f));
	sentence->setTextColor(Color4B::BLACK);
	textBack->addChild(sentence);
}

void CollectionModalLayer::DoNotHave(std::string filePath, std::string name)
{
	//背景
	Sprite* backGround = Sprite::create("modal/collectionModalBack.png");
	backGround->setPosition(Vec2(visibleSize.width * 0.5f, 
								 visibleSize.height - (backGround->getContentSize().height * 0.5f)));
	this->addChild(backGround);

	//選んだもの
	Sprite* selectedSprite = Sprite::create(filePath);
	selectedSprite->setPosition(Vec2(backGround->getContentSize().width * 0.5f, 
									 backGround->getContentSize().height * 0.5f));
	backGround->addChild(selectedSprite);

	//テキストの背景
	Sprite* textBack = Sprite::create("modal/textBack.png");
	textBack->setPosition(Vec2(visibleSize.width * 0.5f, 
							   visibleSize.height * 0.3f));
	this->addChild(textBack);

	//選んだものの名前
	Label* textName = Label::createWithTTF(UserData::GetInstance()->DefaultTTF(30.0f), name);
	textName->setPosition(Vec2(textBack->getContentSize().width * 0.5f, 
							   textBack->getContentSize().height* 0.8f));
	textName->setTextColor(Color4B::BLACK);
	textBack->addChild(textName);
	
	//文
	Label* sentence = Label::createWithTTF(UserData::GetInstance()->DefaultTTF(32.0f), u8"まだ手に入れていません");
	sentence->setPosition(Vec2(textBack->getContentSize().width * 0.5f, 
							   textBack->getContentSize().height * 0.4f));
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