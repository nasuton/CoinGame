#ifndef BackButton_h
#define BackButton_h

#include "ui/CocosGUI.h"

class BackButton : public cocos2d::ui::Button
{
public:
	BackButton();
	virtual ~BackButton();

	bool init(std::string imageFileName);

	static BackButton* ButtonCreate(std::string imageFileName);
};

#endif