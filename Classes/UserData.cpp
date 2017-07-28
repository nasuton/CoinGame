#include "UserData.h"

USING_NS_CC;

UserData* UserData::instance = nullptr;

UserData::UserData()
	:resolutionSize(0.0f, 0.0f)
	,dataPath("")
{

}

UserData::~UserData()
{

}

UserData* UserData::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new UserData();
	}

	return instance;
}

void UserData::DeleteInstance()
{
	if (instance != nullptr)
	{
		delete instance;
	}

	instance = nullptr;
}

void UserData::CreatePlist()
{
	dataPath = FileUtils::getInstance()->getWritablePath() + "userDefault.plist";

	//plistが存在した場合はreturnする
	if (FileUtils::getInstance()->isFileExist(dataPath))
	{
		return;
	}

	//plistの中身を作る
	ValueMap data;
	data["remainingNumber"] = 0;
	ValueMap resultList;
	data["result"] = resultList;
	FileUtils::getInstance()->writeToFile(data, dataPath);
}

void UserData::SetResolutionSize(cocos2d::Size screenSize)
{
	resolutionSize = screenSize;
}

Size UserData::GetResolutionSize()
{
	return resolutionSize;
}

void UserData::SaveNum(int num)
{
	ValueMap originalData = FileUtils::getInstance()->getValueMapFromFile(dataPath);

	originalData["remainingNumber"] = num;

	if (!FileUtils::getInstance()->writeToFile(originalData, dataPath))
	{
		log("not Save");
	}
}

int UserData::LoadNum()
{
	ValueMap originalData = FileUtils::getInstance()->getValueMapFromFile(dataPath);

	int possessionNum = originalData["remainingNumber"].asInt();

	return possessionNum;
}

void UserData::SaveResult(std::string premiumName, std::string res)
{
	ValueMap originalData = FileUtils::getInstance()->getValueMapFromFile(dataPath);

	ValueMap resultMap = originalData["result"].asValueMap();

	if (resultMap.find(premiumName) != resultMap.end())
	{
		return;
	}

	resultMap[premiumName] = res;

	originalData["result"] = resultMap;

	if (!FileUtils::getInstance()->writeToFile(originalData, dataPath))
	{
		log("not Save");
	}
}

ValueMap UserData::GetResult()
{
	ValueMap originalData = FileUtils::getInstance()->getValueMapFromFile(dataPath);

	ValueMap possession = originalData["result"].asValueMap();

	return possession;
}

std::string UserData::DefaultFontName()
{
	return "fonts/misaki_gothic.ttf";
}

TTFConfig UserData::DefaultTTF(float fontSize)
{
	TTFConfig config(this->DefaultFontName(), fontSize);

	return config;
}