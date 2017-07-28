#include "AppDelegate.h"
#include "EnvironmentDefaultData.h"
#include "TitleScene.h"
#include "UserData.h"

#define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    
	auto evn = EnvironmentDefaultData::GetInstance();
	
	// initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect(evn->gameName, cocos2d::Rect(0, 0, evn->largeResolutionSize.width, evn->largeResolutionSize.height));
#else
        glview = GLViewImpl::create(evn->gameName);
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(evn->designResolutionSize.width, evn->designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > evn->mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(evn->largeResolutionSize.height/evn->designResolutionSize.height, evn->largeResolutionSize.width/evn->designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > evn->smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(evn->mediumResolutionSize.height/evn->designResolutionSize.height, evn->mediumResolutionSize.width/evn->designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(evn->smallResolutionSize.height/evn->designResolutionSize.height, evn->smallResolutionSize.width/evn->designResolutionSize.width));
    }

    register_all_packages();

	//プラットフォームによって読み込むファイルを分ける
	std::vector<std::string> searchPath;
	auto platform = Application::getInstance()->getTargetPlatform();
	switch (platform)
	{
	case Application::Platform::OS_ANDROID:
		searchPath.push_back("Android");
		searchPath.push_back("json");
		searchPath.push_back("fonts");
		searchPath.push_back("sound/Smartphone");
		searchPath.push_back("stageData");
		break;
		
	case Application::Platform::OS_IPHONE:
		searchPath.push_back("ios");
		searchPath.push_back("json");
		searchPath.push_back("fonts");
		searchPath.push_back("sound/Smartphone");
		searchPath.push_back("stageData");
		break;

	case Application::Platform::OS_WINDOWS:
		searchPath.push_back("Android");
		searchPath.push_back("json");
		searchPath.push_back("sound/Windows");
		searchPath.push_back("fonts");
		searchPath.push_back("stageData");
		break;
	default:
		break;
	}
	//上記で分けたpathで探すようにする
	FileUtils::getInstance()->setSearchPaths(searchPath);

	//解像度を取得する
	Size visibleSize = Director::getInstance()->getVisibleSize();
	UserData::GetInstance()->SetResolutionSize(visibleSize);
	//plistを作成する
	UserData::GetInstance()->CreatePlist();

    //最初に流すsceneを作成
	auto scene = TitleScene::SceneCreate();

    //その作ったシーンを実際に動かす
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
