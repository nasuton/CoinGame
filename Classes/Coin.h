#ifndef Coin_h
#define Coin_h

#include "SpriteCreator.h"

class Coin : public SpriteCreator<Coin>
{
private:
	std::map<std::string, float> coinType;

	cocos2d::EventListenerPhysicsContact* contactListener;

public:
	Coin();
	virtual ~Coin();

	bool init(std::string imageFileName);

	void CoinEntry(cocos2d::Vec2 pos);

	void ApplyForceCoin(float vecx, float power);

	void SetCoinEnable(bool enable);

	void SetCoinVisible(bool visible);

	void SetCoinPhysics(cocos2d::PhysicsBody* pysicsBody);

private:
	bool OnContactBegin(cocos2d::PhysicsContact &contact);
};

#endif