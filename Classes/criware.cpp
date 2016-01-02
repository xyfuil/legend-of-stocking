#include "criware.h"
#include "WelScene.h"

USING_NS_CC;

criware::criware()
{
}


criware::~criware()
{
}

bool criware::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto cri = Sprite::create("ui/criware.png");
	//cri->getTexture()->setAliasTexParameters();
	cri->setPosition(Vec2(400.0f, 240.0f));
	cri->setOpacity(0.0f);
	this->addChild(cri);

	cri->runAction(Sequence::create(DelayTime::create(0.5f), EaseSineOut::create(FadeIn::create(0.8f)), DelayTime::create(1.0f), CallFunc::create(CC_CALLBACK_0(criware::end, this)), NULL));

	return true;
}

void criware::end()
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, WelScene::create()));
}