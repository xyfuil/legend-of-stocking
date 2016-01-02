#include "WelLayer.h"
#include "GameScene.h"

USING_NS_CC;

WelLayer::WelLayer()
{
}


WelLayer::~WelLayer()
{
}

bool WelLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto start = MenuItemImage::create("ui/start.png", "ui/start_s.png", CC_CALLBACK_1(WelLayer::startCallback, this));
	start->setAnchorPoint(Vec2(0.0f, 0.0f));
	start->setPosition(Vec2(0.0f, 0.0f));

	auto exit = MenuItemImage::create("ui/exit.png", "ui/exit_s.png", CC_CALLBACK_1(WelLayer::exitCallback, this));
	exit->setAnchorPoint(Vec2(0.0f, 0.0f));
	exit->setPosition(Vec2(396.0f, 0.0f));

	auto menu = Menu::create(start, exit, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

void WelLayer::startCallback(Ref *pSender)
{
	criadx2le::stopAll();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameScene::create()));
}
void WelLayer::exitCallback(Ref *pSender)
{
	criadx2le::stopAll();
    Director::getInstance()->end();
}

void WelLayer::onEnterTransitionDidFinish()
{
}