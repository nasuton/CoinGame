#ifndef ChoiceLayer_h
#define ChoiceLayer_h

#include "LayerBase.h"
#include "SliderLayer.h"
#include "JsonHelper.h"

using keeporder = std::vector<std::pair<std::string, std::string>>;

class ChoiceLayer : public LayerBase
{
private:
	enum selectScene
	{
		stage1 = 0,
		stage2,
		gacha,
		collection,
	};

	cocos2d::Size visibleSize;

	SliderLayer* slider;

public:
	ChoiceLayer();
	virtual ~ChoiceLayer();

	CREATE_FUNC(ChoiceLayer);

private:
	bool init();

	void DecisionButtonInit(const rapidjson::Value& decision);

	void SelectScene(int number);
};
#endif