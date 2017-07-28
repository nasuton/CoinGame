#ifndef CapsuleToysLayer_h
#define CapsuleToysLayer_h

#include "LayerBase.h"
#include "GachaHandleSprite.h"
#include "GachaButton.h"
#include "BackButton.h"

class CapsuleToysLayer : public LayerBase
{
private:
	//ガチャボタン
	GachaButton* gachaButton;

	//ハンドルのSprite
	GachaHandleSprite* handleSprite;

	//もどるボタン
	BackButton* backButton;

	//解像度
	cocos2d::Size visibleSize;

	//imageFilePathと排出率の構造体
	struct contentsParameter
	{
		std::string res;
		float probability;
	};

	//排出するガチャの内容
	std::map<std::string, contentsParameter> result;

	//排出率のトータル数
	float totalProbability;

public:
	CapsuleToysLayer();
	virtual ~CapsuleToysLayer();

	CREATE_FUNC(CapsuleToysLayer);

private:
	bool init();
	//ガチャボタンを押した後の動作
	void DischargeCapsule(float delta);

	//ガチャの中身をセットする
	bool SetResult(std::string jsonPath);

	//ガチャの中身から一つだけ選択する
	void SelectResult(std::map<std::string, contentsParameter> const& resultReference);
};

#endif