#ifndef TitleScene_h
#define TitleScene_h

#include "SceneBase.h"

class TitleScene : public SceneBase
{
public:
	TitleScene();
	virtual ~TitleScene();

	//�V�[���̍쐬
	static cocos2d::Scene* SceneCreate();
};

#endif