#ifndef UserData_h
#define UserData_h

#include "cocos2d.h"

class UserData
{
private:
	//解像度
	cocos2d::Size resolutionSize;

	//plistまでのデータパス
	std::string dataPath;

	static UserData* instance;

public:
	~UserData();

	static UserData* GetInstance();

	static void DeleteInstance();

	//plistを作成
	void CreatePlist();

	//解像度をセットする
	void SetResolutionSize(cocos2d::Size resolution);

	//解像度を取得
	cocos2d::Size GetResolutionSize();

	//ガチャを引くための景品の数をsaveする
	void SaveNum(int num);

	//
	int LoadNum();

	//ガチャで手に入れた景品を保存する
	void SaveResult(std::string premiumName, std::string res);

	//すでに入手しているものを取得
	cocos2d::ValueMap GetResult();

	//使用しているfontの名前
	std::string DefaultFontName();

	//TTFConfigを取得
	cocos2d::TTFConfig DefaultTTF(float fontSize);

private:
	UserData();
};

#endif