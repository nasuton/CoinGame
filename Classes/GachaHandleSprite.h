#ifndef GachaHandleSprite_h
#define GachaHandleSprite_h

#include "SpriteCreator.h"

class GachaHandleSprite : public SpriteCreator<GachaHandleSprite>
{
public:
	GachaHandleSprite();
	virtual ~GachaHandleSprite();

	bool init(std::string imageFileName);

	//Spriteをtouchした場合
	void SpriteTouch();
};

#endif