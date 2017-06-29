#ifndef CapsuleToysModalLayer_h
#define CapsuleToysModalLayer_h

#include "ModalLayerBase.h"
#include "ui/CocosGUI.h"

class CapsuleToysModalLayer : public ModalLayerBase
{
public:
	CapsuleToysModalLayer();
	virtual ~CapsuleToysModalLayer();

	cocos2d::Size visibleSize;

	void CanNotDraw();

	void DrawingResult(std::string name, std::string imageFileName);

	CREATE_FUNC(CapsuleToysModalLayer);

private:
	bool init();

	void PushUiButton(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
};

#endif