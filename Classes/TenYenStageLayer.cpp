#include "TenYenStageLayer.h"
#include "PhysicsLine.h"
#include "PrizeSprite.h"
#include "LeverLeft.h"
#include "LeverRight.h"
#include "BackButton.h"
#include "SceneManager.h"
#include "JsonHelper.h"
#include "ManagingSound.h"
#include "UserData.h"

#include "ui/CocosGUI.h"

USING_NS_CC;

TenYenStageLayer::TenYenStageLayer()
{

}

TenYenStageLayer::~TenYenStageLayer()
{

}

TenYenStageLayer* TenYenStageLayer::Layercreate(int num)
{
	auto ret = new TenYenStageLayer();

	if (ret && ret->init(num))
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return ret;
	}
}

void TenYenStageLayer::StageSetUp(int num)
{
	visibleSize = UserData::GetInstance()->GetResolutionSize();

	rapidjson::Document tenYen = JsonHelper::DocumentParse<rapidjson::kParseDefaultFlags>(StringUtils::format("json/tenYenStage%i.json", num));

	if (tenYen.HasParseError())
	{
		log("json parse error");
	}

	const rapidjson::Value& lostHole = tenYen["lostHole"];
	for (rapidjson::SizeType i = 0; i < lostHole.Size(); i++)
	{
		Rect substitutionLostHole = Rect(lostHole[i]["position"]["x"].GetFloat(), lostHole[i]["position"]["y"].GetFloat(), lostHole[i]["size"]["width"].GetFloat(), lostHole[i]["size"]["height"].GetFloat());
		hole.push_back(substitutionLostHole);
	}

	const rapidjson::Value& goal = tenYen["goalHole"];
	goalHole = Rect(goal["position"]["x"].GetFloat(), goal["position"]["y"].GetFloat(), goal["size"]["width"].GetFloat(), goal["size"]["height"].GetFloat());

	const rapidjson::Value& backSprite = tenYen["backGround"];
	Sprite* backGround = Sprite::create(backSprite["res"].GetString());
	backGround->setPosition(Vec2(visibleSize.width * backSprite["position"]["x"].GetFloat(), visibleSize.height * backSprite["position"]["y"].GetFloat()));
	this->addChild(backGround);

	const rapidjson::Value& stageline = tenYen["physicsLine"];
	PhysicsLine* stageLine = PhysicsLine::create();
	stageLine->CreateLine(stageline["createLine"].GetString());
	stageLine->setCategoryMask(stageline["categoryMask"].GetInt());
	stageLine->setCollisionMask(stageline["collisionMask"].GetInt());
	stageLine->setContactTestMask(stageline["contactTestMask"].GetInt());
	stageLine->CreatePhysicsChain(stageline["createPhysicsChain"].GetString(), PhysicsMaterial(stageline["material"]["density"].GetFloat(), stageline["material"]["restitution"].GetFloat(), stageline["material"]["friction"].GetFloat()), true);
	this->addChild(stageLine);

	const rapidjson::Value& uiButton = tenYen["coinInletItem"];
	ui::Button* coinInletItem = cocos2d::ui::Button::create(uiButton["res"].GetString());
	coinInletItem->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Button::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Button::Widget::TouchEventType::ENDED:
			this->CoinInlet();
			break;

		default:
			break;
		}
	});
	coinExitPos = Vec2(uiButton["position"]["x"].GetFloat(), uiButton["position"]["y"].GetFloat());
	coinInletItem->setPosition(Vec2(visibleSize.width * coinExitPos.x, visibleSize.height * coinExitPos.y));
	this->addChild(coinInletItem);

	const rapidjson::Value& circle = tenYen["circleNode"];
	for (int i = 0; i < hole.size(); i++)
	{
		Vec2 circlePos = Vec2(hole[i].origin.x + (hole[i].size.width * circle["position"]["x"].GetFloat()), hole[i].origin.y + (hole[i].size.height * circle["position"]["y"].GetFloat()));
		DrawNode* circleNode = DrawNode::create();
		circleNode->drawDot(circlePos, circle["size"].GetFloat(), Color4F(circle["color"]["red"].GetFloat(), circle["color"]["green"].GetFloat(), circle["color"]["blue"].GetFloat(), circle["color"]["alpha"].GetFloat()));
		this->addChild(circleNode);
	}

	const rapidjson::Value& coin = tenYen["tenCoin"];
	PhysicsMaterial coinMaterial;
	coinMaterial.density = coin["coinMaterial"]["density"].GetFloat();
	coinMaterial.restitution = coin["coinMaterial"]["restitution"].GetFloat();
	coinMaterial.friction = coin["coinMaterial"]["friction"].GetFloat();

	PhysicsBody* coinPhysics = PhysicsBody::createCircle(coin["coinPhysics"]["radius"].GetFloat(), coinMaterial);
	coinPhysics->setMass(coin["coinPhysics"]["mass"].GetFloat());
	coinPhysics->setMoment(coin["coinPhysics"]["moment"].GetFloat());
	coinPhysics->setCategoryBitmask(coin["coinPhysics"]["categoryBitmask"].GetInt());
	coinPhysics->setCollisionBitmask(coin["coinPhysics"]["collisionBitmask"].GetInt());
	coinPhysics->setContactTestBitmask(coin["coinPhysics"]["contactTestBitmask"].GetInt());
	coinPhysics->setName(coin["coinPhysics"]["name"].GetString());

	tenCoin = Coin::CreateSprite(coin["res"].GetString());
	tenCoin->SetCoinPhysics(coinPhysics);
	tenCoin->SetCoinEnable(false);
	tenCoin->setVisible(false);
	this->addChild(tenCoin);

	const rapidjson::Value& leftLever = tenYen["leftLever"];
	std::vector<Vec2> leftPos;
	std::vector<Rect> leftArea;
	for (rapidjson::SizeType i = 0; i < leftLever["leftData"].Size(); i++)
	{
		Vec2 pos = Vec2(leftLever["leftData"][i]["position"]["x"].GetFloat(), leftLever["leftData"][i]["position"]["y"].GetFloat());
		leftPos.push_back(pos);

		Rect area = Rect(leftLever["leftData"][i]["Area"]["position"]["x"].GetFloat(), leftLever["leftData"][i]["Area"]["position"]["y"].GetFloat(), leftLever["leftData"][i]["Area"]["size"]["width"].GetFloat(), leftLever["leftData"][i]["Area"]["size"]["height"].GetFloat());
		leftArea.push_back(area);
	}

	for (int i = 0; i < leftPos.size(); i++)
	{
		Sprite* leverBackGround = Sprite::create(leftLever["backGround"]["res"].GetString());
		leverBackGround->setPosition(leftPos[i]);
		leverBackGround->setAnchorPoint(Vec2(leftLever["backGround"]["anchorPoint"]["x"].GetFloat(), leftLever["backGround"]["anchorPoint"]["y"].GetFloat()));
		this->addChild(leverBackGround);

		LeverLeft* lever = LeverLeft::CreateLever(leftLever["res"].GetString(), tenCoin);
		lever->setArea(leftArea[i]);
		lever->setPosition(leftPos[i]);
		this->addChild(lever);
	}

	const rapidjson::Value& rightLever = tenYen["rightLever"];
	std::vector<Vec2> rightPos;
	std::vector<Rect> rightArea;
	for (rapidjson::SizeType i = 0; i < rightLever["rightData"].Size(); i++)
	{
		Vec2 pos = Vec2(rightLever["rightData"][i]["position"]["x"].GetFloat(), rightLever["rightData"][i]["position"]["y"].GetFloat());
		rightPos.push_back(pos);

		Rect area = Rect(rightLever["rightData"][i]["Area"]["position"]["x"].GetFloat(), rightLever["rightData"][i]["Area"]["position"]["y"].GetFloat(), rightLever["rightData"][i]["Area"]["size"]["width"].GetFloat(), rightLever["rightData"][i]["Area"]["size"]["height"].GetFloat());
		rightArea.push_back(area);
	}

	for (int i = 0; i < rightPos.size(); i++)
	{
		Sprite* leverBackGround = Sprite::create(rightLever["backGround"]["res"].GetString());
		leverBackGround->setPosition(rightPos[i]);
		leverBackGround->setAnchorPoint(Vec2(rightLever["backGround"]["anchorPoint"]["x"].GetFloat(), rightLever["backGround"]["anchorPoint"]["y"].GetFloat()));
		this->addChild(leverBackGround);

		LeverRight* lever = LeverRight::CreateLever(rightLever["res"].GetString(), tenCoin);
		lever->setArea(rightArea[i]);
		lever->setPosition(rightPos[i]);
		this->addChild(lever);
	}

	const rapidjson::Value& prizewall = tenYen["prizeWall"];
	PhysicsLine* prizeWall = PhysicsLine::create();
	prizeWall->setCategoryMask(prizewall["categoryMask"].GetInt());
	prizeWall->setCollisionMask(prizewall["collisionMask"].GetInt());
	prizeWall->setContactTestMask(prizewall["contactTestMask"].GetInt());
	prizeWall->CreatePhysicsChain(prizewall["res"].GetString(), PHYSICSBODY_MATERIAL_DEFAULT, true);
	this->addChild(prizeWall);

	const rapidjson::Value& back = tenYen["returnButton"];
	BackButton* backButton = BackButton::ButtonCreate(back["res"].GetString());
	backButton->setPosition(Vec2(backButton->getContentSize().width * 0.5f, visibleSize.height - (backButton->getContentSize().height * 0.5f)));
	backButton->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Button::Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Button::Widget::TouchEventType::ENDED:
			SceneManager::CreateChoiceScene();
			break;
		default:
			break;
		}
	});
	this->addChild(backButton);

	const rapidjson::Value& other = tenYen["other"];
	falling = other["falling"].GetFloat();
	giftExitPos = Vec2(other["geftExitPos"]["width"].GetFloat(), other["geftExitPos"]["height"].GetFloat());
	giftFileName = other["giftFileName"].GetString();

	ManagingSound::GetInstance()->PlayBgm("sound/BGM/tenYenStage", 0.3, true, 0.5f);
}

