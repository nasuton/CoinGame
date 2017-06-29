#ifndef TenYenStageLayer_h
#define TenYenStageLayer_h

#include "StageBase.h"
#include "Coin.h"

class TenYenStageLayer : public StageBase
{
private:
	cocos2d::Size visibleSize;

	Coin* tenCoin;

	std::vector<cocos2d::Rect> hole;

	cocos2d::Rect goalHole;

	float falling;

	cocos2d::Vec2 coinExitPos;

	cocos2d::Vec2 giftExitPos;

	std::string giftFileName;

public:
	TenYenStageLayer();
	virtual ~TenYenStageLayer();

	static TenYenStageLayer* Layercreate(int num);

private:
	void StageSetUp(int num);

	void StageUpDate(float delta);

	void CoinInlet();
};

#endif