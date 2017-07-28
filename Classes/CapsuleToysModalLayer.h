#ifndef CapsuleToysModalLayer_h
#define CapsuleToysModalLayer_h

#include "ModalLayerBase.h"
#include "ui/CocosGUI.h"

class CapsuleToysModalLayer : public ModalLayerBase
{
public:
	CapsuleToysModalLayer();
	virtual ~CapsuleToysModalLayer();

	//解像度
	cocos2d::Size visibleSize;

	//引けなかった場合
	void CanNotDraw();

	//引いた際の結果
	void DrawingResult(std::string name, std::string imageFileName);

	CREATE_FUNC(CapsuleToysModalLayer);

private:
	bool init();

	//もどるボタンを押した場合
	void PushUiButton(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
};

#endif