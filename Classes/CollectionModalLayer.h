#ifndef CollectionModalLayer_h
#define CollectionModalLayer_h

#include "ui/CocosGUI.h"
#include "ModalLayerBase.h"

class CollectionModalLayer : public ModalLayerBase
{
private:
	cocos2d::Size visibleSize;

public:
	CollectionModalLayer();
	virtual ~CollectionModalLayer();

	void HaveIt(std::string filePath, std::string name, std::string sentenceText);

	void DoNotHave(std::string filePath, std::string name);

	CREATE_FUNC(CollectionModalLayer);
private:
	bool init();

	void PushUiButton(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
};

#endif