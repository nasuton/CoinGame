#ifndef TenYenStageLayer_h
#define TenYenStageLayer_h

#include "StageBase.h"
#include "Coin.h"

class TenYenStageLayer : public StageBase
{
private:
	//解像度
	cocos2d::Size visibleSize;

	//コイン
	Coin* tenCoin;

	//はずれ穴の配列
	std::vector<cocos2d::Rect> hole;

	//ゴール穴
	cocos2d::Rect goalHole;

	//穴へ落ちる際のコインの速度
	float falling;

	//コインの出現地
	cocos2d::Vec2 coinExitPos;

	//ギフトの出現地
	cocos2d::Vec2 giftExitPos;

	//ギフトの画像ファイルpath
	std::string giftFileName;

public:
	TenYenStageLayer();
	virtual ~TenYenStageLayer();

	static TenYenStageLayer* Layercreate(int num);

private:
	//	セットアップ
	void StageSetUp(int num);

	//アップデート
	void StageUpDate(float delta);

	//コインの出現
	void CoinInlet();
};

#endif