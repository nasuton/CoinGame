#ifndef UserData_h
#define UserData_h

#include "cocos2d.h"

class UserData
{
private:
	cocos2d::Size resolutionSize;

	std::string dataPath;

	static UserData* instance;

public:
	~UserData();

	static UserData* GetInstance();

	static void DeleteInstance();

	void CreatePlist();

	void SetResolutionSize(cocos2d::Size resolution);

	cocos2d::Size GetResolutionSize();

	void SaveNum(int num);

	int LoadNum();

	void SaveResult(std::string premiumName, std::string res);

	cocos2d::ValueMap GetResult();

	std::string DefaultFontName();

	cocos2d::TTFConfig DefaultTTF(float fontSize);

private:
	UserData();
};

#endif