#ifndef GachaButton_h
#define GachaButton_h

#include "ui/CocosGUI.h"

class GachaButton : public cocos2d::ui::Button
{
public:
	GachaButton();
	virtual ~GachaButton();

	bool init(std::string imageFileName);

	//このSpriteを作成させる関数
	static GachaButton* CreateGacha(std::string imageFileName);
};

#endif
