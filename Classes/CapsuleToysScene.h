#ifndef CapsuleToysScene_h
#define CapsuleToysScene_h

#include "SceneBase.h"

class CapsuleToysScene : public SceneBase
{
public:
	CapsuleToysScene();
	virtual ~CapsuleToysScene();

	//シーンの作成
	static cocos2d::Scene* SceneCreate();
};

#endif