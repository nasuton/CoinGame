#include "SliderLayer.h"
#include "UserData.h"

USING_NS_CC;

SliderLayer::SliderLayer()
	:sliderSpan(0)
	,sliderNum(0)
	,slideViewPositon(0.0f, 0.0f)
	,sliderPosX(0)
	,page(0)
{
	//touchを追加
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(SliderLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(SliderLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SliderLayer::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(SliderLayer::onTouchCancelled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

}

SliderLayer::~SliderLayer()
{
	//touchを削除
	Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
}

bool SliderLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	moveToDuration = 0.3f;
	positionY = 0.0f;
	easeOutTime = 2.0f;

	return true;
}

void SliderLayer::AddSlide(std::vector<std::pair<std::string, std::string>> &addSlideView)
{
	for (int i = 0; i < addSlideView.size(); i++)
	{
		Label* slideLabel = Label::createWithTTF(UserData::GetInstance()->DefaultTTF(40.0f), 
												 addSlideView[i].first);
		slideLabel->setColor(Color3B::BLACK);
		slideLabel->setPosition(Vec2(slideViewPositon.x + (sliderSpan * i), 
									 slideViewPositon.y + 200.0f));
		this->addChild(slideLabel);

		Sprite* slideSprite = Sprite::create(addSlideView[i].second);
		slideSprite->setPosition(Vec2(slideViewPositon.x + (sliderSpan * i), 
									  slideViewPositon.y));
		this->addChild(slideSprite);
	}
}

int SliderLayer::GetPage()
{
	return page;
}

bool SliderLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	Vec2 touchPoint = touch->getLocation();

	sliderPosX = this->getPosition().x - touchPoint.x;

	swipePosX = touchPoint.x;

	swipeDifference = 0;

	return true;
}

void SliderLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	Vec2 touchPoint = touch->getLocation();

	this->setPosition(touchPoint.x + sliderPosX, 0);

	swipeDifference = swipePosX - touchPoint.x;

	swipePosX = touchPoint.x;
}

void SliderLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	if (20 < fabs(swipeDifference))
	{
		if (swipeDifference < 0)
		{
			if (0 < page)
			{
				page--;
			}
		}
		else
		{
			if (page < sliderNum - 1)
			{
				page++;
			}
		}
	}
	else
	{
		float view = this->getPosition().x;

		if ((view < -sliderSpan * page - sliderSpan / 4) && page < sliderNum - 1)
		{
			page++;
		}
		else if ((-sliderSpan * page + sliderSpan / 4 < view) && 0 < page)
		{
			page--;
		}
	}

	//実際に動かす関数
	SlidePage();

}

void SliderLayer::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	//指を離した時と同じ
	SlidePage();
}

void SliderLayer::SlidePage()
{
	//動かす
	this->runAction(EaseOut::create(MoveTo::create(moveToDuration, Point(-sliderSpan * page, positionY)), easeOutTime));
}