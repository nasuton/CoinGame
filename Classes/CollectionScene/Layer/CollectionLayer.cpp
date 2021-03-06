﻿#include "CollectionScene/Layer/CollectionLayer.h"
#include "CollectionScene/ModalLayer/CollectionModalLayer.h"
#include "Other/Scene/SceneManager.h"
#include "Other/UserData/UserData.h"
#include "Other/Json/JsonHelper.h"
#include "Other/BackButton.h"
#include "Other/Audio/ManagingSound.h"

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
	//解像度の取得
	Size visibleSize = UserData::GetInstance()->GetResolutionSize();
	
	//背景
	Sprite* backGround = Sprite::create("collection/collectionLayerBack.png");
	backGround->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
	this->addChild(backGround);

	//
	std::vector<cocos2d::ui::Button*> collection;
	ValueMap userHaveIt = UserData::GetInstance()->GetResult();
	scrollViewLayer = ScrollViewLayer::create();
	bool haveIt = false;

	//説明文の取得
	rapidjson::Document sentenceDoc = JsonHelper::DocumentParse<rapidjson::kParseDefaultFlags>("json/resultSentence.json");

	if (sentenceDoc.HasParseError())
	{
		log("sentenceDoc parse Error.");
		return false;
	}

	const rapidjson::Value& sentence = sentenceDoc["resultSentence"];

	//ガチャの中身を全部取得
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

				ui::Button* collectionButton = cocos2d::ui::Button::create("collection/collectionBack.png");
				collectionButton->setSwallowTouches(false);
				collectionButton->addTouchEventListener([this, haveIt, key, res, article](cocos2d::Ref* sender, 
																						  cocos2d::ui::Button::TouchEventType type)	{
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

				//持っていない場合は半透明にする
				Sprite* collectionSprite = Sprite::create(res);
				collectionSprite->setPosition(Vec2(collectionButton->getContentSize().width * 0.5f, 
												   collectionButton->getContentSize().height * 0.5f));
				if (!haveIt)
				{
					collectionSprite->setOpacity(collectionSprite->getOpacity() * 0.5f);
				}
				collectionButton->addChild(collectionSprite);
				collection.push_back(collectionButton);
			}
		}
	}

	//スクロールビューの作成
	ui::ScrollView* scrollView = cocos2d::ui::ScrollView::create();
	scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
	scrollView->setBounceEnabled(true);
	this->addChild(scrollView);

	//Layerを追加
	scrollViewLayer->AddScrollLayer(collection);
	scrollView->addChild(scrollViewLayer);
	scrollView->setInnerContainerSize(Size(scrollViewLayer->getContentSize().width, 
										   scrollViewLayer->getContentSize().height * scrollViewLayer->GetMagnification()));

	//スクロールビューのサイズを設定
	Size inveSize = Size(scrollViewLayer->getContentSize().width,
						 scrollViewLayer->getContentSize().height);
	scrollView->setContentSize(inveSize);

	//もどるボタン
	BackButton* backButton = BackButton::ButtonCreate("backButton.png");
	backButton->setPosition(Vec2(backButton->getContentSize().width * 0.5f, visibleSize.height - (backButton->getContentSize().height * 0.5f)));
	backButton->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Button::Widget::TouchEventType type) {
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

	//BGMを再生
	ManagingSound::GetInstance()->PlayBgm("BGM/collectionSceneBGM", 0.5f, true, 0.5f);

	return true;
}
