#include "Other/System/EnvironmentDefaultData.h"

USING_NS_CC;

EnvironmentDefaultData* EnvironmentDefaultData::envInstance = nullptr;

EnvironmentDefaultData::EnvironmentDefaultData()
{
	//解像度の設定とゲームのタイトル
	designResolutionSize = Size(360.0f, 640.0f);
	smallResolutionSize = Size(360.0f, 640.0f);
	mediumResolutionSize = Size(640.0f, 1136.0f);
	largeResolutionSize = Size(1080.0f, 1920.0f);
	gameName = std::string("CoinGame");
}

EnvironmentDefaultData::~EnvironmentDefaultData()
{
	CC_SAFE_DELETE(envInstance);
}

EnvironmentDefaultData* EnvironmentDefaultData::GetInstance()
{
	if (!envInstance)
	{
		envInstance = new EnvironmentDefaultData;
	}

	return envInstance;
}