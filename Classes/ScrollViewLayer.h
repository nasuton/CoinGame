#ifndef ScrollViewLayer_h
#define ScrollViewLayer_h

#include "LayerBase.h"
#include "ui/CocosGUI.h"

class ScrollViewLayer : public LayerBase
{
private:
	//解像度
	cocos2d::Size visibleSize;

	//touchを使えるようにするため
	cocos2d::EventListenerTouchOneByOne* touchListener;

	//タッチした瞬間のposを保存
	cocos2d::Vec2 touchLocation;

	//Layerをどれくらいのばすかの倍率
	float magnificationHeight;

	//間隔
	float interval;

	//動いたか
	bool isMove;
public:
	ScrollViewLayer();
	virtual ~ScrollViewLayer();

	//倍率を取得
	float GetMagnification();

	//動いたかどうか
	bool GetMove();

	//スクロールビューに追加する
	void AddScrollLayer(const std::vector<cocos2d::ui::Button*>& collectionButton);

	CREATE_FUNC(ScrollViewLayer);
private:
	bool init();

	//touchイベント
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
};

#endif