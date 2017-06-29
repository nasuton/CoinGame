#include "CollectionLayer.h"
#include "CollectionModalLayer.h"
#include "SceneManager.h"
#include "UserData.h"
#include "JsonHelper.h"
#include "BackButton.h"
#include "ManagingSound.h"

#include "ui/CocosGUI.h"

USING_NS_CC;

CollectionLayer::CollectionLayer()
{

}

CollectionLayer::~CollectionLayer()
{

}

bool CollectionLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = UserData::GetInstance()->GetResolutionSize();

	Sprite* backGround = Sprite::create("collection/collectionLayerBack.png");
	backGround->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
	this->addChild(backGround);

	std::vector<cocos2d::ui::Button*> collection;
	ValueMap userHaveIt = UserData::GetInstance()->GetResult();
	scrollViewLayer = ScrollViewLayer::create();
	bool haveIt = false;

	rapidjson::Document sentenceDoc = JsonHelper::DocumentParse<rapidjson::kParseDefaultFlags>("json/resultSentence.json");

	if (sentenceDoc.HasParseError())
	{
		log("sentenceDoc parse Error.");
		return false;
	}

	const rapidjson::Value& sentence = sentenceDoc["resultSentence"];


	rapidjson::Document collectionDoc = JsonHelper::DocumentParse<rapidjson::kParseDefaultFlags>("json/result.json");

	if (collectionDoc.HasParseError())
	{
		log("collectionDoc parse Error.");
		return false;
	}

	if (collectionDoc.IsObject())
	{
		std::string key;
		std::string article;
		std::string res;

		rapidjson::Value& contents = collectionDoc["result"];
		for (rapidjson::Value::ConstMemberIterator itr = contents.MemberBegin(); itr != contents.MemberEnd(); itr++)
		{
			key = itr->name.GetString();
			const rapidjson::Value& value = itr->value;
			if (userHaveIt.find(key) != userHaveIt.end())
			{
				haveIt = true;
				article = sentence[key.c_str()].GetString();
			}
			else
			{
				haveIt = false;
			}

			if (value.GetType() == rapidjson::kArrayType)
			{
				res = value[0].GetString();

				auto collectionButton = cocos2d::ui::Button::create("collection/collectionBack.png");
				collectionButton->setSwallowTouches(false);
				collectionButton->addTouchEventListener([this, haveIt, key, res, article](cocos2d::Ref* sender, cocos2d::ui::Button::TouchEventType type)
				{
					switch (type)
					{
						case cocos2d::ui::Button::TouchEventType::ENDED:
							if (!scrollViewLayer->GetMove())
							{
								CollectionModalLayer* modal = CollectionModalLayer::create();
								if (!haveIt)
								{
									modal->DoNotHave(res, key);
									this->addChild(modal);
								}
								else
								{
									modal->HaveIt(res, key, article);
									this->addChild(modal);
								}
							}
							break;
						default:
							break;
					}
				});
				Sprite* collectionSprite = Sprite::create(res);
				collectionSprite->setPosition(Vec2(collectionButton->getContentSize().width * 0.5f, collectionButton->getContentSize().height * 0.5f));
				if (!haveIt)
				{
					collectionSprite->setOpacity(collectionSprite->getOpacity() * 0.5f);
				}
				collectionButton->addChild(collectionSprite);
				collection.push_back(collectionButton);
			}
		}
	}

	ui::ScrollView* scrollView = cocos2d::ui::ScrollView::create();
	scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
	scrollView->setBounceEnabled(true);
	this->addChild(scrollView);

	scrollViewLayer->AddScrollLayer(collection);
	scrollView->addChild(scrollViewLayer);
	scrollView->setInnerContainerSize(Size(scrollViewLayer->getContentSize().width, scrollViewLayer->getContentSize().height * scrollViewLayer->GetMagnification()));

	Size inveSize = Size(scrollViewLayer->getContentSize().width, scrollViewLayer->getContentSize().height);
	scrollView->setContentSize(inveSize);

	BackButton* backButton = BackButton::ButtonCreate("backButton.png");
	backButton->setPosition(Vec2(backButton->getContentSize().width * 0.5f, visibleSize.height - (backButton->getContentSize().height * 0.5f)));
	backButton->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Button::Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Button::Widget::TouchEventType::ENDED:
			ManagingSound::GetInstance()->StopBgm(0.3f, true);
			SceneManager::CreateChoiceScene();
			break;
		default:
			break;
		}
	});
	this->addChild(backButton);

	ManagingSound::GetInstance()->PlayBgm("sound/BGM/collectionSceneBGM", 0.5f, true, 0.5f);

	return true;
}