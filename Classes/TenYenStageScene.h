#ifndef TenYenStage_h
#define TenYenStage_h

#include "SceneBase.h"

class TenYenStageScene : public SceneBase
{
public:
	TenYenStageScene();
	virtual ~TenYenStageScene();

	static cocos2d::Scene* SceneCreate(int num);
};

#endif
