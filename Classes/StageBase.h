#ifndef StageBase_h
#define StageBase_h

#include "LayerBase.h"

class StageBase : public LayerBase
{
public:
	StageBase();
	virtual ~StageBase();

	bool init(int num);

protected:
	virtual void StageUpDate(float delta);

	virtual void StageSetUp(int num);

private:
	void update(float delta);
};

#endif
