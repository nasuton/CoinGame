﻿#include "CapsuleToysLayer.h"
#include "JsonHelper.h"
#include "SceneManager.h"
#include "CapsuleToysModalLayer.h"
#include "UserData.h"

USING_NS_CC;

CapsuleToysLayer::CapsuleToysLayer()
	:totalProbability(0.0f)
{

}

CapsuleToysLayer::~CapsuleToysLayer()
{
	result.clear();
}

bool CapsuleToysLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = UserData::GetInstance()->GetResolutionSize();

	rapidjson::Document capsuleToysDoc = JsonHelper::DocumentParse<rapidjson::kParseDefaultFlags>("json/capsuleToysScene.json");

	if (capsuleToysDoc.HasParseError())
	{
		log("json parse error");
	}

	Sprite* capsuleBack = Sprite::create("gacha/capsuleBackGround.png");
	capsuleBack->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
	this->addChild(capsuleBack);

	const rapidjson::Value& bodySprite = capsuleToysDoc["backGround"];
	Sprite* body = Sprite::create(bodySprite["res"].GetString());
	body->setPosition(Vec2(visibleSize.width * bodySprite["position"]["x"].GetFloat(), visibleSize.height * bodySprite["position"]["y"].GetFloat()));
	this->addChild(body);

	const rapidjson::Value& handle = capsuleToysDoc["gachaHandle"];
	handleSprite = GachaHandleSprite::CreateSprite(handle["res"].GetString());
	handleSprite->setPosition(Vec2(visibleSize.width * handle["position"]["x"].GetFloat(), visibleSize.height * handle["position"]["y"].GetFloat()));
	this->addChild(handleSprite);

	const rapidjson::Value& uiBack = capsuleToysDoc["backButton"];
	backButton = BackButton::ButtonCreate(uiBack["res"].GetString());
	backButton->setPosition(Vec2(backButton->getContentSize().width * uiBack["position"]["x"].GetFloat(), visibleSize.height - (backButton->getContentSize().height * uiBack["position"]["y"].GetFloat())));
	backButton->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Button::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Button::Widget::TouchEventType::ENDED:
			SceneManager::CreateChoiceScene();
			break;
		default:
			break;
		}
	});
	this->addChild(backButton);

	const rapidjson::Value& uiButton = capsuleToysDoc["gachaButton"];
	gachaButton = GachaButton::CreateGacha(uiButton["res"].GetString());
	gachaButton->setPosition(Vec2(visibleSize.width * uiButton["position"]["x"].GetFloat(), visibleSize.height * uiButton["position"]["y"].GetFloat()));
	gachaButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			handleSprite->SpriteTouch();

			gachaButton->setTouchEnabled(false);

			backButton->setTouchEnabled(false);

			scheduleOnce(schedule_selector(CapsuleToysLayer::DischargeCapsule), 4.0f);
		}
	});
	this->addChild(gachaButton);


	this->SetResult("json/result.json");
	for (auto itr = result.begin(); itr != result.end(); itr++)
	{
		totalProbability += itr->second.probability;
	}

	return true;
}

void CapsuleToysLayer::DischargeCapsule(float delta)
{
	Sprite* capsule = Sprite::create("gacha/capsule.png");
	capsule->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.32f));
	capsule->setOpacity(0);
	this->addChild(capsule);

	auto fadeInCapsule = FadeIn::create(1.0f);

	auto moveToCapsule = MoveTo::create(1.5f, Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.26f));

	auto fadeOutCapsule = FadeOut::create(2.0f);

	auto resetButtonFunc = CallFunc::create([this]() {
		gachaButton->setTouchEnabled(true);

		backButton->setTouchEnabled(true);
	});

	auto removeCapsule = RemoveSelf::create();

	auto modalFunc = CallFunc::create([this]() {
		this->SelectResult(result);
	});

	auto sequence = Sequence::create(fadeInCapsule, moveToCapsule, fadeOutCapsule, resetButtonFunc, removeCapsule, modalFunc, NULL);

	capsule->runAction(sequence);
}

bool CapsuleToysLayer::SetResult(std::string jsonPath)
{
	rapidjson::Document resultDoc = JsonHelper::DocumentParse<rapidjson::kParseDefaultFlags>(jsonPath);

	if (resultDoc.HasParseError())
	{
		log("resultDoc parse Error.");
		return false;
	}

	if (resultDoc.IsObject())
	{
		rapidjson::Value& contents = resultDoc["result"];

		for (rapidjson::Value::ConstMemberIterator itr = contents.MemberBegin(); itr != contents.MemberEnd(); itr++)
		{
			std::string key = itr->name.GetString();
			const rapidjson::Value& value = itr->value;
			if (value.GetType() == rapidjson::kArrayType)
			{
				result[key].res = value[0].GetString();
				if (value.Size() > 1)
				{
					result[key].probability = value[1].GetFloat();
				}
			}
		}
	}

	return true;
}

void CapsuleToysLayer::SelectResult(std::map<std::string, contentsParameter> const& resultReference)
{
	std::random_device rand_divice;
	std::mt19937 mersenne(rand_divice());
	std::uniform_real_distribution<float> rand(0.0f, totalProbability);

	float randomResult = rand(mersenne);

	for (auto itr = resultReference.begin(); itr != resultReference.end(); itr++)
	{
		randomResult -= itr->second.probability;
		if (randomResult < 0)
		{
			auto modal = CapsuleToysModalLayer::create();
			modal->DrawingResult(itr->first, itr->second.res);
			this->addChild(modal);
			UserData::GetInstance()->SaveResult(itr->first, itr->second.res);
			break;
		}
	}
}