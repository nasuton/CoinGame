#ifndef SceneBase_h
#define SceneBase_h

#include "cocos2d.h"

class SceneBase : public cocos2d::Scene
{
public:
	SceneBase();
	virtual ~SceneBase();

protected:
	template <class LayerClass>
	static cocos2d::Layer* CreateLayer();

	template <class LayerClass>
	static cocos2d::Layer* CreateLayer(int num);
};

template <class LayerClass>
inline cocos2d::Layer* SceneBase::CreateLayer()
{
	auto layer = LayerClass::create();

	return layer;
}

template <class LayerClass>
inline cocos2d::Layer* SceneBase::CreateLayer(int num)
{
	auto layer = LayerClass::Layercreate(num);

	return layer;
}

#endif