#ifndef TitleScene_h
#define TitleScene_h

#include "SceneBase.h"

class TitleScene : public SceneBase
{
public:
	TitleScene();
	virtual ~TitleScene();

	//ƒV[ƒ“‚Ìì¬
	static cocos2d::Scene* SceneCreate();
};

#endif