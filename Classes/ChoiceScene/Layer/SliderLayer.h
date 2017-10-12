#ifndef SliderLayer_h
#define SliderLayer_h

#include "Other/LayerBase/LayerBase.h"

class SliderLayer : public LayerBase
{
public:
	//スライドの間隔
	CC_SYNTHESIZE(int, sliderSpan, SliderSpan);

	//スライドの数
	CC_SYNTHESIZE(int, sliderNum, SliderNum);

	//スライドの位置
	CC_SYNTHESIZE(cocos2d::Vec2, slideViewPositon, SlideViewPosition);

private:
	//タッチを有効にするためのリスナー
	cocos2d::EventListenerTouchOneByOne* touchListener;

	//sliderのx軸のposition
	int sliderPosX;

	//現在のページ数
	int page;

	//タッチした際の最初の位置
	float swipePosX;

	//どれだけ動いたか
	float swipeDifference;

	//動く速度
	float moveToDuration;

	//スライドのY軸の位置
	float positionY;

	//次のスライドに行くまでの時間
	float easeOutTime;

public:
	SliderLayer();
	virtual ~SliderLayer();

	virtual bool init();

	//スライドを追加する
	void AddSlide(std::vector<std::pair<std::string, std::string>> &addSlideView);

	//現在のページを取得
	int GetPage();

	CREATE_FUNC(SliderLayer);

private:
	//タッチイベント
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	//スライドした際のアニメーション
	void SlidePage();
};

#endif
