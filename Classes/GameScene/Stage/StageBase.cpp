#include "GameScene/Stage/StageBase.h"

USING_NS_CC;

StageBase::StageBase()
{

}

StageBase::~StageBase()
{

}

bool StageBase::init(int num)
{
	if (!Layer::init())
	{
		return false;
	}

	StageSetUp(num);

	this->scheduleUpdate();

	return true;
}

void StageBase::update(float delta)
{
	StageUpDate(delta);
}

void StageBase::StageSetUp(int num)
{

}

void StageBase::StageUpDate(float delta)
{

}