#include "AppDelegate.h"
#include "LoadingScene.h"
#include "WelScene.h"
#include "GameScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("The Legend Of Stocking", Rect(0.0f, 0.0f, 800.0f, 480.0f), 1.0f);
        director->setOpenGLView(glview);
    }

	glview->setDesignResolutionSize(800.0f, 480.0f, kResolutionShowAll);
    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	criadx2le::initialize();

    // create a scene. it's an autorelease object
    auto scene = LoadingScene::create();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		/* ¥µ¥¹¥Ú¥ó¥É•r¤ÏÒôÉù¤òÒ»•rÍ£Ö¹ */
		criAtomEx_StopSound_ANDROID();
	#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		/* ¥µ¥¹¥Ú¥ó¥É•r¤ÏÒôÉù¤òÒ»•rÍ£Ö¹ */
		criAtomEx_StopSound_IOS();
	#endif

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		/* ¥ê¥¸¥å©`¥à•r¤ÏÒôÉù¤òÔÙé_ */
		criAtomEx_StartSound_ANDROID();
	#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		/* ¥µ¥¹¥Ú¥ó¥É•r¤ÏÒôÉù¤òÒ»•rÍ£Ö¹ */
		criAtomEx_StopSound_IOS();
	#endif

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
