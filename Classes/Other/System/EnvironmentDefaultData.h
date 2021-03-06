#ifndef EnvironmentDefaultData_h
#define EnvironmentDefaultData_h

#include "cocos2d.h"

class EnvironmentDefaultData
{
public:
	~EnvironmentDefaultData();

	static EnvironmentDefaultData* GetInstance();
	
	//ゲーム内の解像度
	cocos2d::Size designResolutionSize;

	cocos2d::Size smallResolutionSize;

	cocos2d::Size mediumResolutionSize;

	cocos2d::Size largeResolutionSize;

	std::string gameName;
private:
	EnvironmentDefaultData();

	static EnvironmentDefaultData* envInstance;
};

#endif