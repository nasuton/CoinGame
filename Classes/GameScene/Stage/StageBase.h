#ifndef StageBase_h
#define StageBase_h

#include "Other/LayerBase/LayerBase.h"

class StageBase : public LayerBase
{
public:
	StageBase();
	virtual ~StageBase();

	bool init(int num);

protected:
	//継承先で呼ばれるUpDate
	virtual void StageUpDate(float delta);

	//継承先で呼ばれるSetUp
	virtual void StageSetUp(int num);

private:
	void update(float delta);
};

#endif
