#ifndef CollectionScene_h
#define CollectionScene_h

#include "Other/Scene/SceneBase.h"

class CollectionScene : public SceneBase
{
public:
	CollectionScene();
	virtual ~CollectionScene();

	//シーンを作成
	static cocos2d::Scene* SceneCreate();
};

#endif