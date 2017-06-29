#include "BackButton.h"
#include "UserData.h"

USING_NS_CC;

BackButton::BackButton()
{

}

BackButton::~BackButton()
{

}

bool BackButton::init(std::string imageFileName)
{
	if (ui::Button::init(imageFileName))
	{
		this->setTitleText("もどる");

		this->setTitleColor(Color3B::BLACK);

		this->setTitleFontName(UserData::GetInstance()->DefaultFontName());

		this->setTitleFontSize(15.0f);

		this->setTouchEnabled(true);

		return true;
	}
	else
	{
		return false;
	}
}

BackButton* BackButton::ButtonCreate(std::string imageFileName)
{
	auto ret = new BackButton();
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