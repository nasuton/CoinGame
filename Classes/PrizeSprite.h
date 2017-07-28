#ifndef PrizeSprite_h
#define PrizeSprite_h

#include "SpriteCreator.h"

class PrizeSprite :public SpriteCreator<PrizeSprite>
{
private:
	//実行するまでの時間
	float timeToRun;

public:
	PrizeSprite();
	virtual ~PrizeSprite();

	bool init(std::string imageFileName);

private:
	//指定された時間後に設定
	void Disappear(float delta);
};

#endif