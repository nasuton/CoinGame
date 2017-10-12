#include "GameScene/Coin.h"
#include "Other/System/Probability.h"
#include "Other/Audio/ManagingSound.h"

USING_NS_CC;

Coin::Coin()
{
	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Coin::OnContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

Coin::~Coin()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(contactListener);

	coinType.clear();
}

bool Coin::init(std::string imageFileName)
{
	if (Sprite::initWithFile(imageFileName))
	{
		coinType =
		{
			{ "coinType/coin1.png", 10.0f },
			{ "coinType/coin2.png", 20.0f },
			{ "coinType/coin3.png", 30.0f },
			{ "coinType/coin4.png", 40.0f }
		};

		return true;
	}
	else
	{
		return false;
	}
}

void Coin::CoinEntry(cocos2d::Vec2 pos)
{
	//coinのSpriteを変える
	std::string reSprite = Probability::SelectOne(coinType);

	this->getPhysicsBody()->resetForces();
	this->getPhysicsBody()->setVelocity(Vec2(0.0f, 0.0f));

	this->stopAllActions();
	this->setSpriteFrame(Sprite::create(reSprite)->getSpriteFrame());

	this->setPosition(pos);

	this->getPhysicsBody()->setEnabled(true);
	this->setVisible(true);
}

void Coin::SetCoinEnable(bool enable)
{
	this->getPhysicsBody()->setEnabled(enable);
}

void Coin::SetCoinPhysics(cocos2d::PhysicsBody* pysicsBody)
{
	this->setPhysicsBody(pysicsBody);
}

void Coin::SetCoinVisible(bool visible)
{
	this->setVisible(visible);
}

bool Coin::OnContactBegin(cocos2d::PhysicsContact &contact)
{
	//コインがぶつかったら音を鳴らす
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	if ("coin" == bodyA->getName() || "coin" == bodyB->getName())
	{
		ManagingSound::GetInstance()->PlaySe("SE/coin_contact.m4a", false);
	}

	return true;
}

