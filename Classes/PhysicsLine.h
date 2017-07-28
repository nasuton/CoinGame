#ifndef PhysicsLine_h
#define PhysicsLine_h

#include "LayerBase.h"

class PhysicsLine : public LayerBase
{
public:
	CC_SYNTHESIZE(int, categoryMask, CategoryMask);
	CC_SYNTHESIZE(int, collisionMask, CollisionMask);
	CC_SYNTHESIZE(int, contactTestMask, ContactTestMask);

public:
	PhysicsLine();
	virtual ~PhysicsLine();

	//線を引く
	void CreateLine(std::string fileName, 
					float width = 2.0f, 
					const cocos2d::Color4F &colors = cocos2d::Color4F(1.0f, 1.0f, 1.0f, 1.0f));

	//当たり判定用
	void CreatePhysicsChain(std::string fileName,
							const cocos2d::PhysicsMaterial &material = cocos2d::PHYSICSBODY_MATERIAL_DEFAULT,
							bool setMask = false);

	CREATE_FUNC(PhysicsLine);
private:
	bool init();
};

#endif