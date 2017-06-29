﻿#include "GachaButton.h"
#include "UserData.h"

USING_NS_CC;

GachaButton::GachaButton()
{

}

GachaButton::~GachaButton()
{

}

bool GachaButton::init(std::string imageFileName)
{
	if (ui::Button::init(imageFileName))
	{
		this->setTitleText("まわす");

		this->setTitleColor(Color3B::BLACK);

		this->setTitleFontName(UserData::GetInstance()->DefaultFontName());

		this->setTitleFontSize(30);

		return true;
	}
	else
	{
		return false;
	}
}

GachaButton* GachaButton::CreateGacha(std::string imageFileName)
{
	auto ret = new GachaButton();
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