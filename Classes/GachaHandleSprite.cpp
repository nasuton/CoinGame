#include "GachaHandleSprite.h"

USING_NS_CC;

GachaHandleSprite::GachaHandleSprite()
{

}

GachaHandleSprite::~GachaHandleSprite()
{

}

bool GachaHandleSprite::init(std::string imageFileName)
{
	if (Sprite::initWithFile(imageFileName))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GachaHandleSprite::SpriteTouch()
{
	//touchされた場合は回す
	RotateBy* rotateAction = RotateBy::create(2.0f, 180.0f);

	Sequence* sequen = Sequence::create(rotateAction, rotateAction, NULL);

	this->runAction(sequen);
}