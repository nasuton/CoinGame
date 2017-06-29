#ifndef SliderLayer_h
#define SliderLayer_h

#include "LayerBase.h"

class SliderLayer : public LayerBase
{
public:
	CC_SYNTHESIZE(int, sliderSpan, SliderSpan);
	CC_SYNTHESIZE(int, sliderNum, SliderNum);
	CC_SYNTHESIZE(cocos2d::Vec2, slideViewPositon, SlideViewPosition);

private:
	cocos2d::EventListenerTouchOneByOne* touchListener;

	int sliderPosX;

	int page;

	float swipePosX;

	float swipeDifference;

	float moveToDuration;

	float positionY;

	float easeOutTime;

public:
	SliderLayer();
	virtual ~SliderLayer();

	virtual bool init();

	void AddSlide(std::vector<std::pair<std::string, std::string>> &addSlideView);

	int GetPage();

	CREATE_FUNC(SliderLayer);

private:
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	void SlidePage();
};

#endif
