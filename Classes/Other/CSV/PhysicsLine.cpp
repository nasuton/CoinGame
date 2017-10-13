#include "Other/CSV/PhysicsLine.h"

#include <vector>
#include <fstream>

USING_NS_CC;

PhysicsLine::PhysicsLine()
	:categoryMask(0)
	,collisionMask(0)
	,contactTestMask(0)
{

}

PhysicsLine::~PhysicsLine()
{

}

bool PhysicsLine::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}

void PhysicsLine::CreateLine(std::string fileName, float width, const Color4F& colors)
{
	std::vector<Vec2> drawData;

	//読みこめるようにする
	std::string filePath = FileUtils::getInstance()->getStringFromFile(fileName);
	std::istringstream stream(filePath);
	std::string sheetLine;

	while (std::getline(stream, sheetLine))
	{
		std::istringstream sheetStream(sheetLine);
		std::string temp;

		std::vector<std::string> cellData;

		while (getline(sheetStream, temp, ','))
		{
			cellData.push_back(temp);
		}

		Vec2 linepos = Vec2(std::atoi(cellData[0].c_str()), std::atoi(cellData[1].c_str()));
		if (0 == std::atoi(cellData[2].c_str()))
		{
			drawData.push_back(linepos);
		}
		else
		{
			drawData.push_back(linepos);
			DrawNode* rail = DrawNode::create();
			rail->drawSegment(drawData[0], drawData[1], width, colors);
			this->addChild(rail);

			drawData.clear();
			drawData.shrink_to_fit();
		}
	}
}

void PhysicsLine::CreatePhysicsChain(std::string fileName, const cocos2d::PhysicsMaterial& material, bool setMask)
{
	std::vector<Vec2> railData;
	std::string	filePath = FileUtils::getInstance()->getStringFromFile(fileName);
	std::istringstream stream(filePath);
	std::string sheetLine;

	while (std::getline(stream, sheetLine))
	{
		std::istringstream sheetStream(sheetLine);
		std::string temp;

		std::vector<std::string> cellData;
		while (std::getline(sheetStream, temp, ','))
		{
			cellData.push_back(temp);
		}

		Vec2 pos = Vec2(std::atoi(cellData[0].c_str()), std::atoi(cellData[1].c_str()));
		if (0 == std::atoi(cellData[2].c_str()))
		{
			railData.push_back(pos);
		}
		else
		{
			railData.push_back(pos);

			Node* rail = Node::create();
			rail->setPhysicsBody(PhysicsBody::createEdgeChain(railData.data(), (int)railData.size(), material));

			if (setMask)
			{
				rail->getPhysicsBody()->setCategoryBitmask(getCategoryMask());
				rail->getPhysicsBody()->setCollisionBitmask(getCollisionMask());
				rail->getPhysicsBody()->setContactTestBitmask(getContactTestMask());
			}

			rail->getPhysicsBody()->setDynamic(false);
			this->addChild(rail);

			railData.clear();
			railData.shrink_to_fit();
		}
	}
}