#ifndef TitleScene_h
#define TitleScene_h

#include "SceneBase.h"

class TitleScene : public SceneBase
{
public:
	TitleScene();
	virtual ~TitleScene();

	//シーンの作成
	static cocos2d::Scene* SceneCreate();
};

#endif