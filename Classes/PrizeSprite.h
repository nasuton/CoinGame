#ifndef PrizeSprite_h
#define PrizeSprite_h

#include "SpriteCreator.h"

class PrizeSprite :public SpriteCreator<PrizeSprite>
{
public:
	PrizeSprite();
	virtual ~PrizeSprite();

	bool init(std::string imageFileName);

private:
	void Disappear(float delta);

	float timeToRun;
};

#endif