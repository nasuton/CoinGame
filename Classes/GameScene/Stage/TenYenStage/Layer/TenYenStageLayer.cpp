#include "GameScene/Stage/TenYenStage/Layer/TenYenStageLayer.h"
#include "Other/CSV/PhysicsLine.h"
#include "GameScene/PrizeSprite.h"
#include "GameScene/Lever/LeverLeft.h"
#include "GameScene/Lever/LeverRight.h"
#include "Other/BackButton.h"
#include "Other/Scene/SceneManager.h"
#include "Other/Json/JsonHelper.h"
#include "Other/Audio/ManagingSound.h"
#include "Other/UserData/UserData.h"

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
	//解像度の取得
	visibleSize = UserData::GetInstance()->GetResolutionSize();

	//stageのjsonファイルを読み込めるようにする
	rapidjson::Document tenYen = JsonHelper::DocumentParse<rapidjson::kParseDefaultFlags>(StringUtils::format("json/tenYenStage%i.json", num));

	//読み込みに失敗した場合
	if (tenYen.HasParseError())
	{
		log("json parse error.");
	}

	//stageのsettingのjsonを読み込む
	rapidjson::Document tenYenSetting = JsonHelper::DocumentParse<rapidjson::kParseDefaultFlags>(StringUtils::format("json/StageSetting%i.json", num));
	if (tenYenSetting.HasParseError())
	{
		log("json parse error.");
	}

	//落ちる穴の作成のための下準備
	const rapidjson::Value& lostHole = tenYen["lostHole"];
	for (rapidjson::SizeType i = 0; i < lostHole.Size(); i++)
	{
		Rect substitutionLostHole = Rect(lostHole[i]["position"]["x"].GetFloat(),
										 lostHole[i]["position"]["y"].GetFloat(), 
										 lostHole[i]["size"]["width"].GetFloat(), 
										 lostHole[i]["size"]["height"].GetFloat());
		hole.push_back(substitutionLostHole);
	}

	//背景
	const rapidjson::Value& backSprite = tenYenSetting["backGround"];
	Sprite* backGround = Sprite::create(backSprite["res"].GetString());
	backGround->setPosition(Vec2(visibleSize.width * backSprite["position"]["x"].GetFloat(), 
								 visibleSize.height * backSprite["position"]["y"].GetFloat()));
	this->addChild(backGround);

	//描画する白い線の設定
	const rapidjson::Value& stageline = tenYenSetting["physicsLine"];
	PhysicsLine* stageLine = PhysicsLine::create();
	stageLine->CreateLine(stageline["createLine"].GetString());
	stageLine->setCategoryMask(stageline["categoryMask"].GetInt());
	stageLine->setCollisionMask(stageline["collisionMask"].GetInt());
	stageLine->setContactTestMask(stageline["contactTestMask"].GetInt());
	stageLine->CreatePhysicsChain(stageline["createPhysicsChain"].GetString(), 
								  PhysicsMaterial(stageline["material"]["density"].GetFloat(),
												  stageline["material"]["restitution"].GetFloat(), 
												  stageline["material"]["friction"].GetFloat()), 
								  true);
	this->addChild(stageLine);

	//コインを出現させるためのボタン
	const rapidjson::Value& uiButton = tenYenSetting["coinInletItem"];
	ui::Button* coinInletItem = cocos2d::ui::Button::create(uiButton["res"].GetString());
	coinInletItem->addTouchEventListener([this](cocos2d::Ref* sender, 
										 cocos2d::ui::Button::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Button::Widget::TouchEventType::ENDED:
			this->CoinInlet();
			break;

		default:
			break;
		}
	});
	coinExitPos = Vec2(uiButton["position"]["x"].GetFloat(), 
					   uiButton["position"]["y"].GetFloat());
	coinInletItem->setPosition(Vec2(visibleSize.width * coinExitPos.x, 
									visibleSize.height * coinExitPos.y));
	this->addChild(coinInletItem);

	//落ちる穴の描画
	const rapidjson::Value& circle = tenYenSetting["circleNode"];
	for (int i = 0; i < hole.size(); i++)
	{
		Vec2 circlePos = Vec2(hole[i].origin.x + (hole[i].size.width * circle["position"]["x"].GetFloat()), 
							  hole[i].origin.y + (hole[i].size.height * circle["position"]["y"].GetFloat()));
		DrawNode* circleNode = DrawNode::create();
		circleNode->drawDot(circlePos, 
							circle["size"].GetFloat(), 
							Color4F(circle["color"]["red"].GetFloat(), 
									circle["color"]["green"].GetFloat(),
									circle["color"]["blue"].GetFloat(), 
									circle["color"]["alpha"].GetFloat()));
		this->addChild(circleNode);
	}

	//ゴールの作成
	const rapidjson::Value& goal = tenYen["goalHole"];
	goalHole = Rect(goal["position"]["x"].GetFloat(), 
					goal["position"]["y"].GetFloat(), 
					goal["size"]["width"].GetFloat(), 
					goal["size"]["height"].GetFloat());

	Sprite* goalHoleRect = Sprite::create();
	goalHoleRect->setTextureRect(goalHole);
	goalHoleRect->setColor(Color3B(255, 0, 0));
	goalHoleRect->setPosition(Vec2(goalHole.origin.x + (goalHole.size.width * 0.5f), 
								   goalHole.origin.y + (goalHole.size.height * 0.5f)));
	this->addChild(goalHoleRect);

	//コインの設定
	const rapidjson::Value& coin = tenYenSetting["tenCoin"];
	PhysicsMaterial coinMaterial;
	coinMaterial.density = coin["coinMaterial"]["density"].GetFloat();
	coinMaterial.restitution = coin["coinMaterial"]["restitution"].GetFloat();
	coinMaterial.friction = coin["coinMaterial"]["friction"].GetFloat();

	PhysicsBody* coinPhysics = PhysicsBody::createCircle(coin["coinPhysics"]["radius"].GetFloat(), 
														 coinMaterial);
	coinPhysics->setMass(coin["coinPhysics"]["mass"].GetFloat());
	coinPhysics->setMoment(coin["coinPhysics"]["moment"].GetFloat());
	coinPhysics->setCategoryBitmask(coin["coinPhysics"]["categoryBitmask"].GetInt());
	coinPhysics->setCollisionBitmask(coin["coinPhysics"]["collisionBitmask"].GetInt());
	coinPhysics->setContactTestBitmask(coin["coinPhysics"]["contactTestBitmask"].GetInt());
	coinPhysics->setName(coin["coinPhysics"]["name"].GetString());

	//コインを実際に作成
	tenCoin = Coin::CreateSprite(coin["res"].GetString());
	tenCoin->SetCoinPhysics(coinPhysics);
	tenCoin->SetCoinEnable(false);
	tenCoin->setVisible(false);
	this->addChild(tenCoin);

	//左のレバーの作成
	const rapidjson::Value& leftLever = tenYen["leftLever"];
	std::vector<Vec2> leftPos;
	std::vector<Rect> leftArea;
	for (rapidjson::SizeType i = 0; i < leftLever["leftData"].Size(); i++)
	{
		Vec2 pos = Vec2(leftLever["leftData"][i]["position"]["x"].GetFloat(), 
						leftLever["leftData"][i]["position"]["y"].GetFloat());
		leftPos.push_back(pos);

		Rect area = Rect(leftLever["leftData"][i]["Area"]["position"]["x"].GetFloat(), 
						 leftLever["leftData"][i]["Area"]["position"]["y"].GetFloat(), 
						 leftLever["leftData"][i]["Area"]["size"]["width"].GetFloat(), 
						 leftLever["leftData"][i]["Area"]["size"]["height"].GetFloat());
		leftArea.push_back(area);
	}

	//実際にレバーを描画する
	const rapidjson::Value& leftLeverSprite = tenYenSetting["lever"];
	for (int i = 0; i < leftPos.size(); i++)
	{
		Sprite* leverBackGround = Sprite::create(leftLeverSprite["backGround"]["res"].GetString());
		leverBackGround->setPosition(leftPos[i]);
		leverBackGround->setAnchorPoint(Vec2(leftLeverSprite["backGround"]["anchorPoint"]["x"].GetFloat(),
											 leftLeverSprite["backGround"]["anchorPoint"]["y"].GetFloat()));
		this->addChild(leverBackGround);

		LeverLeft* lever = LeverLeft::CreateLever(leftLeverSprite["res"].GetString(), tenCoin);
		lever->setArea(leftArea[i]);
		lever->setPosition(leftPos[i]);
		this->addChild(lever);
	}

	//右のレバーを作成
	const rapidjson::Value& rightLever = tenYen["rightLever"];
	std::vector<Vec2> rightPos;
	std::vector<Rect> rightArea;
	for (rapidjson::SizeType i = 0; i < rightLever["rightData"].Size(); i++)
	{
		Vec2 pos = Vec2(rightLever["rightData"][i]["position"]["x"].GetFloat(),
						rightLever["rightData"][i]["position"]["y"].GetFloat());
		rightPos.push_back(pos);

		Rect area = Rect(rightLever["rightData"][i]["Area"]["position"]["x"].GetFloat(), 
						 rightLever["rightData"][i]["Area"]["position"]["y"].GetFloat(),
						 rightLever["rightData"][i]["Area"]["size"]["width"].GetFloat(), 
						 rightLever["rightData"][i]["Area"]["size"]["height"].GetFloat());
		rightArea.push_back(area);
	}

	//実際にレバーを描画する
	const rapidjson::Value& rightLeverSprite = tenYenSetting["lever"];
	for (int i = 0; i < rightPos.size(); i++)
	{
		Sprite* leverBackGround = Sprite::create(rightLeverSprite["backGround"]["res"].GetString());
		leverBackGround->setPosition(rightPos[i]);
		leverBackGround->setAnchorPoint(Vec2(rightLeverSprite["backGround"]["anchorPoint"]["x"].GetFloat(),
											 rightLeverSprite["backGround"]["anchorPoint"]["y"].GetFloat()));
		this->addChild(leverBackGround);

		LeverRight* lever = LeverRight::CreateLever(rightLeverSprite["res"].GetString(), tenCoin);
		lever->setArea(rightArea[i]);
		lever->setPosition(rightPos[i]);
		this->addChild(lever);
	}

	//景品の出口の設定
	const rapidjson::Value& prizewall = tenYenSetting["prizeWall"];
	PhysicsLine* prizeWall = PhysicsLine::create();
	prizeWall->setCategoryMask(prizewall["categoryMask"].GetInt());
	prizeWall->setCollisionMask(prizewall["collisionMask"].GetInt());
	prizeWall->setContactTestMask(prizewall["contactTestMask"].GetInt());
	prizeWall->CreatePhysicsChain(prizewall["res"].GetString(),
								  PHYSICSBODY_MATERIAL_DEFAULT, 
								  true);
	this->addChild(prizeWall);

	//もどるボタンの作成
	const rapidjson::Value& back = tenYenSetting["returnButton"];
	BackButton* backButton = BackButton::ButtonCreate(back["res"].GetString());
	backButton->setPosition(Vec2(backButton->getContentSize().width * 0.5f,
								 visibleSize.height - (backButton->getContentSize().height * 0.5f)));
	backButton->addTouchEventListener([this](cocos2d::Ref* sender, 
											 cocos2d::ui::Button::Widget::TouchEventType type) {
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

	//その他の細かい設定
	const rapidjson::Value& other = tenYenSetting["other"];
	falling = other["falling"].GetFloat();
	giftExitPos = Vec2(other["geftExitPos"]["width"].GetFloat(), 
					   other["geftExitPos"]["height"].GetFloat());
	giftFileName = other["giftFileName"].GetString();

	//BGMの再生
	ManagingSound::GetInstance()->PlayBgm("BGM/tenYenStageBGM", 0.3, true, 0.5f);
}

void TenYenStageLayer::StageUpDate(float delta)
{
	Vec2 velocity = tenCoin->getPhysicsBody()->getVelocity();
	float coinSpeed = velocity.getDistance(Vec2::ZERO);

	//穴へ落ちる処理
	if (coinSpeed <= falling && tenCoin->getPhysicsBody()->isEnabled())
	{
		for (int i = 0; i < hole.size(); ++i)
		{
			if (hole[i].containsPoint(tenCoin->getPosition()))
			{
				//SEの再生
				ManagingSound::GetInstance()->PlaySe("SE/coin_hole.m4a", false);

				tenCoin->SetCoinEnable(false);
				tenCoin->SetCoinVisible(false);
			}
		}

		if (goalHole.containsPoint(tenCoin->getPosition()))
		{
			//SEの再生
			ManagingSound::GetInstance()->PlaySe("SE/goal.m4a", false);

			tenCoin->SetCoinEnable(false);
			tenCoin->SetCoinVisible(false);

			//ゴールへ落ちた際は景品を輩出
			PrizeSprite* gift = PrizeSprite::CreateSprite(giftFileName);
			gift->setPosition(Vec2(visibleSize.width * giftExitPos.x, visibleSize.height * giftExitPos.y));
			this->addChild(gift);
		}
	}
}

void TenYenStageLayer::CoinInlet()
{
	//SEの再生
	ManagingSound::GetInstance()->PlaySe("SE/coin_entry.m4a", false);

	tenCoin->CoinEntry(Vec2(visibleSize.width * coinExitPos.x, visibleSize.height * coinExitPos.y));
}
