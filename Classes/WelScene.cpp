#include "WelScene.h"
#include "WelLayer.h"

USING_NS_CC;

WelScene::WelScene()
{
}


WelScene::~WelScene()
{
}

bool WelScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	criadx2le::loadAcbFile("music/bgm.acb", "music/bgm.awb");

	auto layer = WelLayer::create();
	this->addChild(layer);

	return true;
}

void WelScene::onEnterTransitionDidFinish()
{
	//AudioEngine::play2d("music/wel.mp3", true, 0.5f);
	criadx2le::playCueById(0);
}