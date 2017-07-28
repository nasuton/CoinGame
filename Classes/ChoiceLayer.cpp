#include "ChoiceLayer.h"
#include "SceneManager.h"
#include "ManagingSound.h"
#include "UserData.h"

#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::experimental;

ChoiceLayer::ChoiceLayer()
{

}

ChoiceLayer::~ChoiceLayer()
{

}

bool ChoiceLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = UserData::GetInstance()->GetResolutionSize();

	//jsonを使えるようにする
	rapidjson::Document choiceDoc = JsonHelper::DocumentParse<rapidjson::kParseDefaultFlags>("json/choiceScene.json");

	if (choiceDoc.HasParseError())
	{
		log("json parse error");
	}

	//背景
	const rapidjson::Value& background = choiceDoc["backGround"];
	auto backGround = Sprite::create(background["res"].GetString());
	backGround->setPosition(Vec2(visibleSize.width * background["position"]["x"].GetFloat(), 
								 visibleSize.height * background["position"]["y"].GetFloat()));
	this->addChild(backGround);

	//スライドビューの作成
	const rapidjson::Value& slideView = choiceDoc["slideViewSprite"];
	keeporder view;
	for (rapidjson::Value::ConstMemberIterator itr = slideView.MemberBegin(); itr != slideView.MemberEnd(); itr++)
	{
		std::string name = itr->name.GetString();
		std::string res = itr->value.GetString();
		view.push_back(std::make_pair(name, res));
	}

	//スライドビューの作成
	const rapidjson::Value& slideSetting = choiceDoc["slideView"];
	slider = SliderLayer::create();
	slider->setSliderNum((int)view.size());
	slider->setSliderSpan(slideSetting["span"].GetInt());
	slider->setSlideViewPosition(Vec2(visibleSize.width * slideSetting["position"]["x"].GetFloat(), 
									  visibleSize.height * slideSetting["position"]["y"].GetFloat()));
	slider->AddSlide(view);
	this->addChild(slider);

	//もどるボタンの作成
	const rapidjson::Value& decision = choiceDoc["uiButton"];
	this->DecisionButtonInit(decision);

	//BGMの再生
	ManagingSound::GetInstance()->PlayBgm("BGM/selectSceneBGM", 0.5f, true, 0.5f);

	return true;
}

void ChoiceLayer::DecisionButtonInit(const rapidjson::Value& decision)
{
	auto decisionButton = cocos2d::ui::Button::create(decision["res"].GetString());
	decisionButton->setPosition(Vec2(visibleSize.width * decision["position"]["x"].GetFloat(), 
									 visibleSize.height * decision["position"]["y"].GetFloat()));
	decisionButton->setTitleFontName(UserData::GetInstance()->DefaultFontName());
	decisionButton->setTitleText(decision["fontText"].GetString());
	decisionButton->setTitleFontSize(decision["fontSize"].GetFloat());
	decisionButton->setTitleColor(Color3B(decision["color"]["red"].GetFloat(), 
										  decision["color"]["green"].GetFloat(), 
										  decision["color"]["blue"].GetFloat()));
	decisionButton->addTouchEventListener([this](cocos2d::Ref* sender, 
												 cocos2d::ui::Button::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Button::TouchEventType::ENDED:
			ManagingSound::GetInstance()->StopBgm(0.3f, false);
			this->SelectScene(slider->GetPage());
			break;
		default:
			break;
		}
	});
	this->addChild(decisionButton);
}

void ChoiceLayer::SelectScene(int number)
{
	switch (number)
	{
	case selectScene::stage1:
		SceneManager::CreateTenYenStageScene(number);
		break;

	case selectScene::stage2:
		SceneManager::CreateTenYenStageScene(number);
		break;

	case selectScene::gacha:
		SceneManager::CreateCapsuleToyScene();
		break;

	case selectScene::collection:
		SceneManager::CreateCollectionScene();
		break;
	default:
		break;
	}
}