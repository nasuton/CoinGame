#ifndef SpriteBase_h
#define SpriteBase_h

#include "cocos2d.h"

template <class SpriteType>
class SpriteCreator : public cocos2d::Sprite
{
public:
	static SpriteType* CreateSprite(std::string imageFileName) 
	{
		auto ret = new SpriteType();
		if (ret && ret->init(imageFileName))
		{
			ret->autorelease();

			return ret;
		}
		else
		{
			CC_SAFE_DELETE(ret);

			return ret;
		}
	}
};

#endif