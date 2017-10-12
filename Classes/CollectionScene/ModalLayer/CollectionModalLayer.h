#ifndef CollectionModalLayer_h
#define CollectionModalLayer_h

#include "Other/LayerBase/ModalLayerBase.h"

#include "ui/CocosGUI.h"

class CollectionModalLayer : public ModalLayerBase
{
private:
	//解像度
	cocos2d::Size visibleSize;

public:
	CollectionModalLayer();
	virtual ~CollectionModalLayer();

	//持っていた場合
	void HaveIt(std::string filePath, std::string name, std::string sentenceText);

	//持っていない場合
	void DoNotHave(std::string filePath, std::string name);

	CREATE_FUNC(CollectionModalLayer);
private:
	bool init();

	//もどるボタンを押した際
	void PushUiButton(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
};

#endif