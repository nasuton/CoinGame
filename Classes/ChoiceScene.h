﻿#ifndef ChoiceScene_h
#define ChoiceScene_h

#include "SceneBase.h"

class ChoiceScene : public SceneBase
{
public:
	ChoiceScene();
	virtual ~ChoiceScene();

	//シーンの作成
	static cocos2d::Scene* SceneCreate();
};

#endif