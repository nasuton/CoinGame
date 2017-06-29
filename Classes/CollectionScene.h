#ifndef CollectionScene_h
#define CollectionScene_h

#include "SceneBase.h"

class CollectionScene : public SceneBase
{
public:
	CollectionScene();
	virtual ~CollectionScene();

	static cocos2d::Scene* SceneCreate();
};

#endif