#ifndef ChoiceLayer_h
#define ChoiceLayer_h

#include "Other/LayerBase/LayerBase.h"
#include "ChoiceScene/Layer/SliderLayer.h"
#include "Other/Json/JsonHelper.h"

using keeporder = std::vector<std::pair<std::string, std::string>>;

class ChoiceLayer : public LayerBase
{
private:
	//選択するシーン
	enum selectScene
	{
		stage1 = 0,
		stage2,
		gacha,
		collection,
	};

	//解像度
	cocos2d::Size visibleSize;

	//スライダーレイヤー
	SliderLayer* slider;

public:
	ChoiceLayer();
	virtual ~ChoiceLayer();

	CREATE_FUNC(ChoiceLayer);

private:
	bool init();

	//もどるボタン作成
	void DecisionButtonInit(const rapidjson::Value& decision);

	//選ばれたシーン
	void SelectScene(int number);
};
#endif