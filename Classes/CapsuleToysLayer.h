#ifndef CapsuleToysLayer_h
#define CapsuleToysLayer_h

#include "LayerBase.h"
#include "GachaHandleSprite.h"
#include "GachaButton.h"
#include "BackButton.h"

class CapsuleToysLayer : public LayerBase
{
private:
	GachaButton* gachaButton;

	GachaHandleSprite* handleSprite;

	BackButton* backButton;

	cocos2d::Size visibleSize;

	struct contentsParameter
	{
		std::string res;
		float probability;
	};
	std::map<std::string, contentsParameter> result;

	float totalProbability;

public:
	CapsuleToysLayer();
	virtual ~CapsuleToysLayer();

	CREATE_FUNC(CapsuleToysLayer);

private:
	bool init();

	void DischargeCapsule(float delta);

	bool SetResult(std::string jsonPath);

	void SelectResult(std::map<std::string, contentsParameter> const& resultReference);
};

#endif