#ifndef TenYenStage_h
#define TenYenStage_h

#include "Other/Scene/SceneBase.h"

class TenYenStageScene : public SceneBase
{
public:
	TenYenStageScene();
	virtual ~TenYenStageScene();

	//シーンの作成
	static cocos2d::Scene* SceneCreate(int num);
};

#endif
