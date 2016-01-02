#include "LoadingScene.h"
#include "criware.h"

USING_NS_CC;

LoadingScene::LoadingScene()
{
}


LoadingScene::~LoadingScene()
{
}

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/ui.plist");

	auto layer = criware::create();
	this->addChild(layer);

	return true;
}