#ifndef Coin_h
#define Coin_h

#include "Other/SpriteBase/SpriteCreator.h"

class Coin : public SpriteCreator<Coin>
{
private:
	//コインの種類
	std::map<std::string, float> coinType;

	//コインが他の剛体にぶつかった際の処理をするため
	cocos2d::EventListenerPhysicsContact* contactListener;

public:
	Coin();
	virtual ~Coin();

	bool init(std::string imageFileName);

	//コインが入った場合
	void CoinEntry(cocos2d::Vec2 pos);

	//剛体を有効にするかどうか
	void SetCoinEnable(bool enable);

	//透明にするかどうか
	void SetCoinVisible(bool visible);
	
	//剛体をつける
	void SetCoinPhysics(cocos2d::PhysicsBody* pysicsBody);

private:
	//他の剛体にぶつかったさいの処理
	bool OnContactBegin(cocos2d::PhysicsContact &contact);
};

#endif