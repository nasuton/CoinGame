#ifndef EnvironmentDefaultData_h
#define EnvironmentDefaultData_h

#include "cocos2d.h"

class EnvironmentDefaultData
{
public:
	~EnvironmentDefaultData();

	static EnvironmentDefaultData* GetInstance();
	
	//ƒQ[ƒ€“à‚Ì‰ğ‘œ“x
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