void TenYenStageLayer::StageUpDate(float delta)
{
	Vec2 velocity = tenCoin->getPhysicsBody()->getVelocity();
	float coinSpeed = velocity.getDistance(Vec2::ZERO);

	if (coinSpeed <= falling && tenCoin->getPhysicsBody()->isEnabled())
	{
		for (int i = 0; i < hole.size(); ++i)
		{
			if (hole[i].containsPoint(tenCoin->getPosition()))
			{
				ManagingSound::GetInstance()->PlaySe("sound/SE/coin_hole.m4a", false);

				tenCoin->SetCoinEnable(false);
				tenCoin->SetCoinVisible(false);
			}
		}

		if (goalHole.containsPoint(tenCoin->getPosition()))
		{
			ManagingSound::GetInstance()->PlaySe("sound/SE/goal", false);

			tenCoin->SetCoinEnable(false);
			tenCoin->SetCoinVisible(false);

			PrizeSprite* gift = PrizeSprite::CreateSprite(giftFileName);
			gift->setPosition(Vec2(visibleSize.width * giftExitPos.x, visibleSize.height * giftExitPos.y));
			this->addChild(gift);
		}
	}
}

void TenYenStageLayer::CoinInlet()
{
	ManagingSound::GetInstance()->PlaySe("sound/SE/coin_entry.m4a", false);

	tenCoin->CoinEntry(Vec2(visibleSize.width * coinExitPos.x, visibleSize.height * coinExitPos.y));
}